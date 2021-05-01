

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include <errno.h>

#include <printf.h>

#include "core/types.h"
#include "core/console.h"


static void handler_null(char ch);


static console_handler_t handler = &handler_null;



/**
 *
 * Return the current console handler.
 *
 **/
console_handler_t console_get_handler()
{

	return handler;

}



/**
 *
 * Update the current console handler. The handler can be NULL,
 * in which case system messages are discarded.
 *
 **/
console_handler_t console_set_handler(console_handler_t h)
{

	console_handler_t prev_handler = handler;

	if (h != NULL)
		handler = h;

	else
		handler = &handler_null;

	return prev_handler;

}



/**
 *
 * Print a formatted message to the system logs.
 *
 **/
void printk(const char *fmt, ...)
{

	va_list args;

	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

}



/**
 *
 * Print a message to the system logs.
 *
 **/
void writek(const char *msg)
{

	int ch;

	while ((ch = *msg++) != 0)
		_putchar(ch);

}



/**
 *
 * Print a message to the system logs.
 *
 **/
void writekn(const char *msg, size_t len)
{

	for (int n=0; n < len; n++)
		_putchar(msg[n]);

}



/**
 *
 * Internally called by printf() and co. Forwards the characters
 * to the current console handler.
 *
 **/
void _putchar(char ch)
{

	handler(ch);

}



/**
 *
 * Null console handler, discards incoming messages
 *
 **/
void handler_null(char ch)
{
}

