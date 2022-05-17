

#ifndef CORE_KERNEL_H
#define CORE_KERNEL_H


enum {
	RB_HALT_SYSTEM = 0xcdef0123,
	RB_POWER_OFF   = 0x4321fedc,
	RB_AUTOBOOT    = 0x1234567
};


int  reboot(int cmd);
void panic() __attribute__((noreturn));


#endif
