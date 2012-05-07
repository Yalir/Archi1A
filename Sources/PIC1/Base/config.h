
#ifndef CONFIG_H
#define CONFIG_H

#include <p18cxxx.h>

#if defined(__18F6680)
	#define PIC_ID 1
#elif defined(__18F8680)
	#define PIC_ID 2
#else
	#error Undefined PIC
#endif

#define PIC1_ONLY if (PIC_ID == 1)
#define PIC2_ONLY if (PIC_ID == 2)

#endif
