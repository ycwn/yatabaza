

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "core/types.h"
#include "core/list.h"



void _list_append(list *self, list *item)
{

	item->prev = self;
	item->next = self->next;

	self->next->prev = item;
	self->next       = item;

}



void _list_prepend(list *self, list *item)
{

	item->prev = self->prev;
	item->next = self;

	self->prev->next = item;
	self->prev       = item;

}



void _list_remove(list *self)
{

	self->prev->next = self->next;
	self->next->prev = self->prev;

	self->prev = self;
	self->next = self;

}



size_t _list_count(list *self)
{

	size_t n = 0;

	for (list *it=self->next; it != self; it=it->next)
		n++;

	return n;

}

