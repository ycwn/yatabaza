

#ifndef CORE_ALGORITHM_H
#define CORE_ALGORITHM_H


/**
 *   Generate a function that sorts arrays of a given datatype
 * with the given comparator using insertion sort.
 *
 * Generates:
 *   void function_name(datatype *array, int num);
 *
 * Comparator is:
 *   int comparator(const datatype *a, const datatype *b)
 *
 **/
#define GENERATE_INSERTION_SORT(function_name, datatype, comparator)                \
	void function_name(datatype *array, int num)                                \
	{                                                                           \
		for (int i=1, j; i < num; i++) {                                    \
			datatype temp = array[i];                                   \
			j = i - 1;                                                  \
			while (j >= 0 &&(comparator)((const datatype*)&array[j],    \
						     (const datatype*)&temp) > 0) { \
				array[j + 1] = array[j];                            \
				j--;                                                \
			}                                                           \
			array[j + 1] = temp;                                        \
		}                                                                   \
	}


/**
 *   Generate a function that sorts arrays of a given datatype
 * with the given comparator using selection sort.
 *
 * Generates:
 *   void function_name(datatype *array, int num);
 *
 * Comparator is:
 *   int comparator(const datatype *a, const datatype *b)
 *
 **/
#define GENERATE_SELECTION_SORT(function_name, datatype, comparator)              \
	void function_name(datatype *array, int num)                              \
	{                                                                         \
		for (int i=0, j, k; i < num - 1; i++) {                           \
			k = i;                                                    \
			for (j=i+1; j < num; j++)                                 \
				if ((comparator)((const datatype*)&array[k],      \
					         (const datatype*)&array[j]) > 0) \
					k = j;                                    \
			datatype temp = array[i];                                 \
			array[i] = array[k];                                      \
			array[k] = temp;                                          \
		}                                                                 \
	}


/**
 *   Generate a function that sorts arrays of a given datatype
 * with the given comparator using shell sort.
 *
 * Generates:
 *   void function_name(datatype *array, int num);
 *
 * Comparator is:
 *   int comparator(const datatype *a, const datatype *b)
 *
 **/
#define GENERATE_SHELL_SORT(function_name, datatype, comparator)                             \
	void function_name(datatype *array, int num)                                         \
	{                                                                                    \
		int k = 1;                                                                   \
		while (k < num) k = 3 * k + 1;                                               \
		while (k > 0) {                                                              \
			k /= 3;                                                              \
			for (int i=k, j; i < num; i++) {                                     \
				datatype temp = array[i];                                    \
				j = i - k;                                                   \
				while (j >= 0 && (comparator)((const datatype*)&array[j],    \
							      (const datatype*)&temp) > 0) { \
					array[j + k] = array[j];                             \
					j -= k;                                              \
				}                                                            \
				array[j + k] = temp;                                         \
			}                                                                    \
		}                                                                            \
	}


/**
 *   Generate a sorting network that sorts arrays of a given datatype
 * and size with the given comparator using Batcher's Even-Odd merge.
 * Maximum array size is 32 elements.
 *
 * Generates:
 *   void function_name(datatype *array);
 *
 * Comparator is:
 *   int comparator(const datatype *a, const datatype *b)
 *
 **/
#define GENERATE_SORTING_NETWORK(function_name, datatype, N, comparator) \
	void function_name(datatype *array)                              \
	{                                                                \
		datatype temp;                                           \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  0, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  1, 17);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  2, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3, 19);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  4, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5, 21);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  6, 22);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 23);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  8, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  9, 25);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 10, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 27);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 12, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 29);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 14, 30);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 31);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  0,  8);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  1,  9);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  2, 10);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3, 11);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  4, 12);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5, 13);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  6, 14);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 15);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 16, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 17, 25);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 18, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 19, 27);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 20, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 21, 29);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 22, 30);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 23, 31);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  8, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  9, 17);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 10, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 19);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 12, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 21);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 14, 22);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 23);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  0,  4);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  1,  5);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  2,  6);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3,  7);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  8, 12);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  9, 13);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 10, 14);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 15);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 16, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 17, 21);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 18, 22);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 19, 23);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 24, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 25, 29);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 26, 30);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 27, 31);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  4, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5, 17);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  6, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 19);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 12, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 25);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 14, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 27);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  4,  8);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5,  9);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  6, 10);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 11);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 12, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 17);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 14, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 19);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 20, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 21, 25);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 22, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 23, 27);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  0,  2);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  1,  3);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  4,  6);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5,  7);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  8, 10);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  9, 11);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 12, 14);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 15);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 16, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 17, 19);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 20, 22);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 21, 23);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 24, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 25, 27);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 28, 30);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 29, 31);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  2, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3, 17);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  6, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 21);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 10, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 25);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 14, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 29);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  2,  8);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3,  9);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  6, 12);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 13);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 10, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 17);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 14, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 21);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 18, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 19, 25);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 22, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 23, 29);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  2,  4);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3,  5);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  6,  8);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7,  9);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 10, 12);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 13);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 14, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 17);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 18, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 19, 21);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 22, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 23, 25);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 26, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 27, 29);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  0,  1);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  2,  3);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  4,  5);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  6,  7);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  8,  9);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 10, 11);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 12, 13);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 14, 15);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 16, 17);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 18, 19);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 20, 21);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 22, 23);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 24, 25);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 26, 27);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 28, 29);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 30, 31);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  1, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 22);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  9, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 30);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  1,  8);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3, 10);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5, 12);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 14);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  9, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 22);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 17, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 19, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 21, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 23, 30);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  1,  4);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3,  6);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5,  8);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7, 10);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  9, 12);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 14);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 17, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 19, 22);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 21, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 23, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 25, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 27, 30);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  1,  2);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  3,  4);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  5,  6);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  7,  8);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N,  9, 10);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 11, 12);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 13, 14);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 15, 16);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 17, 18);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 19, 20);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 21, 22);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 23, 24);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 25, 26);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 27, 28);        \
		__SORTING_NETWORK_CMPSWAP(comparator, N, 29, 30);        \
	}

#define __SORTING_NETWORK_CMPSWAP(comparator, N, A, B)                      \
	do {                                                                \
		if ((N) > B) {                                              \
			if ((comparator)((const datatype*)&array[A],        \
					 (const datatype*)&array[B]) > 0) { \
				temp     = array[A];                        \
				array[A] = array[B];                        \
				array[B] = temp;                            \
			}                                                   \
		}                                                           \
	} while (0);



/**
 *   Generate a function that finds the first item of
 * an equal range in a sorted array.
 *
 * Generates:
 *   const datatype *function_name(const datatype *array, int num, keytype key);
 *
 * Comparator is:
 *   int comparator(const datatype *value, keytype key)
 *
 **/
#define GENERATE_LOWER_BOUND(function_name, datatype, keytype, comparator)         \
	const datatype *function_name(const datatype *array, int num, keytype key) \
	{                                                                          \
		const datatype *first = array;                                     \
		for (int count=num; count > 0;) {                                  \
			int             step = count / 2;                          \
			const datatype *idx  = first + step;                       \
			if ((comparator)(idx, key) < 0) {                          \
				first  = ++idx;                                    \
				count -= step + 1;                                 \
			} else                                                     \
				count = step;                                      \
		}                                                                  \
		return first;                                                      \
	}



/**
 *   Generate a function that finds the last item of
 * an equal range in a sorted array.
 *
 * Generates:
 *   const datatype *function_name(const datatype *array, int num, keytype key);
 *
 * Comparator is:
 *   int comparator(const datatype *value, keytype key)
 *
 **/
#define GENERATE_UPPER_BOUND(function_name, datatype, keytype, comparator)         \
	const datatype *function_name(const datatype *array, int num, keytype key) \
	{                                                                          \
		const datatype *last = array;                                      \
		for (int count=num; count > 0;) {                                  \
			int             step = count / 2;                          \
			const datatype *idx  = last + step;                        \
			if (comparator(idx, key) <= 0) {                           \
				last   = ++idx;                                    \
				count -= step + 1;                                 \
			} else                                                     \
				count = step;                                      \
		}                                                                  \
		return last;                                                       \
	}



/**
 * Generate the definitions (structs and prototypes) for
 * an implementation of a circular (ring) buffer.
 *
 **/
#define GENERATE_RINGBUF_DEF(ringbuf, datatype, capacity)                                                                  \
                                                                                                                           \
	enum { ringbuf##_capacity = (capacity) };                                                                          \
	typedef datatype ringbuf##_datatype;                                                                               \
                                                                                                                           \
	struct ringbuf {                                                                                                   \
                                                                                                                           \
		int head;                                                                                                  \
		int tail;                                                                                                  \
                                                                                                                           \
		ringbuf##_datatype data[ringbuf##_capacity];                                                               \
                                                                                                                           \
	};                                                                                                                 \
															   \
	ringbuf##_datatype ringbuf##_peek(struct ringbuf *rb);                                                             \
	bool ringbuf##_pushv(struct ringbuf *rb, const ringbuf##_datatype *val);                                           \
	bool ringbuf##_pushvv(struct ringbuf *rb, ringbuf##_datatype **elm);                                               \
	bool ringbuf##_popv(struct ringbuf *rb, ringbuf##_datatype *val);                                                  \
															   \
	static inline void ringbuf##_clear(struct ringbuf *rb)    { rb->head = rb->tail = 0; }                             \
	static inline uint ringbuf##_count(struct ringbuf *rb)    { return rb->tail - rb->head; }                          \
	static inline bool ringbuf##_is_empty(struct ringbuf *rb) { return ringbuf##_count(rb) == 0; }                     \
	static inline bool ringbuf##_is_full( struct ringbuf *rb) { return ringbuf##_count(rb) >= ringbuf##_capacity; }    \
															   \
	static inline bool ringbuf##_push(struct ringbuf *rb, const ringbuf##_datatype val) {                              \
		return ringbuf##_pushv(rb, &val);                                                                          \
	}                                                                                                                  \
                                                                                                                           \


/**
 * Generate the external prototypes for the ring buffer.
 *
 **/
#define GENERATE_RINGBUF_EXT(ringbuf)                                                    \
	extern ringbuf##_datatype ringbuf##_peek(struct ringbuf *rb);                    \
	extern bool ringbuf##_pushv(struct ringbuf *rb, const ringbuf##_datatype *val);  \
	extern bool ringbuf##_pushvv(struct ringbuf *rb, ringbuf##_datatype **elm);      \
	extern bool ringbuf##_popv(struct ringbuf *rb, ringbuf##_datatype *val);



/**
 * Generate the implementation of the ring buffer's basic functions.
 *
 **/
#define GENERATE_RINGBUF_SRC(ringbuf)                                                         \
                                                                                              \
	ringbuf##_datatype ringbuf##_peek(struct ringbuf *rb) {                               \
		return rb->data[(rb->head >= 0)? rb->head: rb->head + ringbuf##_capacity];    \
	}                                                                                     \
                                                                                              \
	bool ringbuf##_pushv(struct ringbuf *rb, const ringbuf##_datatype *val) {             \
		bool full = ringbuf##_is_full(rb);                                            \
		rb->data[rb->tail++] = *val;                                                  \
		if (rb->tail >= ringbuf##_capacity) {                                         \
			rb->tail -= ringbuf##_capacity;                                       \
			rb->head -= ringbuf##_capacity;                                       \
		}                                                                             \
		if (!full)                                                                    \
			return false;                                                         \
		rb->head++;                                                                   \
		return true;                                                                  \
	}                                                                                     \
											      \
	bool ringbuf##_pushvv(struct ringbuf *rb, ringbuf##_datatype **elm) {                 \
		bool full = ringbuf##_is_full(rb);                                            \
		*elm = &rb->data[rb->tail++];                                                 \
		if (rb->tail >= ringbuf##_capacity) {                                         \
			rb->tail -= ringbuf##_capacity;                                       \
			rb->head -= ringbuf##_capacity;                                       \
		}                                                                             \
		if (!full)                                                                    \
			return false;                                                         \
		rb->head++;                                                                   \
		return true;                                                                  \
	}                                                                                     \
                                                                                              \
	bool ringbuf##_popv(struct ringbuf *rb, ringbuf##_datatype *val) {                    \
		if (ringbuf##_is_empty(rb)) return false;                                     \
		*val = ringbuf##_peek(rb);                                                    \
		rb->head++;                                                                   \
		return true;                                                                  \
	}



/**
 * Generate the prototypes and implementation of the ring buffer.
 *
 **/
#define GENERATE_RINGBUF(ringbuf, datatype, capacity) \
	GENERATE_RINGBUF_DEF(ringbuf, datatype, capacity) \
	GENERATE_RINGBUF_SRC(ringbuf)



/**
 *  Expand the parameter and convert to string
 *
 **/
#define PP_STRINGIFY_II(X)  #X
#define PP_STRINGIFY_I(X)   PP_STRINGIFY_II(X)
#define PP_STRINGIFY(X)     PP_STRINGIFY_I(X)



/**
 * Expand and concatenate the parameters
 *
 **/
#define PP_CONCAT_II(x, y)  x##y
#define PP_CONCAT_I(x, y)   PP_CONCAT_II(x, y)
#define PP_CONCAT(x, y)     PP_CONCAT_I(x, y)



/**
 *  Count the arguments given to the variadic macro (up to 99)
 *
 **/
#define PP_NARG_I( \
	_00, _01, _02, _03, _04, _05, _06, _07, _08, _09,  \
	_10, _11, _12, _13, _14, _15, _16, _17, _18, _19,  \
	_20, _21, _22, _23, _24, _25, _26, _27, _28, _29,  \
	_30, _31, _32, _33, _34, _35, _36, _37, _38, _39,  \
	_40, _41, _42, _43, _44, _45, _46, _47, _48, _49,  \
	_50, _51, _52, _53, _54, _55, _56, _57, _58, _59,  \
	_60, _61, _62, _63, _64, _65, _66, _67, _68, _69,  \
	_70, _71, _72, _73, _74, _75, _76, _77, _78, _79,  \
	_80, _81, _82, _83, _84, _85, _86, _87, _88, _89,  \
	_90, _91, _92, _93, _94, _95, _96, _97, _98, _99,  \
	N, ...)  N

#define PP_NARG(...)  PP_NARG_I(,##__VA_ARGS__,  \
	99, 98, 97, 96, 95, 94, 93, 92, 91, 90,  \
	89, 88, 87, 86, 85, 84, 83, 82, 81, 80,  \
	79, 78, 77, 76, 75, 74, 73, 72, 71, 70,  \
	69, 68, 67, 66, 65, 64, 63, 62, 61, 60,  \
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50,  \
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40,  \
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30,  \
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20,  \
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10,  \
	 9,  8,  7,  6,  5,  4,  3,  2,  1,  0)



/**
 *  Generate an overloaded call to X, by appending the number
 *  of arguments to the name.
 *
 **/
#define PP_OVERLOAD(X, ...) PP_CONCAT(X, PP_NARG(__VA_ARGS__))



/**
 *  Apply X to each argument
 *
 **/
#define PP_FOREACH_I_0(X, ...)
#define PP_FOREACH_I_1(X, x, ...)   X(x) PP_FOREACH_I_0(X, __VA_ARGS__)
#define PP_FOREACH_I_2(X, x, ...)   X(x) PP_FOREACH_I_1(X, __VA_ARGS__)
#define PP_FOREACH_I_3(X, x, ...)   X(x) PP_FOREACH_I_2(X, __VA_ARGS__)
#define PP_FOREACH_I_4(X, x, ...)   X(x) PP_FOREACH_I_3(X, __VA_ARGS__)
#define PP_FOREACH_I_5(X, x, ...)   X(x) PP_FOREACH_I_4(X, __VA_ARGS__)
#define PP_FOREACH_I_6(X, x, ...)   X(x) PP_FOREACH_I_5(X, __VA_ARGS__)
#define PP_FOREACH_I_7(X, x, ...)   X(x) PP_FOREACH_I_6(X, __VA_ARGS__)
#define PP_FOREACH_I_8(X, x, ...)   X(x) PP_FOREACH_I_7(X, __VA_ARGS__)
#define PP_FOREACH_I_9(X, x, ...)   X(x) PP_FOREACH_I_8(X, __VA_ARGS__)
#define PP_FOREACH_I_10(X, x, ...)  X(x) PP_FOREACH_I_9(X, __VA_ARGS__)
#define PP_FOREACH_I_11(X, x, ...)  X(x) PP_FOREACH_I_10(X, __VA_ARGS__)
#define PP_FOREACH_I_12(X, x, ...)  X(x) PP_FOREACH_I_11(X, __VA_ARGS__)
#define PP_FOREACH_I_13(X, x, ...)  X(x) PP_FOREACH_I_12(X, __VA_ARGS__)
#define PP_FOREACH_I_14(X, x, ...)  X(x) PP_FOREACH_I_13(X, __VA_ARGS__)
#define PP_FOREACH_I_15(X, x, ...)  X(x) PP_FOREACH_I_14(X, __VA_ARGS__)
#define PP_FOREACH_I_16(X, x, ...)  X(x) PP_FOREACH_I_15(X, __VA_ARGS__)
#define PP_FOREACH_I_17(X, x, ...)  X(x) PP_FOREACH_I_16(X, __VA_ARGS__)
#define PP_FOREACH_I_18(X, x, ...)  X(x) PP_FOREACH_I_17(X, __VA_ARGS__)
#define PP_FOREACH_I_19(X, x, ...)  X(x) PP_FOREACH_I_18(X, __VA_ARGS__)
#define PP_FOREACH_I_20(X, x, ...)  X(x) PP_FOREACH_I_19(X, __VA_ARGS__)
#define PP_FOREACH_I_21(X, x, ...)  X(x) PP_FOREACH_I_20(X, __VA_ARGS__)
#define PP_FOREACH_I_22(X, x, ...)  X(x) PP_FOREACH_I_21(X, __VA_ARGS__)
#define PP_FOREACH_I_23(X, x, ...)  X(x) PP_FOREACH_I_22(X, __VA_ARGS__)
#define PP_FOREACH_I_24(X, x, ...)  X(x) PP_FOREACH_I_23(X, __VA_ARGS__)
#define PP_FOREACH_I_25(X, x, ...)  X(x) PP_FOREACH_I_24(X, __VA_ARGS__)
#define PP_FOREACH_I_26(X, x, ...)  X(x) PP_FOREACH_I_25(X, __VA_ARGS__)
#define PP_FOREACH_I_27(X, x, ...)  X(x) PP_FOREACH_I_26(X, __VA_ARGS__)
#define PP_FOREACH_I_28(X, x, ...)  X(x) PP_FOREACH_I_27(X, __VA_ARGS__)
#define PP_FOREACH_I_29(X, x, ...)  X(x) PP_FOREACH_I_28(X, __VA_ARGS__)
#define PP_FOREACH_I_30(X, x, ...)  X(x) PP_FOREACH_I_29(X, __VA_ARGS__)
#define PP_FOREACH_I_31(X, x, ...)  X(x) PP_FOREACH_I_30(X, __VA_ARGS__)
#define PP_FOREACH_I_32(X, x, ...)  X(x) PP_FOREACH_I_31(X, __VA_ARGS__)
#define PP_FOREACH_I_33(X, x, ...)  X(x) PP_FOREACH_I_32(X, __VA_ARGS__)
#define PP_FOREACH_I_34(X, x, ...)  X(x) PP_FOREACH_I_33(X, __VA_ARGS__)
#define PP_FOREACH_I_35(X, x, ...)  X(x) PP_FOREACH_I_34(X, __VA_ARGS__)
#define PP_FOREACH_I_36(X, x, ...)  X(x) PP_FOREACH_I_35(X, __VA_ARGS__)
#define PP_FOREACH_I_37(X, x, ...)  X(x) PP_FOREACH_I_36(X, __VA_ARGS__)
#define PP_FOREACH_I_38(X, x, ...)  X(x) PP_FOREACH_I_37(X, __VA_ARGS__)
#define PP_FOREACH_I_39(X, x, ...)  X(x) PP_FOREACH_I_38(X, __VA_ARGS__)
#define PP_FOREACH_I_40(X, x, ...)  X(x) PP_FOREACH_I_39(X, __VA_ARGS__)
#define PP_FOREACH_I_41(X, x, ...)  X(x) PP_FOREACH_I_40(X, __VA_ARGS__)
#define PP_FOREACH_I_42(X, x, ...)  X(x) PP_FOREACH_I_41(X, __VA_ARGS__)
#define PP_FOREACH_I_43(X, x, ...)  X(x) PP_FOREACH_I_42(X, __VA_ARGS__)
#define PP_FOREACH_I_44(X, x, ...)  X(x) PP_FOREACH_I_43(X, __VA_ARGS__)
#define PP_FOREACH_I_45(X, x, ...)  X(x) PP_FOREACH_I_44(X, __VA_ARGS__)
#define PP_FOREACH_I_46(X, x, ...)  X(x) PP_FOREACH_I_45(X, __VA_ARGS__)
#define PP_FOREACH_I_47(X, x, ...)  X(x) PP_FOREACH_I_46(X, __VA_ARGS__)
#define PP_FOREACH_I_48(X, x, ...)  X(x) PP_FOREACH_I_47(X, __VA_ARGS__)
#define PP_FOREACH_I_49(X, x, ...)  X(x) PP_FOREACH_I_48(X, __VA_ARGS__)
#define PP_FOREACH_I_50(X, x, ...)  X(x) PP_FOREACH_I_49(X, __VA_ARGS__)
#define PP_FOREACH_I_51(X, x, ...)  X(x) PP_FOREACH_I_50(X, __VA_ARGS__)
#define PP_FOREACH_I_52(X, x, ...)  X(x) PP_FOREACH_I_51(X, __VA_ARGS__)
#define PP_FOREACH_I_53(X, x, ...)  X(x) PP_FOREACH_I_52(X, __VA_ARGS__)
#define PP_FOREACH_I_54(X, x, ...)  X(x) PP_FOREACH_I_53(X, __VA_ARGS__)
#define PP_FOREACH_I_55(X, x, ...)  X(x) PP_FOREACH_I_54(X, __VA_ARGS__)
#define PP_FOREACH_I_56(X, x, ...)  X(x) PP_FOREACH_I_55(X, __VA_ARGS__)
#define PP_FOREACH_I_57(X, x, ...)  X(x) PP_FOREACH_I_56(X, __VA_ARGS__)
#define PP_FOREACH_I_58(X, x, ...)  X(x) PP_FOREACH_I_57(X, __VA_ARGS__)
#define PP_FOREACH_I_59(X, x, ...)  X(x) PP_FOREACH_I_58(X, __VA_ARGS__)
#define PP_FOREACH_I_60(X, x, ...)  X(x) PP_FOREACH_I_59(X, __VA_ARGS__)
#define PP_FOREACH_I_61(X, x, ...)  X(x) PP_FOREACH_I_60(X, __VA_ARGS__)
#define PP_FOREACH_I_62(X, x, ...)  X(x) PP_FOREACH_I_61(X, __VA_ARGS__)
#define PP_FOREACH_I_63(X, x, ...)  X(x) PP_FOREACH_I_62(X, __VA_ARGS__)
#define PP_FOREACH_I_64(X, x, ...)  X(x) PP_FOREACH_I_63(X, __VA_ARGS__)
#define PP_FOREACH_I_65(X, x, ...)  X(x) PP_FOREACH_I_64(X, __VA_ARGS__)
#define PP_FOREACH_I_66(X, x, ...)  X(x) PP_FOREACH_I_65(X, __VA_ARGS__)
#define PP_FOREACH_I_67(X, x, ...)  X(x) PP_FOREACH_I_66(X, __VA_ARGS__)
#define PP_FOREACH_I_68(X, x, ...)  X(x) PP_FOREACH_I_67(X, __VA_ARGS__)
#define PP_FOREACH_I_69(X, x, ...)  X(x) PP_FOREACH_I_68(X, __VA_ARGS__)
#define PP_FOREACH_I_70(X, x, ...)  X(x) PP_FOREACH_I_69(X, __VA_ARGS__)
#define PP_FOREACH_I_71(X, x, ...)  X(x) PP_FOREACH_I_70(X, __VA_ARGS__)
#define PP_FOREACH_I_72(X, x, ...)  X(x) PP_FOREACH_I_71(X, __VA_ARGS__)
#define PP_FOREACH_I_73(X, x, ...)  X(x) PP_FOREACH_I_72(X, __VA_ARGS__)
#define PP_FOREACH_I_74(X, x, ...)  X(x) PP_FOREACH_I_73(X, __VA_ARGS__)
#define PP_FOREACH_I_75(X, x, ...)  X(x) PP_FOREACH_I_74(X, __VA_ARGS__)
#define PP_FOREACH_I_76(X, x, ...)  X(x) PP_FOREACH_I_75(X, __VA_ARGS__)
#define PP_FOREACH_I_77(X, x, ...)  X(x) PP_FOREACH_I_76(X, __VA_ARGS__)
#define PP_FOREACH_I_78(X, x, ...)  X(x) PP_FOREACH_I_77(X, __VA_ARGS__)
#define PP_FOREACH_I_79(X, x, ...)  X(x) PP_FOREACH_I_78(X, __VA_ARGS__)
#define PP_FOREACH_I_80(X, x, ...)  X(x) PP_FOREACH_I_79(X, __VA_ARGS__)
#define PP_FOREACH_I_81(X, x, ...)  X(x) PP_FOREACH_I_80(X, __VA_ARGS__)
#define PP_FOREACH_I_82(X, x, ...)  X(x) PP_FOREACH_I_81(X, __VA_ARGS__)
#define PP_FOREACH_I_83(X, x, ...)  X(x) PP_FOREACH_I_82(X, __VA_ARGS__)
#define PP_FOREACH_I_84(X, x, ...)  X(x) PP_FOREACH_I_83(X, __VA_ARGS__)
#define PP_FOREACH_I_85(X, x, ...)  X(x) PP_FOREACH_I_84(X, __VA_ARGS__)
#define PP_FOREACH_I_86(X, x, ...)  X(x) PP_FOREACH_I_85(X, __VA_ARGS__)
#define PP_FOREACH_I_87(X, x, ...)  X(x) PP_FOREACH_I_86(X, __VA_ARGS__)
#define PP_FOREACH_I_88(X, x, ...)  X(x) PP_FOREACH_I_87(X, __VA_ARGS__)
#define PP_FOREACH_I_89(X, x, ...)  X(x) PP_FOREACH_I_88(X, __VA_ARGS__)
#define PP_FOREACH_I_90(X, x, ...)  X(x) PP_FOREACH_I_89(X, __VA_ARGS__)
#define PP_FOREACH_I_91(X, x, ...)  X(x) PP_FOREACH_I_90(X, __VA_ARGS__)
#define PP_FOREACH_I_92(X, x, ...)  X(x) PP_FOREACH_I_91(X, __VA_ARGS__)
#define PP_FOREACH_I_93(X, x, ...)  X(x) PP_FOREACH_I_92(X, __VA_ARGS__)
#define PP_FOREACH_I_94(X, x, ...)  X(x) PP_FOREACH_I_93(X, __VA_ARGS__)
#define PP_FOREACH_I_95(X, x, ...)  X(x) PP_FOREACH_I_94(X, __VA_ARGS__)
#define PP_FOREACH_I_96(X, x, ...)  X(x) PP_FOREACH_I_95(X, __VA_ARGS__)
#define PP_FOREACH_I_97(X, x, ...)  X(x) PP_FOREACH_I_96(X, __VA_ARGS__)
#define PP_FOREACH_I_98(X, x, ...)  X(x) PP_FOREACH_I_97(X, __VA_ARGS__)
#define PP_FOREACH_I_99(X, x, ...)  X(x) PP_FOREACH_I_98(X, __VA_ARGS__)

#define PP_FOREACH(X, ...)  PP_OVERLOAD(PP_FOREACH_I_, __VA_ARGS__)(X, __VA_ARGS__)



#endif

