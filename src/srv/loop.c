

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>

#include "stm32f1xx_hal.h"

#include "core/types.h"
#include "core/algorithm.h"
#include "core/device.h"


enum {
	FD_NUM = 15,

	FD_n_RD = 1 << 0,
	FD_n_WR = 1 << 1,

	FD_n_ACC = FD_n_RD | FD_n_WR,

	FD_ACC_MASK = (1 << (2 * FD_NUM)) - 1,
	FD_EXCL     = 1 << 31
};

static int loopback_open(const char *path, int flags, int mode);
static int loopback_close(int fd);
static int loopback_read(int fd, void *buf, int len);
static int loopback_write(int fd, const void *buf, int len);

DEVICE(loop,

	DEVICE_OPEN( loopback_open),
	DEVICE_CLOSE(loopback_close),
	DEVICE_READ( loopback_read),
	DEVICE_WRITE(loopback_write),

	DEVICE_DESCRIPTION("Loopback device")

);


GENERATE_RINGBUF(loopbuf, u8, 1024);

static u32            status = 0;
static struct loopbuf loopback;

static inline bool loopback_is_exclusive()     { return status & FD_EXCL; }
static inline void loopback_set_exclusive()    { status |= FD_EXCL; }
static inline void loopback_clr_exclusive()    { status &= ~FD_EXCL; }
static inline bool loopback_has_open()         { return status & FD_ACC_MASK; }
static inline bool loopback_fd_is_free(int fd) { return (status & (FD_n_ACC << (2 * fd))) == 0; }
static inline bool loopback_fd_can_rd(int fd)  { return (status & (FD_n_RD  << (2 * fd))) != 0; }
static inline bool loopback_fd_can_wr(int fd)  { return (status & (FD_n_WR  << (2 * fd))) != 0; }
static inline void loopback_fd_set_rd(int fd)  { status |= FD_n_RD << (2 * fd); }
static inline void loopback_fd_set_wr(int fd)  { status |= FD_n_WR << (2 * fd); }
static inline void loopback_fd_clear( int fd)  { status &= ~(FD_n_ACC << (2 * fd)); }



int loopback_open(const char *path, int flags, int mode)
{

	if (strcmp(path, "/dev/loop") != 0)
		return -ENOSYS;

	if (flags & O_CREAT)
		return -EEXIST;

	if (flags & O_EXCL && loopback_has_open())
		return -EBUSY;

	if (loopback_is_exclusive())
		return -EBUSY;

	int fd = -1;

	for (int n=0; n < FD_NUM; n++)
		if (loopback_fd_is_free(n)) {

			fd = n;
			break;

		}

	if (fd < 0)
		return -EMFILE;

	if ((flags & O_ACCMODE) == O_RDWR || (flags & O_ACCMODE) == O_RDONLY)
		loopback_fd_set_rd(fd);

	if ((flags & O_ACCMODE) == O_RDWR || (flags & O_ACCMODE) == O_WRONLY)
		loopback_fd_set_wr(fd);

	if (flags & O_TRUNC)
		loopbuf_clear(&loopback);

	if (flags & O_EXCL)
		loopback_set_exclusive();

	return fd;

}



int loopback_close(int fd)
{

	if (fd < 0 || fd >= FD_NUM || loopback_fd_is_free(fd))
		return -EBADF;

	loopback_fd_clear(fd);
	loopback_clr_exclusive();

	return 0;

}



int loopback_read(int fd, void *buf, int len)
{

	if (fd < 0 || fd >= FD_NUM || !loopback_fd_can_rd(fd))
		return -EBADF;

	u8 *ptr = buf;
	int num;

	for (num=0; num < len; num++)
		if (!loopbuf_pop(&loopback, ptr++))
			break;

	return num;

}



int loopback_write(int fd, const void *buf, int len)
{

	if (fd < 0 || fd >= FD_NUM || !loopback_fd_can_wr(fd))
		return -EBADF;

	const u8 *ptr = buf;

	for (int n=0; n < len; n++)
		if (!loopbuf_push(&loopback, ptr[n]))
			break;

	return len;

}

