

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>

#include "stm32f1xx_hal.h"

#include "core/types.h"
#include "core/algorithm.h"
#include "core/list.h"
#include "core/console.h"
#include "core/service.h"

#include "synth/midi.h"


static int  midi_io_start();
static int  midi_io_stop();
static void midi_io_recv();
static void midi_io_write(void *ptr, const u8 *buf, uint len);


SERVICE_DEF(cpuclk);
SERVICE_DEF(midi);

SERVICE(midi_io,

	SERVICE_START(midi_io_start),
	SERVICE_STOP( midi_io_stop),

	SERVICE_DESCRIPTION("MIDI I/O interface"),

	SERVICE_DEPENDS(
		cpuclk,
		midi
	)
);


static UART_HandleTypeDef uart;
static midi_source        uart_source;
static midi_drain         uart_drain;
static u8                 buffer[1];



int midi_io_start()
{

	GPIO_InitTypeDef gpio_rx = { 0 };
	GPIO_InitTypeDef gpio_tx = { 0 };

	gpio_tx.Pin   = GPIO_PIN_10;
	gpio_tx.Mode  = GPIO_MODE_AF_PP;
	gpio_tx.Speed = GPIO_SPEED_HIGH;
	gpio_tx.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &gpio_tx);

	gpio_rx.Pin   = GPIO_PIN_11;
	gpio_rx.Mode  = GPIO_MODE_AF_OD;
	gpio_rx.Speed = GPIO_SPEED_HIGH;
	gpio_rx.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &gpio_rx);

	memset(&uart, 0, sizeof(uart));

	uart.Instance        = USART3;
	uart.Init.BaudRate   = 31250;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.StopBits   = UART_STOPBITS_1;
	uart.Init.Parity     = UART_PARITY_NONE;
	uart.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	uart.Init.Mode       = UART_MODE_TX_RX;

	if (HAL_UART_Init(&uart) != HAL_OK)
		return -EIO;


	midi_drain_init(&uart_drain);

	uart_drain.channels = MIDI_ALL;
	uart_drain.write    = &midi_io_write;

	midi_drain_register(&uart_drain);


	midi_source_init(&uart_source);

	HAL_UART_RegisterCallback(&uart, HAL_UART_RX_COMPLETE_CB_ID, &midi_io_recv);
	HAL_UART_Receive_IT(&uart, buffer, sizeof(buffer));

	return 0;

}



int midi_io_stop()
{

	HAL_UART_UnRegisterCallback(&uart, HAL_UART_RX_COMPLETE_CB_ID);
	midi_drain_unregister(&uart_drain);

	return 0;

}



void midi_io_recv()
{

	midi_source_recv(&uart_source, buffer[0]);
	HAL_UART_Receive_IT(&uart, buffer, sizeof(buffer));

}



void midi_io_write(void *ptr, const u8 *buf, uint len)
{

	HAL_UART_Transmit(&uart, (u8*)buf, len, HAL_MAX_DELAY);

}

