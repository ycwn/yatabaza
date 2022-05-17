
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


#define configUSE_PREEMPTION       1
#define configUSE_IDLE_HOOK        0
#define configUSE_TICK_HOOK        1
#define configCPU_CLOCK_HZ         72000000UL
#define configTICK_RATE_HZ         (TickType_t)1000
#define configMAX_PRIORITIES       5
#define configMINIMAL_STACK_SIZE   64
#define configTOTAL_HEAP_SIZE      15360
#define configMAX_TASK_NAME_LEN    8
#define configUSE_TRACE_FACILITY   1
#define configUSE_16_BIT_TICKS     0
#define configIDLE_SHOULD_YIELD    1

#define configUSE_CO_ROUTINES             0
#define configMAX_CO_ROUTINE_PRIORITIES   2

#define configUSE_MUTEXES                 1
#define configUSE_COUNTING_SEMAPHORES     1
#define configUSE_ALTERNATIVE_API         0
#define configCHECK_FOR_STACK_OVERFLOW    2
#define configUSE_RECURSIVE_MUTEXES       1
#define configQUEUE_REGISTRY_SIZE         0
#define configGENERATE_RUN_TIME_STATS     0
#define configUSE_APPLICATION_TASK_TAG    0
#define configSUPPORT_STATIC_ALLOCATION   0
#define configSUPPORT_DYNAMIC_ALLOCATION  1


#define INCLUDE_vTaskPrioritySet           1
#define INCLUDE_uxTaskPriorityGet          1
#define INCLUDE_vTaskDelete                1
#define INCLUDE_vTaskCleanUpResources      0
#define INCLUDE_vTaskSuspend               1
#define INCLUDE_vTaskDelayUntil            1
#define INCLUDE_vTaskDelay                 1
#define INCLUDE_xTaskGetSchedulerState     1
#define INCLUDE_xTaskGetCurrentTaskHandle  1


#define configKERNEL_INTERRUPT_PRIORITY          255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     191
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY   15


#define xPortPendSVHandler   PendSV_Handler
#define vPortSVCHandler      SVC_Handler
#define xPortSysTickHandler  SysTick_Handler


#endif

