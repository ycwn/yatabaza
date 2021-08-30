

#ifndef CORE_KERNEL_H
#define CORE_KERNEL_H


void panic() __attribute__((noreturn));


#define CRITICAL_SECTION(...)                                         \
	do {                                                          \
		UBaseType_t irq_mask = taskENTER_CRITICAL_FROM_ISR(); \
		do {                                                  \
			__VA_ARGS__                                   \
		} while (0);                                          \
		taskEXIT_CRITICAL_FROM_ISR(irq_mask);                 \
	} while (0)


#endif

