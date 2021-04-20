

#ifndef __SRV_BUS_H
#define __SRV_BUS_H


typedef u16 addr_t;


void bus_reset();
int  bus_ping(addr_t addr);
int  bus_scan_list(addr_t *addrs, uint num, addr_t start, addr_t end);

int bus_read_buf(addr_t addr, void *buf, size_t num);
int bus_write_buf(addr_t addr, const void *buf, size_t num);

int bus_read_r8_buf( addr_t addr, u8 reg, void *buf, size_t num);
int bus_write_r8_buf(addr_t addr, u8 reg, const void *buf, size_t num);

int bus_read_r16_buf( addr_t addr, u16 reg, void *buf, size_t num);
int bus_write_r16_buf(addr_t addr, u16 reg, const void *buf, size_t num);


static inline int bus_read_u8( addr_t addr, u8  *val) { return bus_read_buf(addr, val, sizeof(u8));  }
static inline int bus_read_u16(addr_t addr, u16 *val) { return bus_read_buf(addr, val, sizeof(u16)); }
static inline int bus_read_u32(addr_t addr, u32 *val) { return bus_read_buf(addr, val, sizeof(u32)); }
static inline int bus_read_u64(addr_t addr, u64 *val) { return bus_read_buf(addr, val, sizeof(u64)); }

static inline int bus_write_u8( addr_t addr, u8  val) { return bus_write_buf(addr, &val, sizeof(u8)); }
static inline int bus_write_u16(addr_t addr, u16 val) { return bus_write_buf(addr, &val, sizeof(u16)); }
static inline int bus_write_u32(addr_t addr, u32 val) { return bus_write_buf(addr, &val, sizeof(u32)); }
static inline int bus_write_u64(addr_t addr, u64 val) { return bus_write_buf(addr, &val, sizeof(u64)); }


static inline int bus_read_r8_u8( addr_t addr, u8 reg, u8  *val) { return bus_read_r8_buf(addr, reg, val, sizeof(u8));  }
static inline int bus_read_r8_u16(addr_t addr, u8 reg, u16 *val) { return bus_read_r8_buf(addr, reg, val, sizeof(u16)); }
static inline int bus_read_r8_u32(addr_t addr, u8 reg, u32 *val) { return bus_read_r8_buf(addr, reg, val, sizeof(u32)); }
static inline int bus_read_r8_u64(addr_t addr, u8 reg, u64 *val) { return bus_read_r8_buf(addr, reg, val, sizeof(u64)); }

static inline int bus_write_r8_u8( addr_t addr, u8 reg, u8  val) { return bus_write_r8_buf(addr, reg, &val, sizeof(u8)); }
static inline int bus_write_r8_u16(addr_t addr, u8 reg, u16 val) { return bus_write_r8_buf(addr, reg, &val, sizeof(u16)); }
static inline int bus_write_r8_u32(addr_t addr, u8 reg, u32 val) { return bus_write_r8_buf(addr, reg, &val, sizeof(u32)); }
static inline int bus_write_r8_u64(addr_t addr, u8 reg, u64 val) { return bus_write_r8_buf(addr, reg, &val, sizeof(u64)); }


static inline int bus_read_r16_u8( addr_t addr, u16 reg, u8  *val) { return bus_read_r16_buf(addr, reg, val, sizeof(u8));  }
static inline int bus_read_r16_u16(addr_t addr, u16 reg, u16 *val) { return bus_read_r16_buf(addr, reg, val, sizeof(u16)); }
static inline int bus_read_r16_u32(addr_t addr, u16 reg, u32 *val) { return bus_read_r16_buf(addr, reg, val, sizeof(u32)); }
static inline int bus_read_r16_u64(addr_t addr, u16 reg, u64 *val) { return bus_read_r16_buf(addr, reg, val, sizeof(u64)); }

static inline int bus_write_r16_u8( addr_t addr, u16 reg, u8  val) { return bus_write_r16_buf(addr, reg, &val, sizeof(u8)); }
static inline int bus_write_r16_u16(addr_t addr, u16 reg, u16 val) { return bus_write_r16_buf(addr, reg, &val, sizeof(u16)); }
static inline int bus_write_r16_u32(addr_t addr, u16 reg, u32 val) { return bus_write_r16_buf(addr, reg, &val, sizeof(u32)); }
static inline int bus_write_r16_u64(addr_t addr, u16 reg, u64 val) { return bus_write_r16_buf(addr, reg, &val, sizeof(u64)); }


#endif

