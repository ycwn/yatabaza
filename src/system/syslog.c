

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>

#include <sys/stat.h>

#include "stm32f1xx_hal.h"

#include "core/types.h"
#include "core/console.h"
#include "core/service.h"
#include "core/device.h"


static int  syslog_create();
static int  syslog_start();
static int  syslog_stop();
static void syslog_handler_uart(char ch);
static void syslog_handler_loop(char ch);


SERVICE_DEF(cpuclk);

SERVICE(syslog,

	SERVICE_CREATE(syslog_create),
	SERVICE_START( syslog_start),
	SERVICE_STOP(  syslog_stop),

	SERVICE_DESCRIPTION("System console"),

	SERVICE_DEPENDS(
		SERVICE_DEP(cpuclk)
	)

);

union syslog_sink {

	UART_HandleTypeDef uart;
	int                loop;

};


static union syslog_sink syslog_sink;



int syslog_create()
{

	// Early logging goes to loopback
	syslog_sink.loop = open("/dev/loop", O_RDWR | O_TRUNC | O_EXCL, 0);

	if (syslog_sink.loop < 0)
		return -EBUSY;

	console_set_handler(&syslog_handler_loop);
	return 0;

}



int syslog_start()
{

	GPIO_InitTypeDef gpio_rx;
	GPIO_InitTypeDef gpio_tx;

	gpio_tx.Pin   = GPIO_PIN_9;
	gpio_tx.Mode  = GPIO_MODE_AF_PP;
	gpio_tx.Speed = GPIO_SPEED_HIGH;
	gpio_tx.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpio_tx);

	gpio_rx.Pin   = GPIO_PIN_10;
	gpio_rx.Mode  = GPIO_MODE_AF_OD;
	gpio_rx.Speed = GPIO_SPEED_HIGH;
	gpio_rx.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpio_rx);

	int loopfd = syslog_sink.loop;

	memset(&syslog_sink.uart, 0, sizeof(syslog_sink.uart));

	syslog_sink.uart.Instance        = USART1;
	syslog_sink.uart.Init.BaudRate   = 115200;
	syslog_sink.uart.Init.WordLength = UART_WORDLENGTH_8B;
	syslog_sink.uart.Init.StopBits   = UART_STOPBITS_1;
	syslog_sink.uart.Init.Parity     = UART_PARITY_NONE;
	syslog_sink.uart.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	syslog_sink.uart.Init.Mode       = UART_MODE_TX_RX;

	if (HAL_UART_Init(&syslog_sink.uart) != HAL_OK)
		return -EIO;

	char ch;

	while (read(loopfd, &ch, sizeof(ch)) > 0)
		syslog_handler_uart(ch);

	console_set_handler(&syslog_handler_uart);
	close(loopfd);

	return 0;

}



int syslog_stop()
{

	console_set_handler(NULL);
	return 0;

}



void syslog_handler_uart(char ch)
{

	HAL_UART_Transmit(&syslog_sink.uart, (u8*)&ch, sizeof(ch), HAL_MAX_DELAY);

}



void syslog_handler_loop(char ch)
{

	write(syslog_sink.loop, &ch, sizeof(ch));

}

