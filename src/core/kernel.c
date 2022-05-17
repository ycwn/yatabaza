

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/unistd.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stm32f1xx_hal.h"

#include "core/types.h"
#include "core/console.h"
#include "core/kernel.h"
#include "core/service.h"



void init(void *args)
{

	services_create();

	printk("Yatabaza Core initialization complete\n");

	services_start();

	while (1) {
	}

	reboot(RB_HALT_SYSTEM);

}



void main()
{

	HAL_Init();
	
	xTaskCreate(
		&init,
		"init",
		256,
		NULL,
		tskIDLE_PRIORITY,
		NULL
	);

	vTaskStartScheduler();

}



void panic()
{

	vTaskSuspendAll();
	while (1);

}



int reboot(int cmd)
{

	if (cmd != RB_HALT_SYSTEM && cmd != RB_POWER_OFF && cmd != RB_AUTOBOOT)
		return -EINVAL;

	services_stop();
	services_destroy();

	vTaskSuspendAll();

	switch (cmd) {

		case RB_HALT_SYSTEM:
			printk("System halted.\n");
			break;

		case RB_POWER_OFF:
			printk("Power down.\n");
			// Write GPIO to power down here.
			break;

		case RB_AUTOBOOT:
			printk("Restarting system.\n");
			NVIC_SystemReset();
			break;

	}

	panic();

}



/**
 *
 *  Override the HAL_Delay() function that used by the
 * lower levels of the HAL, so that it takes into
 * acount FreeRTOS's task management
 *
 **/
void HAL_Delay(uint32_t msec)
{

	vTaskDelay(msec);

}



/**
 *
 * Call HAL_IncTick() from FreeRTOS's tick hook,
 * so that HAL keeps its timer updated.
 *
 **/
void vApplicationTickHook()
{

	HAL_IncTick();

}



void NMI_Handler()
{

	panic();

}



void HardFault_Handler() //SIGABRT
{

	panic();

}



void MemManage_Handler() //SIGSEGV
{

	panic();

}



void BusFault_Handler() //SIGBUS
{

	panic();

}



void UsageFault_Handler() //SIGILL
{

	panic();

}



void DebugMon_Handler() //SIGTRAP
{

	panic();

}



void vApplicationStackOverflowHook(TaskHandle_t task, char *name)
{
}

