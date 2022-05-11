

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>

#include "stm32f1xx_hal.h"

#include "core/types.h"
#include "core/algorithm.h"
#include "core/console.h"
#include "core/service.h"

#include "system/bus.h"


#define SDA_PIN        GPIO_PIN_7
#define SDA_GPIO_PORT  GPIOB

#define SCL_PIN        GPIO_PIN_6
#define SCL_GPIO_PORT  GPIOB

#define RST_PIN        GPIO_PIN_9
#define RST_GPIO_PORT  GPIOB

#define IRQ_PIN        GPIO_PIN_8
#define IRQ_GPIO_PORT  GPIOB

#define I2C_DEV           I2C1
#define I2C_XFER_SPEED    400000

#define BUS_RESET_DELAY   100
#define BUS_XFER_TIMEOUT  1000


static int bus_start();
static int bus_stop();
static int hal_error(int status);


SERVICE_DEF(cpuclk);

SERVICE(bus,

	SERVICE_START(bus_start),
	SERVICE_STOP( bus_stop),

	SERVICE_DESCRIPTION("Synth I2C bus"),

	SERVICE_DEPENDS(
		cpuclk
	)
);

static I2C_HandleTypeDef i2c_dev;



/**
 *
 * Initialize the I2C bus
 *
 **/
int bus_start()
{

	GPIO_InitTypeDef gpio_sda = { 0 };
	GPIO_InitTypeDef gpio_scl = { 0 };
	GPIO_InitTypeDef gpio_rst = { 0 };
	GPIO_InitTypeDef gpio_irq = { 0 };

	gpio_sda.Pin   = SDA_PIN;
	gpio_sda.Mode  = GPIO_MODE_AF_OD;
	gpio_sda.Pull  = GPIO_NOPULL;
	gpio_sda.Speed = GPIO_SPEED_FREQ_HIGH;

	gpio_scl.Pin   = SCL_PIN;
	gpio_scl.Mode  = GPIO_MODE_AF_OD;
	gpio_scl.Pull  = GPIO_NOPULL;
	gpio_scl.Speed = GPIO_SPEED_FREQ_HIGH;

	gpio_rst.Pin   = RST_PIN;
	gpio_rst.Mode  = GPIO_MODE_OUTPUT_PP;
	gpio_rst.Pull  = GPIO_NOPULL;
	gpio_rst.Speed = GPIO_SPEED_FREQ_HIGH;

	gpio_irq.Pin   = IRQ_PIN;
	gpio_irq.Mode  = GPIO_MODE_INPUT;
	gpio_irq.Pull  = GPIO_NOPULL;
	gpio_irq.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(SDA_GPIO_PORT, &gpio_sda);
	HAL_GPIO_Init(SCL_GPIO_PORT, &gpio_scl);
	HAL_GPIO_Init(RST_GPIO_PORT, &gpio_rst);
	HAL_GPIO_Init(IRQ_GPIO_PORT, &gpio_irq);

	HAL_GPIO_WritePin(RST_GPIO_PORT, RST_PIN, GPIO_PIN_RESET);

	memset(&i2c_dev, 0, sizeof(i2c_dev));

	i2c_dev.Instance            = I2C_DEV;
	i2c_dev.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c_dev.Init.ClockSpeed     = I2C_XFER_SPEED;
	i2c_dev.Init.DutyCycle      = I2C_DUTYCYCLE_2;

	if (HAL_I2C_Init(&i2c_dev) != HAL_OK)
		return -EIO;

	bus_reset();
	return 0;

}



/**
 *
 * Disable the I2C bus
 *
 **/
int bus_stop()
{

	HAL_GPIO_WritePin(RST_GPIO_PORT, RST_PIN, GPIO_PIN_RESET);
	return 0;

}



/**
 *
 * Reset all the devices on the I2C bus
 *
 **/
void bus_reset()
{

	HAL_GPIO_WritePin(RST_GPIO_PORT, RST_PIN, GPIO_PIN_RESET);
	HAL_Delay(BUS_RESET_DELAY);
	HAL_GPIO_WritePin(RST_GPIO_PORT, RST_PIN, GPIO_PIN_SET);

}



/**
 *
 * Ping a I2C device given its address by reading a single byte
 *
 **/
int bus_ping(addr_t addr)
{

	u8     tmp;
	return bus_read_u8(addr, &tmp);

}



/**
 *
 * Scan the I2C bus, by pinging all the devices in the given range.
 * The results are appended to an array, and the number of devices
 * found is returned.
 *
 **/
int bus_scan_list(addr_t *addrs, uint num, addr_t start, addr_t end)
{

	int count = 0;

	for (addr_t addr=start; addr <= end; addr++) {

		int r = bus_ping(addr);

		if (r >= 0) {

			if (addrs != NULL && count < num)
				addrs[count] = addr;

			count++;

		}

	}

	return count;

}



/**
 *
 * Read the specified number of bytes from an I2C device
 *
 **/
int bus_read_buf(addr_t addr, void *buf, size_t num)
{

	return hal_error(HAL_I2C_Master_Receive(&i2c_dev, addr << 1, buf, num, BUS_XFER_TIMEOUT));

}



/**
 *
 * Write the specified number of bytes to an I2C device
 *
 **/
int bus_write_buf(addr_t addr, const void *buf, size_t num)
{

	return hal_error(HAL_I2C_Master_Transmit(&i2c_dev, addr << 1, (u8*)buf, num, BUS_XFER_TIMEOUT));

}



/**
 *
 * Read the specified number of bytes from a register of an I2C device.
 * The register's address is first sent to the device as an 8-bit number,
 * then a read operation is initiated.
 *
 **/
int bus_read_r8_buf(addr_t addr, u8 reg, void *buf, size_t num)
{

	return hal_error(HAL_I2C_Mem_Read(&i2c_dev, addr << 1, reg, I2C_MEMADD_SIZE_8BIT, buf, num, BUS_XFER_TIMEOUT));

}



/**
 *
 * Write the specified number of bytes to a register of an I2C device.
 * The register's address is first sent to the device as an 8-bit number,
 * then a write operation is initiated.
 *
 **/
int bus_write_r8_buf(addr_t addr, u8 reg, const void *buf, size_t num)
{

	return hal_error(HAL_I2C_Mem_Write(&i2c_dev, addr << 1, reg, I2C_MEMADD_SIZE_8BIT, (u8*)buf, num, BUS_XFER_TIMEOUT));

}



/**
 *
 * Read the specified number of bytes from a register of an I2C device.
 * The register's address is first sent to the device as an 16-bit number,
 * then a read operation is initiated.
 *
 **/
int bus_read_r16_buf(addr_t addr, u16 reg, void *buf, size_t num)
{

	return hal_error(HAL_I2C_Mem_Read(&i2c_dev, addr << 1, reg, I2C_MEMADD_SIZE_16BIT, buf, num, BUS_XFER_TIMEOUT));

}



/**
 *
 * Write the specified number of bytes to a register of an I2C device.
 * The register's address is first sent to the device as an 16-bit number,
 * then a write operation is initiated.
 *
 **/
int bus_write_r16_buf(addr_t addr, u16 reg, const void *buf, size_t num)
{

	return hal_error(HAL_I2C_Mem_Write(&i2c_dev, addr << 1, reg, I2C_MEMADD_SIZE_16BIT, (u8*)buf, num, BUS_XFER_TIMEOUT));

}



/**
 *
 * Translate a HAL error code to its POSIX equivalent.
 *
 **/
int hal_error(int status)
{

	switch (status) {

		case HAL_OK:      return 0;
		case HAL_ERROR:   return -EIO;
		case HAL_BUSY:    return -EBUSY;
		case HAL_TIMEOUT: return -ETIMEDOUT;

		default:
			return -EFAULT;

	}

}
