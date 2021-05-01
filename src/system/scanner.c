

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>

#include "stm32f1xx_hal.h"

#include "core/types.h"
#include "core/console.h"
#include "core/service.h"

#include "system/bus.h"


static int scanner_start();


SERVICE_DEF(bus);
SERVICE_DEF(syslog);

SERVICE(scanner,

	SERVICE_START(scanner_start),

	SERVICE_DESCRIPTION("Synth I2C bus scan"),
	SERVICE_DEPENDS(
		SERVICE_DEP(bus),
		SERVICE_DEP(syslog)
	)
);



/**
 *
 * Scan the I2C bus and list all attached devices
 *
 **/
int scanner_start()
{

	int num = 0;

	printk("\t      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");

	for (addr_t addr=0; addr < 128; addr++) {

		if ((addr & 0x0f) == 0)
			printk("\t%02x: ", addr);

		if (bus_ping(addr) >= 0) {

			printk(" %02x", addr);
			num++;

		} else
			printk(" --");

		if ((addr & 0x0f) == 0x0f)
			printk("\n");

	}

	printk("scanner: %d devices detected\n", num);
	return 0;

}

