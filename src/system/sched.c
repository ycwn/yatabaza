

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>

#include "FreeRTOS.h"
#include "task.h"

#include "core/types.h"
#include "core/console.h"
#include "core/service.h"


static int sched_start();
static int sched_stop();


SERVICE_DEF(cpuclk);

SERVICE(sched,

	SERVICE_START(sched_start),
	SERVICE_STOP( sched_stop),

	SERVICE_DESCRIPTION("FreeRTOS scheduler"),
	SERVICE_DEPENDS(
		SERVICE_DEP(sched)
	)

);



/**
 *
 * Start the task scheduler
 *
 **/
int sched_start()
{

	vTaskStartScheduler();
	return 0;

}



/**
 *
 * Stop the task scheduler
 *
 **/
int sched_stop()
{

	vTaskEndScheduler();
	return 0;

}

