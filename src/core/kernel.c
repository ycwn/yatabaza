

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/unistd.h>

#include "stm32f1xx_hal.h"

#include "core/types.h"
#include "core/console.h"
#include "core/kernel.h"



int main()
{

	HAL_Init();

	printk("Yatabaza Core initialization complete\n");

	while (1)
	{
	}

}



void panic()
{

	while (1);

}



void SysTick_Handler()
{

	HAL_IncTick();

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



void SVC_Handler() //???
{

	panic();

}



void DebugMon_Handler() //SIGTRAP
{

	panic();

}



void PendSV_Handler()
{

	panic();

}

