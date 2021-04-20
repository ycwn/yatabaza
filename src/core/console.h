

#ifndef __CORE_CONSOLE_H
#define __CORE_CONSOLE_H


typedef void (*console_handler_t)(char ch);


console_handler_t console_get_handler();
console_handler_t console_set_handler(console_handler_t handler);


void printk(const char *fmt, ...) __attribute__((format(gnu_printf, 1, 2)));

void writek( const char *msg);
void writekn(const char *msg, size_t len);

void dump(const void *buf, size_t len);


#endif

