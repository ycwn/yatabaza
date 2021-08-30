

#ifndef CORE_LIST_H
#define CORE_LIST_H


typedef struct list {

	struct list *prev;
	struct list *next;

	void *ptr;

} list;


void   _list_append( list *self, list *item);
void   _list_prepend(list *self, list *item);
void   _list_remove( list *self);
size_t _list_count(  list *self);


#define LIST_INIT(n, p) { .prev=(n), .next=(n), .ptr=(p) }
#define LIST_PTR(t, n)  ((t*)((n)->ptr))


static inline void    list_init(     list *self, void *ptr)  { self->prev = self->next = self; self->ptr = ptr; }
static inline void    list_append(   list *self, list *item) { _list_prepend(self, item); } // Yes this is correct
static inline void    list_prepend(  list *self, list *item) { _list_append( self, item); }
static inline void    list_insert(   list *self, list *item) { _list_prepend(self, item); }
static inline void    list_remove(   list *self)             { _list_remove(self); }
static inline void    list_push(     list *self, list *item) { _list_append( self, item); }
static inline void    list_unshift(  list *self, list *item) { _list_prepend(self, item); }
static inline list   *list_shift(    list *self)             { list *item=(list*)(self->next); _list_remove(self->next); return item; }
static inline list   *list_pop(      list *self)             { list *item=(list*)(self->prev); _list_remove(self->prev); return item; }
static inline bool    list_is_first( list *self, list *item) { return self->next == item; }
static inline bool    list_is_last(  list *self, list *item) { return self->prev == item; }
static inline list   *list_begin(    list *self)             { return self->next; }
static inline list   *list_end(      list *self)             { return self; }
static inline list   *list_rbegin(   list *self)             { return self->prev; }
static inline list   *list_rend(     list *self)             { return self; }
static inline void   *list_front(    list *self)             { return list_begin( self)->ptr; }
static inline void   *list_back(     list *self)             { return list_rbegin(self)->ptr; }
static inline bool    list_empty(    list *self)             { return self->prev == self; }
static inline bool    list_connected(list *self)             { return self->next != self; }
static inline size_t  list_size(     list *self)             { return _list_count(self); }


#endif


