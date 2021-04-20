

#ifndef __CORE_DEVICE_H
#define __CORE_DEVICE_H


enum {

	O_RDONLY =   0,
	O_WRONLY   = 1,
	O_RDWR     = 2,
	O_APPEND   = 0x0008,
	O_CREAT    = 0x0200,
	O_TRUNC    = 0x0400,
	O_EXCL     = 0x0800,
	O_SYNC     = 0x2000,
	O_NDELAY   = 0x4000,
	O_NONBLOCK = 0x4000,
	O_NOCTTY   = 0x8000,

	O_ACCMODE = (O_RDONLY|O_WRONLY|O_RDWR)
};

struct stat;

typedef int (*device_stat_t)(const char *path, struct stat *buf);
typedef int (*device_unlink_t)(const char *path);
typedef int (*device_open_t)(const char *path, int flags, int mode);
typedef int (*device_close_t)(int fd);
typedef int (*device_read_t)(int fd, void *buf, int len);
typedef int (*device_write_t)(int fd, const void *buf, int len);
typedef int (*device_fstat_t)(int fd, struct stat *st);
typedef int (*device_lseek_t)(int fd, int ofs, int whence);
typedef int (*device_ioctl_t)(int fd, int request, void *arg);


struct _device_vtable_t {

	const char *name;
	const char *description;

	device_stat_t   stat;
	device_unlink_t unlink;
	device_open_t   open;
	device_close_t  close;
	device_read_t   read;
	device_write_t  write;
	device_fstat_t  fstat;
	device_lseek_t  lseek;
	device_ioctl_t  ioctl;

};


int device_def_stat(const char *path, struct stat *buf);
int device_def_unlink(const char *path);
int device_def_open(const char *path, int flags, int mode);
int device_def_close(int fd);
int device_def_read(int fd, void *buf, int len);
int device_def_write(int fd, const void *buf, int len);
int device_def_fstat(int fd, struct stat *st);
int device_def_lseek(int fd, int ofs, int whence);
int device_def_ioctl(int fd, int request, void *arg);



#define DEVICE(X, ...)                                    \
	__attribute__((section("_device_vtbl"),used))     \
	const struct _device_vtable_t __dev_##X##_vtbl={  \
		.name        = #X,                        \
		.description = "Device " #X,              \
		.stat        = &device_def_stat,          \
		.unlink      = &device_def_unlink,        \
		.open        = &device_def_open,          \
		.close       = &device_def_close,         \
		.read        = &device_def_read,          \
		.write       = &device_def_write,         \
		.fstat       = &device_def_fstat,         \
		.lseek       = &device_def_lseek,         \
		.ioctl       = &device_def_ioctl,         \
		## __VA_ARGS__                            \
	};


#define DEVICE_STAT(f)   .stat   = (device_stat_t)(f)
#define DEVICE_UNLINK(f) .unlink = (device_unlink_t)(f)
#define DEVICE_OPEN(f)   .open   = (device_open_t)(f)
#define DEVICE_CLOSE(f)  .close  = (device_close_t)(f)
#define DEVICE_READ(f)   .read   = (device_read_t)(f)
#define DEVICE_WRITE(f)  .write  = (device_write_t)(f)
#define DEVICE_FSTAT(f)  .fstat  = (device_fstat_t)(f)
#define DEVICE_LSEEK(f)  .lseek  = (device_lseek_t)(f)
#define DEVICE_IOCTL(f)  .ioctl  = (device_ioctl_t)(f)

#define DEVICE_DESCRIPTION(desc) .description = (desc)


int stat(const char *path, struct stat *buf);
int unlink(const char *path);
int creat(const char *path, int mode);
int open(const char *path, int flags, int mode);
int close(int fd);
int read(int fd, void *buf, int len);
int write(int fd, const void *buf, int len);
int fstat(int fd, struct stat *st);
int lseek(int fd, int ofs, int whence);
int ioctl(int fd, int request, void *buf);


#endif

