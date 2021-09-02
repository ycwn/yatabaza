

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

#include "synth/opl_io.h"


enum {
	MCP23017_BASE_ADDR  = 0x20,
	SYNTH_OPL2_COUNT    = SYNTH_OPL_LAST - SYNTH_OPL_FIRST + 1
};

enum {
	MCP23017_REG_IOCON_BANK0 = 0x0a,
	MCP23017_REG_IOCON_BANK1 = 0x05
};

enum {
	MCP23017_REG_IODIR   = 0x00,
	MCP23017_REG_IPOL    = 0x02,
	MCP23017_REG_GPINTEN = 0x04,
	MCP23017_REG_DEFVAL  = 0x06,
	MCP23017_REG_INTCON  = 0x08,
	MCP23017_REG_GPPU    = 0x0c,
	MCP23017_REG_INTF    = 0x0e,
	MCP23017_REG_INTCAP  = 0x10,
	MCP23017_REG_GPIO    = 0x12,
	MCP23017_REG_OLAT    = 0x14
};

enum {
	MCP23017_PORT_A = 0,
	MCP23017_PORT_B = 1
};

#define MCP23017_REG(r, p) ((MCP23017_REG_##r) | (p))



/**
 * Expander port configuration
 **/
enum {
	PORT_DATA = MCP23017_PORT_A,
	PORT_CTRL = MCP23017_PORT_B
};


/**
 * Expander control pin configuration
 **/
enum {
	PIN_A0 = 0,
	PIN_CS = 3,
	PIN_RD = 2,
	PIN_WR = 1,
	PIN_RS = 7
};

enum {
	CTRL_IDLE  = (0 << PIN_A0) | (1 << PIN_CS) | (1 << PIN_RD) | (1 << PIN_WR) | (1 << PIN_RS),
	CTRL_RESET = (0 << PIN_A0) | (1 << PIN_CS) | (1 << PIN_RD) | (1 << PIN_WR) | (0 << PIN_RS),
	CTRL_D_RD  = (0 << PIN_A0) | (0 << PIN_CS) | (0 << PIN_RD) | (1 << PIN_WR) | (1 << PIN_RS),
	CTRL_D_WR  = (1 << PIN_A0) | (0 << PIN_CS) | (1 << PIN_RD) | (0 << PIN_WR) | (1 << PIN_RS),
	CTRL_R_WR  = (0 << PIN_A0) | (0 << PIN_CS) | (1 << PIN_RD) | (0 << PIN_WR) | (1 << PIN_RS)
};


static int opl_io_start();
static int opl_io_stop();


SERVICE_DEF(bus);

SERVICE(opl_io,

	SERVICE_START(opl_io_start),
	SERVICE_START(opl_io_stop),

	SERVICE_DESCRIPTION("OPL I/O core"),

	SERVICE_DEPENDS(
		SERVICE_DEP(bus)
	)

);

static u8 devices = 0x00;  // initialized devices
static u8 locked  = 0x00;  // locked devices


static inline void device_set_enabled(   uint dev) { devices |= 1 << dev; }
static inline void device_set_disabled(  uint dev) { devices &= ~(1 << dev); }
static inline bool device_is_initialized(uint dev) { return devices & (1 << dev); }

static inline void device_set_locked(  uint dev) { locked |= 1 << dev; }
static inline void device_set_unlocked(uint dev) { locked &= ~(1 << dev); }
static inline bool device_is_locked(   uint dev) { return locked & (1 << dev); }



/**
 *
 * Initialize any device on the bus.
 *
 **/
int opl_io_start()
{

	devices = 0x00;
	locked  = 0x00;

	for (uint dev=SYNTH_OPL_FIRST; dev <= SYNTH_OPL_LAST; dev++)
		opl_io_init(dev);

	for (uint dev=SYNTH_OPL_FIRST; dev <= SYNTH_OPL_LAST; dev++)
		opl_io_reset(dev);

	return 0;

}



/**
 *
 * Reset all known devices
 *
 **/
int opl_io_stop()
{

	for (uint dev=SYNTH_OPL_FIRST; dev <= SYNTH_OPL_LAST; dev++)
		opl_io_reset(dev);

	devices = 0x00;
	locked  = 0x00;

	return 0;

}



/**
 *
 * Initialize a device. This will set the access mode of
 * the MCP23017 bus expander to 16bit without increment,
 * so that both ports can be updated in a single bus
 * transation. After initialization, the device is kept
 * in reset state, by asserting its /RST line.
 *
 **/
int opl_io_init(uint dev)
{

	if (dev < SYNTH_OPL_FIRST || dev > SYNTH_OPL_LAST)
		return -EINVAL;

	device_set_disabled(dev);

	addr_t addr = MCP23017_BASE_ADDR + dev;

	if (bus_ping(addr) < 0)
		return -ENOENT;

	bool init =
		(bus_write_r8_u8(addr, MCP23017_REG_IOCON_BANK1,       0x00)       >= 0) &&  // Make sure the banks are setup correctly
		(bus_write_r8_u8(addr, MCP23017_REG_IOCON_BANK0,       0x24)       >= 0) &&  // Set 16bit mode (BANK=0), no increment (SEQOP=1)
		(bus_write_r8_u8(addr, MCP23017_REG(GPIO,  PORT_DATA), 0x00)       >= 0) &&  // Clear data port
		(bus_write_r8_u8(addr, MCP23017_REG(GPIO,  PORT_CTRL), CTRL_RESET) >= 0) &&  // Set control port to reset condition
		(bus_write_r8_u8(addr, MCP23017_REG(IODIR, PORT_DATA), 0x00)       >= 0) &&  // Set data port to output
		(bus_write_r8_u8(addr, MCP23017_REG(IODIR, PORT_CTRL), 0x00)       >= 0);    // Set control port to output

	if (!init)
		return -EIO;

	device_set_enabled(dev);

	return 0;

}



/**
 *
 * Reset a device by asserting its /RST line
 *
 **/
int opl_io_reset(uint dev)
{

	if (dev < SYNTH_OPL_FIRST || dev > SYNTH_OPL_LAST)
		return -EINVAL;

	if (!device_is_initialized(dev))
		return -ENOENT;

	addr_t addr = MCP23017_BASE_ADDR + dev;

	if (bus_write_r8_u8(addr, MCP23017_REG(GPIO,  PORT_CTRL), CTRL_RESET) < 0)
		return -EIO;

	HAL_Delay(100);

	if (bus_write_r8_u8(addr, MCP23017_REG(GPIO,  PORT_CTRL), CTRL_IDLE) < 0)
		return -EIO;

	return 0;

}



/**
 *
 * Set the lock bit on a device
 *
 **/
int opl_io_lock(uint dev)
{

	if (dev < SYNTH_OPL_FIRST || dev > SYNTH_OPL_LAST)
		return -EINVAL;

	if (!device_is_initialized(dev))
		return -ENOENT;

	device_set_locked(dev);
	return 0;

}



/**
 *
 * Clear the lock bit on a device
 *
 **/
int opl_io_unlock(uint dev)
{

	if (dev < SYNTH_OPL_FIRST || dev > SYNTH_OPL_LAST)
		return -EINVAL;

	if (!device_is_initialized(dev))
		return -ENOENT;

	device_set_unlocked(dev);
	return 0;
}



/**
 *
 * Check the status of the lock bit of a device
 *
 **/
int opl_io_is_locked(uint dev)
{

	if (dev < SYNTH_OPL_FIRST || dev > SYNTH_OPL_LAST)
		return -EINVAL;

	if (!device_is_initialized(dev))
		return -ENOENT;

	return device_is_locked(dev)? 1: 0;

}



/**
 *
 * Read the status register of a device
 *
 **/
int opl_io_read(uint dev)
{

	if (dev < SYNTH_OPL_FIRST || dev > SYNTH_OPL_LAST)
		return -EINVAL;

	if (!device_is_initialized(dev))
		return -ENOENT;

	addr_t addr = MCP23017_BASE_ADDR + dev;

	u8   status = 0;
	bool read =
		(bus_write_r8_u8(addr, MCP23017_REG(IODIR, PORT_DATA), 0xff)      >= 0) &&  // Set data port to input
		(bus_write_r8_u8(addr, MCP23017_REG(GPIO,  PORT_DATA), 0x00)      >= 0) &&
		(bus_write_r8_u8(addr, MCP23017_REG(GPIO,  PORT_CTRL), CTRL_D_RD) >= 0) &&  // Set A0, assert /RD and /CS
		(bus_read_r8_u8( addr, MCP23017_REG(GPIO,  PORT_DATA), &status)   >= 0) &&  // Read the status register
		(bus_write_r8_u8(addr, MCP23017_REG(GPIO,  PORT_CTRL), CTRL_IDLE) >= 0) &&
		(bus_write_r8_u8(addr, MCP23017_REG(IODIR, PORT_DATA), 0x00)      >= 0);

	return read? status: -EIO;

}



/**
 *
 * Perform a series of writes to a device. To maximize performance,
 * a buffer is constructed that contains the data to send, and the
 * bus control signals.
 *
 **/
int opl_io_write8(uint dev, const u8 *reg, const u8 *val, uint num)
{

	if (dev < SYNTH_OPL_FIRST || dev > SYNTH_OPL_LAST)
		return -EINVAL;

	if (!device_is_initialized(dev))
		return -ENOENT;

	addr_t addr = MCP23017_BASE_ADDR + dev;

	u8 buf[8 * num];

	for (int n=0, p=0; n < num; n++) {

		buf[p++] = reg[n];     // Send register address on data port
		buf[p++] = CTRL_R_WR;  // Now assert /CS and /WR
		buf[p++] = reg[n];
		buf[p++] = CTRL_IDLE;

		buf[p++] = val[n];     // Send value on data port
		buf[p++] = CTRL_D_WR;  // Set A0, assert /CS and /WR
		buf[p++] = val[n];
		buf[p++] = CTRL_IDLE;

	}

	return bus_write_r8_buf(addr, MCP23017_REG(GPIO, PORT_DATA), buf, sizeof(buf));

}

