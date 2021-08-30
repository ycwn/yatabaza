

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




int main()
{

	HAL_Init();

	services_create();

	printk("Yatabaza Core initialization complete\n");

	services_start();

	while (1)
	{
	}

	services_stop();
	services_destroy();

}



void panic()
{

	while (1);

}



void SysTick_Handler()
{

	HAL_IncTick();
	xPortSysTickHandler();

}



void NMI_Handler()
{

	panic();

}



void HardFault_Handler() //ABRT
{

	panic();

}



void MemManage_Handler() //SEGV
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

