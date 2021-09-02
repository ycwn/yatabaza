

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>

#include "stm32f1xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"

#include "core/types.h"
#include "core/algorithm.h"
#include "core/list.h"
#include "core/console.h"
#include "core/kernel.h"
#include "core/service.h"

#include "synth/midi.h"


#define MIDI_VCALL(func, obj, ...)                                \
	do {                                                      \
		if ((obj)->func != NULL)                          \
			(obj)->func((obj)->ptr,##__VA_ARGS__);    \
	} while (0)


enum {
	MIDI_STATUS_INIT = 0
};

static int midi_start();
static int midi_stop();

static int event_length(uint status);
static int event_decode(midi_event *evt, const midi_rawevent *rev);

static inline bool is_midi_status(  uint c) { return (c & 0x80) != 0; }
static inline bool is_midi_channel( uint c) { return (c & 0xF0) != 0xF0; }
static inline bool is_midi_realtime(uint c) { return (c & 0xF8) == 0xF8; }
static inline bool is_midi_system(  uint c) { return (c & 0xF8) == 0xF0; }


SERVICE(midi,

	SERVICE_START(midi_start),
	SERVICE_STOP(midi_stop),

	SERVICE_DESCRIPTION("MIDI Core")

);

//TODO: make ring buffer size configurable at compile time
GENERATE_RINGBUF(midibuf, midi_rawevent, 32);

static list              drains;
static uint              source_id;
static struct midibuf    queue;
static midi_fn_realtime  realtime_handler;



int midi_start()
{

	list_init(&drains, NULL);

	source_id        = 0;
	realtime_handler = NULL;

	midibuf_clear(&queue);

	return 0;

}



int midi_stop()
{

	return 0;

}



/**
 *
 * Initialize the statemachine of a MIDI source
 *
 **/
int midi_source_init(midi_source *src)
{

	if (src == NULL)
		return -EINVAL;

	src->revent.src_id = source_id++;
	src->revent.status = MIDI_STATUS_INIT;
	src->count         = 0;

	return 0;

}



/**
 *
 * Process a single byte from a MIDI source, and update
 * the state accordingly. Realtime events are dispatched
 * immediately, while normal messages are dispatched
 * through a queue. Sysex messages are handled out-of-bounds,
 * since their length is not limited, nor can it be
 * determined. This function should be safe enough to be
 * called during an ISR.
 *
 **/
int midi_source_recv(midi_source *src, u8 data)
{

	if (src == NULL)
		return -EINVAL;

	if (is_midi_realtime(data))
		return midi_dispatch_realtime(src->revent.src_id, data);

	if (is_midi_status(data)) {

		src->revent.status = data;
		src->count         = 0;
		src->total         = event_length(data);

		if (src->total > 0)
			return 0;

	} else {

		if (src->revent.status == MIDI_STATUS_INIT)
			return 0;

		src->revent.data[src->count++] = data;

		if (src->count < src->total)
			return 0;

		src->count = 0;

	}

	midi_post(&src->revent);

	// System messages don't have running status
	if (is_midi_system(src->revent.status) && src->revent.status != MIDI_SYSTEM_SYSEX_DATA)
		src->revent.status = MIDI_STATUS_INIT;

	return 0;

}



/**
 *
 *  Initialize a MIDI event drain
 *
 **/
int midi_drain_init(midi_drain *snk)
{

	if (snk == NULL)
		return -EINVAL;

	list_init(&snk->node, snk);

	snk->status   = MIDI_STATUS_INIT;
	snk->channels = MIDI_ALL;

	snk->start = NULL;
	snk->stop  = NULL;

	snk->write = NULL;
	snk->event = NULL;

	snk->note            = NULL;
	snk->note_on         = NULL;
	snk->note_off        = NULL;
	snk->controller      = NULL;
	snk->program         = NULL;
	snk->aftertouch      = NULL;
	snk->aftertouch_poly = NULL;
	snk->aftertouch_mono = NULL;
	snk->pitchbend       = NULL;

	snk->sysex_data = NULL;
	snk->sysex_end  = NULL;

	snk->tcqf     = NULL;
	snk->song_pos = NULL;
	snk->song_sel = NULL;
	snk->tunerq   = NULL;

	snk->ptr = NULL;

	return 0;

}



/**
 *
 *  Register a MIDI event drain
 *
 */
int midi_drain_register(midi_drain *snk)
{

	if (list_connected(&snk->node))
		return -1;

	list_append(&drains, &snk->node);
	snk->start(snk);

	return 0;

}



/**
 *
 *  Unregister a MIDI event drain
 *
 */
int midi_drain_unregister(midi_drain *snk)
{

	if (snk == NULL)
		return -EINVAL;

	if (!list_connected(&snk->node))
		return -1;

	snk->stop(snk);
	list_remove(&snk->node);

	return 0;

}



/**
 *
 *  Pump the MIDI event queue
 *  Returns the number of events remaining in the queue
 *
 **/
int midi_pump()
{

	midi_rawevent rev;

	bool empty;

	CRITICAL_SECTION(
		empty = !midibuf_popv(&queue, &rev);
	);

	if (empty)
		return 0;

	int rc = midi_dispatch_raw(&rev);

	if (rc < 0)
		return rc;

	return midibuf_count(&queue);

}



/**
 *
 *  Push a MIDI event on to the queue
 *
 **/
int midi_post(const midi_rawevent *rev)
{

	if (rev == NULL)
		return -EINVAL;

	CRITICAL_SECTION(
		midibuf_pushv(&queue, rev);
	);

	return 0;

}



/**
 *
 *  Dispatch a MIDI event to the drains
 *
 **/
int midi_dispatch(const midi_event *evt)
{

	if (evt == NULL)
		return -EINVAL;

	int count = event_length(evt->revent.status);

	for (list *node=list_begin(&drains); node != list_end(&drains); node=node->next) {

		struct midi_drain *snk = LIST_PTR(midi_drain, node);

		uint mask =
			is_midi_channel(evt->revent.status)? 1 << (evt->revent.status & 0x0F):
			is_midi_system(evt->revent.status)?  MIDI_SYSTEM:
			0;

		if ((snk->channels & mask) == 0)
			continue;

		if (count >= 0) { // If theres a valid raw event, update the drain's state

			if (snk->status != evt->revent.status) {

				snk->status = evt->revent.status;
				MIDI_VCALL(write, snk, &evt->revent.status, sizeof(u8));

			}

			MIDI_VCALL(write, snk, evt->revent.data, count);

		}

		MIDI_VCALL(event, snk, evt);

		switch (evt->type) {

			case MIDI_EVENT_NOTE_OFF:
				MIDI_VCALL(note,     snk, evt->note.channel, evt->note.key, 0);
				MIDI_VCALL(note_off, snk, evt->note.channel, evt->note.key, evt->note.velocity);
				break;

			case MIDI_EVENT_NOTE_ON:
				MIDI_VCALL(note, snk, evt->note.channel, evt->note.key, evt->note.velocity);

				if (evt->note.velocity > 0)
					MIDI_VCALL(note_off, snk, evt->note.channel, evt->note.key, evt->note.velocity);

				else
					MIDI_VCALL(note_off, snk, evt->note.channel, evt->note.key, 0);
				break;

			case MIDI_EVENT_AFTERTOUCH_POLY:
				MIDI_VCALL(aftertouch, snk, evt->aftertouch.channel, evt->aftertouch.key, evt->aftertouch.pressure);
				MIDI_VCALL(aftertouch_poly, snk, evt->aftertouch.channel, evt->aftertouch.key, evt->aftertouch.pressure);
				break;

			case MIDI_EVENT_AFTERTOUCH_MONO:
				MIDI_VCALL(aftertouch,      snk, evt->aftertouch.channel, -1, evt->aftertouch.pressure);
				MIDI_VCALL(aftertouch_mono, snk, evt->aftertouch.channel, evt->aftertouch.pressure);
				break;

			case MIDI_EVENT_CONTROL_CHANGE:
				MIDI_VCALL(controller, snk, evt->control.channel, evt->control.id, evt->control.value);
				break;

			case MIDI_EVENT_PROGRAM_CHANGE:
				MIDI_VCALL(program, snk, evt->program.channel, evt->program.number);
				break;

			case MIDI_EVENT_PITCHBEND:
				MIDI_VCALL(pitchbend, snk, evt->pitchbend.channel, evt->pitchbend.amount);
				break;

			case MIDI_SYSTEM_SYSEX_DATA:
				MIDI_VCALL(sysex_data, snk, evt->sysex.data);
				break;

			case MIDI_SYSTEM_TCQF:
				MIDI_VCALL(tcqf, snk, evt->tcqf.code, evt->tcqf.value);
				break;

			case MIDI_SYSTEM_SONGPOS:
				MIDI_VCALL(song_pos, snk, evt->song.position);
				break;

			case MIDI_SYSTEM_SONGSEL:
				MIDI_VCALL(song_sel, snk, evt->song.number);
				break;

			case MIDI_SYSTEM_TUNEREQ:
				MIDI_VCALL(tunerq, snk);
				break;

			case MIDI_SYSTEM_SYSEX_END:
				MIDI_VCALL(sysex_end, snk);
				break;

		}

	}

	return 0;

}



/**
 *
 *  Dispatch a realtime MIDI event to the handler
 *
 **/
int midi_dispatch_realtime(uint source, uint event)
{

	if (realtime_handler != NULL)
		return realtime_handler(source, event);

	else
		return -ENOSYS;

}



/**
 *
 *  Decode and dispatch a raw MIDI event
 *
 **/
int midi_dispatch_raw(const midi_rawevent *rev)
{

	if (rev == NULL)
		return -EINVAL;

	midi_event evt;

	int rc = event_decode(&evt, rev);

	if (rc < 0)
		return rc;

	return midi_dispatch(&evt);

}



/**
 *
 *  Set the realtime MIDI event handler
 *
 **/
void midi_realtime_set_handler(midi_fn_realtime handler)
{

	realtime_handler = handler;
}



/**
 *
 *  Get the current realtime MIDI event handler
 *
 **/
midi_fn_realtime midi_realtime_get_handler()
{

	return realtime_handler;

}



/**
 *
 *  Get the number of arguments of a MIDI event,
 * given the MIDI status byte.
 *
 **/
int event_length(uint status)
{

	if (is_midi_channel(status)) {

		switch (status & 0xF0) {

			case MIDI_EVENT_NOTE_OFF:        return 2;
			case MIDI_EVENT_NOTE_ON:         return 2;
			case MIDI_EVENT_AFTERTOUCH_POLY: return 2;
			case MIDI_EVENT_CONTROL_CHANGE:  return 2;
			case MIDI_EVENT_PROGRAM_CHANGE:  return 1;
			case MIDI_EVENT_AFTERTOUCH_MONO: return 1;
			case MIDI_EVENT_PITCHBEND:       return 2;

		}

	} else if (is_midi_system(status)) {

		switch (status) {

			case MIDI_SYSTEM_SYSEX_DATA: return 1;
			case MIDI_SYSTEM_TCQF:       return 1;
			case MIDI_SYSTEM_SONGPOS:    return 2;
			case MIDI_SYSTEM_SONGSEL:    return 1;
			case MIDI_SYSTEM_TUNEREQ:    return 0;
			case MIDI_SYSTEM_SYSEX_END:  return 0;

		}

	} else if (is_midi_realtime(status))
		return 0;

	return -EINVAL;

}



/**
 *
 *  Decode a raw event and parse its arguments.
 *  Returns 0 if the event is valid, otherwise -EINVAL
 *
 **/
int event_decode(midi_event *evt, const midi_rawevent *rev)
{

	if (is_midi_channel(rev->status)) {

		switch (rev->status & 0xF0) {

			case MIDI_EVENT_NOTE_OFF:
			case MIDI_EVENT_NOTE_ON:
				evt->note.channel  = rev->status & 0x0F;
				evt->note.key      = rev->data[0];
				evt->note.velocity = rev->data[1];
				break;

			case MIDI_EVENT_AFTERTOUCH_POLY:
				evt->type   = rev->status & 0xF0;
				evt->aftertouch.channel  = rev->status & 0x0F;
				evt->aftertouch.key      = rev->data[0];
				evt->aftertouch.pressure = rev->data[1];
				break;

			case MIDI_EVENT_CONTROL_CHANGE:
				evt->control.channel = rev->status & 0x0F;
				evt->control.id      = rev->data[0];
				evt->control.value   = rev->data[1];
				break;

			case MIDI_EVENT_PROGRAM_CHANGE:
				evt->program.channel = rev->status & 0x0F;
				evt->program.number  = rev->data[0];
				break;

			case MIDI_EVENT_AFTERTOUCH_MONO:
				evt->aftertouch.channel  = rev->status & 0x0F;
				evt->aftertouch.key      = -1;
				evt->aftertouch.pressure = rev->data[0];
				break;

			case MIDI_EVENT_PITCHBEND:
				evt->pitchbend.channel = rev->status & 0x0F;
				evt->pitchbend.amount  = rev->data[0] + rev->data[1] * 128;
				break;

			default:
				return -EINVAL;

		}

		evt->type = rev->status & 0xF0;

	} else if (is_midi_system(rev->status)) {

		switch (rev->status) {

			case MIDI_SYSTEM_SYSEX_DATA:
				evt->sysex.data = rev->data[0];
				break;

			case MIDI_SYSTEM_TCQF:
				evt->tcqf.code  = (rev->data[0] & 0x70) >> 4;
				evt->tcqf.value = (rev->data[0] & 0x0f) >> 0;
				break;

			case MIDI_SYSTEM_SONGPOS:
				evt->song.position = 6 * (rev->data[0] + rev->data[1] * 128);
				break;

			case MIDI_SYSTEM_SONGSEL:
				evt->song.number = rev->data[0];
				break;

			case MIDI_SYSTEM_TUNEREQ:
			case MIDI_SYSTEM_SYSEX_END:
				break;

			default:
				return -EINVAL;

		}

		evt->type = rev->status;

	} else
		return -EINVAL;

	evt->source = rev->src_id;
	evt->revent = *rev;

	return 0;

}

