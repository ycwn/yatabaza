

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


static int cpuclk_start();


SERVICE(cpuclk,

	SERVICE_START(cpuclk_start),

	SERVICE_DESCRIPTION("CPU and system clock")

);



/**
 *
 * Initialize the CPU's clock, and enable various peripherals
 *
 **/
int cpuclk_start()
{

	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_DMA1_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	__HAL_RCC_I2C1_CLK_ENABLE();

	__HAL_RCC_USART1_CLK_ENABLE();

 	__HAL_RCC_TIM1_CLK_ENABLE();
 	__HAL_RCC_TIM2_CLK_ENABLE();

	__HAL_AFIO_REMAP_SWJ_DISABLE();

	RCC_OscInitTypeDef osc = { 0 };

	osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc.HSEState       = RCC_HSE_ON;
	osc.HSIState       = RCC_HSI_OFF;
	osc.PLL.PLLState   = RCC_PLL_ON;
	osc.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
	osc.PLL.PLLMUL     = RCC_PLL_MUL9;

	if (HAL_RCC_OscConfig(&osc) != HAL_OK)
		return -EINVAL;

	RCC_ClkInitTypeDef clk = { 0 };

	clk.ClockType      = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
	clk.AHBCLKDivider  = RCC_SYSCLK_DIV1;
	clk.APB2CLKDivider = RCC_HCLK_DIV1;
	clk.APB1CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2) != HAL_OK)
		return -EINVAL;

	const u32 *device_id = (const u32*)0x1FFFF7E8;

	printk("cpu:\n\t%08x\n\t%08x\n\t%08x\n",
		device_id[0],
		device_id[1],
		device_id[2]);

	return 0;

}

