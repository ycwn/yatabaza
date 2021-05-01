

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "core/types.h"
#include "core/device.h"


#define DEVICES_FOREACH(dev) \
	for (const struct _device_vtable_t *dev=&__start__device_vtbl[0]; \
		dev != &__stop__device_vtbl[0]; dev++)


#define DEVICE_FD_BITS  16
#define DEVICE_ID_BITS   8


extern const struct _device_vtable_t __start__device_vtbl[];
extern const struct _device_vtable_t __stop__device_vtbl[];


static inline int make_fd(uint d, uint f) {
	return
		((d & ((1 << (DEVICE_ID_BITS)) - 1)) << (DEVICE_FD_BITS)) |
		((f & ((1 << (DEVICE_FD_BITS)) - 1)));
}

static inline uint get_f(int fd) { return fd & ((1 << (DEVICE_FD_BITS)) - 1); }
static inline uint get_d(int fd) { return (fd >> (DEVICE_FD_BITS)) & ((1 << (DEVICE_ID_BITS)) - 1); }

static const struct _device_vtable_t *get_dev_vtable(int fd);


/**
 *
 * Default device behaviors
 *
 **/
int device_def_stat(const char *path, struct stat *buf)    { return -ENOSYS; }
int device_def_unlink(const char *path)                    { return -ENOSYS; }
int device_def_open(const char *path, int flags, int mode) { return -ENOSYS; }
int device_def_close(int fd)                               { return -ENOSYS; }
int device_def_read(int fd, void *buf, int len)            { return -ENOSYS; }
int device_def_write(int fd, const void *buf, int len)     { return -ENOSYS; }
int device_def_fstat(int fd, struct stat *st)              { return -ENOSYS; }
int device_def_lseek(int fd, int ofs, int whence)          { return -ENOSYS; }
int device_def_isatty(int fd)                              { return -ENOSYS; }
int device_def_ioctl(int fd, int request, void *arg)       { return -ENOSYS; }



/**
 *
 * Return information about a file
 *
 **/
int stat(const char *path, struct stat *buf)
{

	int ret = -ENOENT;

	DEVICES_FOREACH(dev)
		if ((ret = dev->stat(path, buf)) != -ENOSYS)
			break;

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

	return 0;

}



/**
 *
 * Remove a file
 *
 **/
int unlink(const char *path)
{

	int ret = -ENOENT;

	DEVICES_FOREACH(dev)
		if ((ret = dev->unlink(path)) != -ENOSYS)
			break;

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

	return 0;

}



/**
 *
 * Create a new file
 *
 **/
int creat(const char *path, int mode)
{

	return open(path, O_CREAT | O_WRONLY | O_TRUNC, mode);

}



/**
 *
 * Open an existing file, or create a new one
 *
 **/
int open(const char *path, int flags, int mode)
{

	int ret = -ENOENT;
	int num = 0;

	DEVICES_FOREACH(dev) {

		if ((ret = dev->open(path, flags, mode)) != -ENOSYS)
			break;

		num++;

	}

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

 	return make_fd(num, ret);

}



/**
 *
 * Close an open file
 *
 **/
int close(int fd)
{

	int ret = -EBADF;
	const struct _device_vtable_t *dev = get_dev_vtable(fd);

	if (dev != NULL)
		ret = dev->close(get_f(fd));

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

	return ret;

}



/**
 *
 * Read from a file
 *
 **/
int read(int fd, void *buf, int len)
{

	int ret = -EBADF;
	const struct _device_vtable_t *dev = get_dev_vtable(fd);

	if (dev != NULL)
		ret = dev->read(get_f(fd), buf, len);

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

	return ret;

}



/**
 *
 * Write to a file
 *
 **/
int write(int fd, const void *buf, int len)
{

	int ret = -EBADF;
	const struct _device_vtable_t *dev = get_dev_vtable(fd);

	if (dev != NULL)
		ret = dev->write(get_f(fd), buf, len);

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

	return ret;

}



/**
 *
 * Return information about an open file
 *
 **/
int fstat(int fd, struct stat *st)
{

	int ret = -EBADF;
	const struct _device_vtable_t *dev = get_dev_vtable(fd);

	if (dev != NULL)
		ret = dev->fstat(get_f(fd), st);

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

	return ret;

}



/**
 *
 * Reposition a files read or write pointer
 *
 **/
int lseek(int fd, int ofs, int whence)
{

	int ret = -EBADF;
	const struct _device_vtable_t *dev = get_dev_vtable(fd);

	if (dev != NULL)
		ret = dev->lseek(get_f(fd), ofs, whence);

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

	return ret;

}



/**
 *
 * Send a control command to a device
 *
 **/
int ioctl(int fd, int request, void *arg)
{


	int ret = -EBADF;
	const struct _device_vtable_t *dev = get_dev_vtable(fd);

	if (dev != NULL)
		ret = dev->ioctl(get_f(fd), request, arg);

	if (ret < 0) {

		errno = -ret;
		return -1;

	}

	return ret;

}



/**
 *
 * Find a device's vtable, given a file descriptor
 *
 **/
const struct _device_vtable_t *get_dev_vtable(int fd)
{

	if (fd < 0)
		return NULL;

	const struct _device_vtable_t *dev = __start__device_vtbl + get_d(fd);

	if (dev >= __stop__device_vtbl)
		return NULL;

	return dev;

}
