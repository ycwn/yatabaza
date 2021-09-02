

#ifndef SYNTH_MIDI_H
#define SYNTH_MIDI_H


enum {

	MIDI_EVENT_NOTE_OFF        = 0x80,
	MIDI_EVENT_NOTE_ON         = 0x90,
	MIDI_EVENT_AFTERTOUCH_POLY = 0xA0,
	MIDI_EVENT_CONTROL_CHANGE  = 0xB0,
	MIDI_EVENT_PROGRAM_CHANGE  = 0xC0,
	MIDI_EVENT_AFTERTOUCH_MONO = 0xD0,
	MIDI_EVENT_PITCHBEND       = 0xE0,

	MIDI_SYSTEM_SYSEX_DATA = 0xF0,
	MIDI_SYSTEM_TCQF       = 0xF1,
	MIDI_SYSTEM_SONGPOS    = 0xF2,
	MIDI_SYSTEM_SONGSEL    = 0xF3,
	MIDI_SYSTEM_TUNEREQ    = 0xF6,
	MIDI_SYSTEM_SYSEX_END  = 0xF7,

	MIDI_REALTIME_CLOCK    = 0xF8,
	MIDI_REALTIME_TICK     = 0xF9,
	MIDI_REALTIME_START    = 0xFA,
	MIDI_REALTIME_CONTINUE = 0xFB,
	MIDI_REALTIME_STOP     = 0xFC,
	MIDI_REALTIME_ACTSENSE = 0xFE,
	MIDI_REALTIME_RESET    = 0xFF

};

enum {

	MIDI_TIMECODE_FRAME_LS     = 0,
	MIDI_TIMECODE_FRAME_MS     = 1,
	MIDI_TIMECODE_SECONDS_LS   = 2,
	MIDI_TIMECODE_SECONDS_MS   = 3,
	MIDI_TIMECODE_MINUTES_LS   = 4,
	MIDI_TIMECODE_MINUTES_MS   = 5,
	MIDI_TIMECODE_HOURS_LS     = 6,
	MIDI_TIMECODE_HOURS_MS_FPS = 7,

	MIDI_TIMECODE_FPS_24    = 0x00,
	MIDI_TIMECODE_FPS_25    = 0x02,
	MIDI_TIMECODE_FPS_29_97 = 0x04,
	MIDI_TIMECODE_FPS_30    = 0x06,

	MIDI_TIMECODE_HOURS_MS_MASK = 0x01,
	MIDI_TIMECODE_FPS_MASK      = 0x06,


};

enum {

	MIDI_CH01 = 1 <<  0,
	MIDI_CH02 = 1 <<  1,
	MIDI_CH03 = 1 <<  2,
	MIDI_CH04 = 1 <<  3,
	MIDI_CH05 = 1 <<  4,
	MIDI_CH06 = 1 <<  5,
	MIDI_CH07 = 1 <<  6,
	MIDI_CH08 = 1 <<  7,
	MIDI_CH09 = 1 <<  8,
	MIDI_CH10 = 1 <<  9,
	MIDI_CH11 = 1 << 10,
	MIDI_CH12 = 1 << 11,
	MIDI_CH13 = 1 << 12,
	MIDI_CH14 = 1 << 13,
	MIDI_CH15 = 1 << 14,
	MIDI_CH16 = 1 << 15,

	MIDI_SYSTEM = 1 << 24,

	MIDI_CH_ALL =
		MIDI_CH01 | MIDI_CH02 | MIDI_CH03 | MIDI_CH04 |
		MIDI_CH05 | MIDI_CH06 | MIDI_CH07 | MIDI_CH08 |
		MIDI_CH09 | MIDI_CH10 | MIDI_CH11 | MIDI_CH12 |
		MIDI_CH13 | MIDI_CH14 | MIDI_CH15 | MIDI_CH16,

	MIDI_ALL = MIDI_CH_ALL | MIDI_SYSTEM

};


struct midi_event;
struct midi_source;
struct midi_drain;

typedef void (*midi_fn_start)(void *ptr);
typedef void (*midi_fn_stop)(void *ptr);

typedef void (*midi_fn_write)(void *ptr, const u8 *buf, uint len);
typedef void (*midi_fn_event)(void *ptr, const struct midi_event *evt);

typedef void (*midi_fn_note)(void *ptr, int channel, int key, int velocity);
typedef void (*midi_fn_note_on)(void *ptr, int channel, int key, int velocity);
typedef void (*midi_fn_note_off)(void *ptr, int channel, int key, int velocity);
typedef void (*midi_fn_aftertouch)(void *ptr, int channel, int key, int pressure);
typedef void (*midi_fn_aftertouch_poly)(void *ptr, int channel, int key, int pressure);
typedef void (*midi_fn_aftertouch_mono)(void *ptr, int channel, int pressure);
typedef void (*midi_fn_controller)(void *ptr, int channel, int control, int value);
typedef void (*midi_fn_program)(void *ptr, int channel, int program);
typedef void (*midi_fn_pitchbend)(void *ptr, int channel, int amount);

typedef void (*midi_fn_system_sysex_data)(void *ptr, u8 data);
typedef void (*midi_fn_system_tcqf)(void *ptr, uint code, uint value);
typedef void (*midi_fn_system_songpos)(void *ptr, uint position);
typedef void (*midi_fn_system_songsel)(void *ptr, uint number);
typedef void (*midi_fn_system_tunerq)(void *ptr);
typedef void (*midi_fn_system_sysex_end)(void *ptr);

typedef int (*midi_fn_realtime)(uint source, uint event);



typedef struct midi_rawevent {

	u8 src_id;

	u8 status;
	u8 data[2];

} midi_rawevent;


typedef struct midi_source {

	uint count;
	uint total;

	midi_rawevent revent;

} midi_source;


typedef struct midi_drain {

	list node;

	uint status;
	uint channels;

	midi_fn_start  start;
	midi_fn_stop   stop;

	midi_fn_write  write;
	midi_fn_event  event;

	midi_fn_note             note;
	midi_fn_note_on          note_on;
	midi_fn_note_off         note_off;
	midi_fn_controller       controller;
	midi_fn_program          program;
	midi_fn_aftertouch       aftertouch;
	midi_fn_aftertouch_poly  aftertouch_poly;
	midi_fn_aftertouch_mono  aftertouch_mono;
	midi_fn_pitchbend        pitchbend;

	midi_fn_system_sysex_data  sysex_data;
	midi_fn_system_sysex_end   sysex_end;

	midi_fn_system_tcqf     tcqf;
	midi_fn_system_songpos  song_pos;
	midi_fn_system_songsel  song_sel;
	midi_fn_system_tunerq   tunerq;

	void *ptr;

} midi_drain;


struct midi_event_note {

	uint channel;
	uint key;
	uint velocity;

};


struct midi_event_aftertouch {

	uint channel;
	uint key;
	uint pressure;

};


struct midi_event_control_change {

	uint channel;
	uint id;
	uint value;

};


struct midi_event_program_change {

	uint channel;
	uint number;

};


struct midi_event_pitchbend {

	uint channel;
	uint amount;

};


struct midi_event_sysex_data {

	uint data;

};


struct midi_event_tcqf {

	uint code;
	uint value;

};


union midi_event_song {

	uint position;
	uint number;

};


typedef struct midi_event {

	uint type;
	uint source;

	midi_rawevent revent;

	union {

		struct midi_event_note            note;
		struct midi_event_aftertouch      aftertouch;
		struct midi_event_control_change  control;
		struct midi_event_program_change  program;
		struct midi_event_pitchbend       pitchbend;

		struct midi_event_sysex_data  sysex;
		struct midi_event_tcqf        tcqf;
		union  midi_event_song        song;

	};

} midi_event;


int midi_source_init(midi_source *src);
int midi_source_recv(midi_source *src, u8 data);

int midi_drain_init(midi_drain *snk);
int midi_drain_register(midi_drain *snk);
int midi_drain_unregister(midi_drain *snk);

int midi_pump();
int midi_post(const midi_rawevent *rev);
int midi_dispatch(const midi_event *evt);
int midi_dispatch_raw(const midi_rawevent *rev);
int midi_dispatch_realtime(uint source, uint evt);

void             midi_realtime_set_handler(midi_fn_realtime handler);
midi_fn_realtime midi_realtime_get_handler();


static inline void midi_encode_note_off(midi_rawevent *rev, uint source, uint channel, uint key, uint velocity) {
	rev->src_id  = source;
	rev->status  = MIDI_EVENT_NOTE_OFF | (channel & 15);
	rev->data[0] = key;
	rev->data[1] = velocity;
}

static inline void midi_encode_note_on(midi_rawevent *rev, uint source, uint channel, uint key, uint velocity) {
	rev->src_id  = source;
	rev->status  = ((velocity != 0)? MIDI_EVENT_NOTE_ON: MIDI_EVENT_NOTE_OFF) | (channel & 15);
	rev->data[0] = key;
	rev->data[1] = velocity;
}

static inline void midi_encode_aftertouch_poly(midi_rawevent *rev, uint source, uint channel, uint key, uint pressure) {
	rev->src_id  = source;
	rev->status  = MIDI_EVENT_AFTERTOUCH_POLY | (channel & 15);
	rev->data[0] = key;
	rev->data[1] = pressure;
}

static inline void midi_encode_aftertouch_mono(midi_rawevent *rev, uint source, uint channel, uint pressure) {
	rev->src_id  = source;
	rev->status  = MIDI_EVENT_AFTERTOUCH_MONO | (channel & 15);
	rev->data[0] = pressure;
}

static inline void midi_encode_control_change(midi_rawevent *rev, uint source, uint channel, uint id, uint value) {
	rev->src_id  = source;
	rev->status  = MIDI_EVENT_CONTROL_CHANGE | (channel & 15);
	rev->data[0] = id;
	rev->data[1] = value;
}

static inline void midi_encode_program_change(midi_rawevent *rev, uint source, uint channel, uint number) {
 	rev->src_id  = source;
	rev->status  = MIDI_EVENT_PROGRAM_CHANGE | (channel & 15);
	rev->data[0] = number;
}

static inline void midi_encode_pitchbend(midi_rawevent *rev, uint source, uint channel, uint amount) {
	rev->src_id  = source;
	rev->status  = MIDI_EVENT_PITCHBEND | (channel & 15);
	rev->data[0] = (amount >> 7) & 0x7f;
	rev->data[1] = (amount >> 0) & 0x7f;
}

static inline int midi_post_note_off(uint source, uint channel, uint key, uint velocity) {
	midi_rawevent rev;
	midi_encode_note_off(&rev, source, channel, key, velocity);
	return midi_post(&rev);
}

static inline int midi_post_note_on(uint source, uint channel, uint key, uint velocity) {
	midi_rawevent rev;
	midi_encode_note_on(&rev, source, channel, key, velocity);
	return midi_post(&rev);
}

static inline int midi_post_aftertouch_poly(uint source, uint channel, uint key, uint pressure) {
	midi_rawevent rev;
	midi_encode_aftertouch_poly(&rev, source, channel, key, pressure);
	return midi_post(&rev);
}

static inline int midi_post_aftertouch_mono(uint source, uint channel, uint pressure) {
	midi_rawevent rev;
	midi_encode_aftertouch_mono(&rev, source, channel, pressure);
	return midi_post(&rev);
}

static inline int midi_post_control_change(uint source, uint channel, uint id, uint value) {
	midi_rawevent rev;
	midi_encode_control_change(&rev, source, channel, id, value);
	return midi_post(&rev);
}

static inline int midi_post_program_change(uint source, uint channel, uint number) {
	midi_rawevent rev;
	midi_encode_program_change(&rev, source, channel, number);
	return midi_post(&rev);
}

static inline int midi_post_pitchbend(uint source, uint channel, uint amount) {
	midi_rawevent rev;
	midi_encode_pitchbend(&rev, source, channel, amount);
	return midi_post(&rev);
}

static inline int midi_dispatch_note_off(uint source, uint channel, uint key, uint velocity) {
	midi_rawevent rev;
	midi_encode_note_off(&rev, source, channel, key, velocity);
	return midi_dispatch_raw(&rev);
}

static inline int midi_dispatch_note_on(uint source, uint channel, uint key, uint velocity) {
	midi_rawevent rev;
	midi_encode_note_on(&rev, source, channel, key, velocity);
	return midi_dispatch_raw(&rev);
}

static inline int midi_dispatch_aftertouch_poly(uint source, uint channel, uint key, uint pressure) {
	midi_rawevent rev;
	midi_encode_aftertouch_poly(&rev, source, channel, key, pressure);
	return midi_dispatch_raw(&rev);
}

static inline int midi_dispatch_aftertouch_mono(uint source, uint channel, uint pressure) {
	midi_rawevent rev;
	midi_encode_aftertouch_mono(&rev, source, channel, pressure);
	return midi_dispatch_raw(&rev);
}

static inline int midi_dispatch_control_change(uint source, uint channel, uint id, uint value) {
	midi_rawevent rev;
	midi_encode_control_change(&rev, source, channel, id, value);
	return midi_dispatch_raw(&rev);
}

static inline int midi_dispatch_program_change(uint source, uint channel, uint number) {
	midi_rawevent rev;
	midi_encode_program_change(&rev, source, channel, number);
	return midi_dispatch_raw(&rev);
}

static inline int midi_dispatch_pitchbend(uint source, uint channel, uint amount) {
	midi_rawevent rev;
	midi_encode_pitchbend(&rev, source, channel, amount);
	return midi_dispatch_raw(&rev);
}


#endif


