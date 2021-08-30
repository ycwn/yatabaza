

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



#endif

