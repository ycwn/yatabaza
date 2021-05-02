

#ifndef SYNTH_OPL_IO_H
#define SYNTH_OPL_IO_H


enum {
	SYNTH_OPL_FIRST = 0,
	SYNTH_OPL_LAST  = 7
};


int opl_io_init( uint dev);
int opl_io_reset(uint dev);

int opl_io_lock(     uint dev);
int opl_io_unlock(   uint dev);
int opl_io_is_locked(uint dev);

int opl_io_read(  uint dev);
int opl_io_write8(uint dev, const u8 *reg, const u8 *val, uint num);


#endif

