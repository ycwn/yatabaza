

#ifndef CORE_SERVICE_H
#define CORE_SERVICE_H


enum {

	SERVICE_STATE_INIT  = 0, // destroyed or is uninitialized
	SERVICE_STATE_START = 1,
	SERVICE_STATE_STOP  = 2,

	SERVICE_STATE_PREPARE = 3

};


// create:  init -> stop, start, stop: warn
// destroy: start -> stop -> init, init -> nop
// start:   stop -> start, start -> nop, init -> error
// stop:    start -> stop, stop -> nop, init -> error

typedef int  (*service_create_t)();
typedef void (*service_destroy_t)();
typedef int  (*service_start_t)();
typedef int  (*service_stop_t)();

struct _service_vtable_t {

	const char *name;
	const char *description;

	service_create_t  create;
	service_destroy_t destroy;
	service_start_t   start;
	service_stop_t    stop;

	u8 *status;

	const struct _service_vtable_t *const depends[];

};


void services_create();
void services_destroy();
void services_start();
void services_stop();

int service_find(const char *name);
int service_start(int srv);
int service_stop(int srv);

int         service_get_status(int srv);
const char *service_get_name(int srv);
const char *service_get_description(int srv);


extern int  service_def_create();
extern void service_def_destroy();
extern int  service_def_start();
extern int  service_def_stop();


#define SERVICE(X, ...)                                    \
	u8 __##X##_status = SERVICE_STATE_INIT;            \
	const struct _service_vtable_t __srv_##X##_vtbl={  \
		.name        = #X,                         \
		.description = "Service " #X,              \
		.create      = &service_def_create,        \
		.destroy     = &service_def_destroy,       \
		.start       = &service_def_start,         \
		.stop        = &service_def_stop,          \
		.status      = &__##X##_status,            \
		.depends     = { NULL },                   \
		## __VA_ARGS__                             \
	};                                                 \
	__attribute__((section("_service_vtbl"),used))     \
	const void *const __srv_##X##_vt_ptr = &__srv_##X##_vtbl


#define SERVICE_CREATE(ct)  .create  = (service_create_t)(ct)
#define SERVICE_DESTROY(dt) .destroy = (service_destroy_t)(dt)
#define SERVICE_START(st)   .start   = (service_start_t)(st)
#define SERVICE_STOP(sp)    .stop    = (service_stop_t)(sp)

#define SERVICE_DESCRIPTION(desc) .description = (desc)
#define SERVICE_DEPENDS(...)      .depends = { __VA_ARGS__, NULL }
#define SERVICE_DEP(X)            &__srv_##X##_vtbl

#define SERVICE_DEF(X)  \
	extern const struct _service_vtable_t __srv_##X##_vtbl

#endif

