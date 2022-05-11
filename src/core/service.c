

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <errno.h>

#include "core/types.h"
#include "core/algorithm.h"
#include "core/vt102.h"
#include "core/console.h"
#include "core/service.h"


#define MSG_PRE         VT102_CUU(1)  VT102_CHA(64)
#define MSG_POST        VT102_SGR_RESET "\n"
#define MSG_LBRACKET    VT102_SGR_COLOR_FG_BRIGHT_BLUE  "[ "
#define MSG_RBRACKET    VT102_SGR_COLOR_FG_BRIGHT_BLUE  " ]"
#define MSG_OK          VT102_SGR_COLOR_FG_BRIGHT_GREEN " OK "
#define MSG_FAIL        VT102_SGR_COLOR_FG_BRIGHT_RED   "FAIL"
#define MSG_WARN        VT102_SGR_COLOR_FG_YELLOW       "WARN"


#define SERVICES_FOREACH(srv) \
	for (const struct _service_vtable_t **srvptr=__start__service_vtbl; \
		srvptr != __stop__service_vtbl; srvptr++) \
			for (const struct _service_vtable_t *srv=*srvptr; srv != NULL; srv = NULL)


extern const struct _service_vtable_t *__start__service_vtbl[];
extern const struct _service_vtable_t *__stop__service_vtbl[];


static inline bool is_service_id_valid(int srv) {
	return (srv >= 0) && (srv < __stop__service_vtbl - __start__service_vtbl);
}

static int start_r(const struct _service_vtable_t *srv);
static int stop_r( const struct _service_vtable_t *srv);



/**
 *
 * Pre-initialize all known services and daemons
 *
 **/
void services_create()
{

	SERVICES_FOREACH(srv) {

		if (*srv->status != SERVICE_STATE_INIT)
			continue;

		int ret = srv->create();

		if (ret < 0) { // WARN

			continue;

		}

		*srv->status = SERVICE_STATE_STOP;

	}

}



/**
 *
 * Destroy all known services and daemons
 *
 **/
void services_destroy()
{

	SERVICES_FOREACH(srv) {

		if (*srv->status == SERVICE_STATE_START)
			stop_r(srv);

		if (*srv->status != SERVICE_STATE_STOP) { // WARN
		}

		srv->destroy();
		*srv->status = SERVICE_STATE_INIT;

	}

}



/**
 *
 * Start all known services and daemons, one by one.
 * A daemon's dependencies are also started, recursively.
 *
 **/
void services_start()
{

	SERVICES_FOREACH(srv)
		start_r(srv);

}



/**
 *
 * Stop all known services and daemons, one by one.
 *
 **/
void services_stop()
{

	SERVICES_FOREACH(srv)
		stop_r(srv);

}



/**
 *
 * Find a daemon's id, by its name
 *
 **/
int service_find(const char *name)
{

	int id = 0;

	SERVICES_FOREACH(srv)
		if (strcmp(srv->name, name) == 0)
			return id;

		else
			id++;

	return -ENOENT;

}



/**
 *
 * Start a daemon, given its id.
 * The daemon's dependencies are also started, recursively.
 *
 **/
int service_start(int srv)
{

	return is_service_id_valid(srv)?
		start_r(__start__service_vtbl[srv]):
		-ENOENT;

}



/**
 *
 * Stop a daemon, given its id.
 * Any daemon that depends upon it, is also stopped.
 *
 **/
int service_stop(int srv)
{

	return is_service_id_valid(srv)?
		stop_r(__start__service_vtbl[srv]):
		-ENOENT;

}



/**
 *
 * Query the status of a daemon
 *
 **/
int service_get_status(int srv)
{

	return is_service_id_valid(srv)?
		*__start__service_vtbl[srv]->status:
		-ENOENT;

}



/**
 *
 * Return the name of a daemon, given its id
 *
 **/
const char *service_get_name(int srv)
{

	return is_service_id_valid(srv)?
		__start__service_vtbl[srv]->name:
		"[Unknown]";

}



/**
 *
 * Return the description of a daemon, given its id
 *
 **/
const char *service_get_description(int srv)
{

	return is_service_id_valid(srv)?
		__start__service_vtbl[srv]->description:
		"[Unknown]";

}



/**
 *
 * Default behaviors of daemons
 *
 **/
int  service_def_create()  { return 0; }
void service_def_destroy() { }
int  service_def_start()   { return 0; }
int  service_def_stop()    { return 0; }



/**
 *
 * Recursively start a daemon and its dependencies
 *
 **/
int start_r(const struct _service_vtable_t *srv)
{

	if (*srv->status == SERVICE_STATE_START)
		return 0;

	if (*srv->status == SERVICE_STATE_INIT)  //Error: Service uninitialized
		return -EINVAL;

	if (*srv->status == SERVICE_STATE_PREPARE) //Error: cyclic dependency detected
		return -EMLINK;

	int ret = 0;

	*srv->status = SERVICE_STATE_PREPARE;

	for (int n=0;; n++) {

		const struct _service_vtable_t *dep = srv->depends[n];

		if (dep == NULL)
			break;

		if ((ret = start_r(dep)) < 0)
			goto done;

	}

	printk("Starting %s: %s...\n", srv->name, srv->description);

	ret = srv->start();

	printk((ret >= 0)?
		MSG_PRE MSG_LBRACKET MSG_OK   MSG_RBRACKET MSG_POST:
		MSG_PRE MSG_LBRACKET MSG_FAIL MSG_RBRACKET MSG_POST);

done:
	*srv->status = (ret >= 0)?
		SERVICE_STATE_START:
		SERVICE_STATE_STOP;

	return ret;

}



/**
 *
 * Recursively stop a daemon and its dependants
 *
 **/
int stop_r(const struct _service_vtable_t *srv)
{

	if (*srv->status == SERVICE_STATE_STOP)
		return 0;

	if (*srv->status == SERVICE_STATE_INIT)  //Error: Service uninitialized
		return -EINVAL;

	int ret = 0;

	SERVICES_FOREACH(dep) {

		for (int n=0;; n++) {

			const struct _service_vtable_t *depsrv = dep->depends[n];

			if (depsrv == NULL)
				break;

			if (depsrv == srv) {

				if ((ret = stop_r(dep)) < 0)
					goto done;

				break;

			}

		}

	}

	printk("Stopping %s...\n", srv->name);

	ret = srv->stop();

	printk((ret >= 0)?
		MSG_PRE MSG_LBRACKET MSG_OK   MSG_RBRACKET MSG_POST:
		MSG_PRE MSG_LBRACKET MSG_FAIL MSG_RBRACKET MSG_POST);
done:
	*srv->status = (ret >= 0)?
		SERVICE_STATE_STOP:
		SERVICE_STATE_START;

	return ret;

}

