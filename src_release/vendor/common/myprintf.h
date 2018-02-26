#ifndef MYPRINTF_H
#define MYPRINTF_H
void mini_printf(const char *format, ...);
void array_printf(u8*data, u8 len);

//#define printf	mini_printf

//#define debugBuffer (*(volatile unsigned char (*)[40])(0x8095d8))
#endif
