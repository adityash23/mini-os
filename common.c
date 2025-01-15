#include "common.h"

void putchar(char ch);

void printf(const char *fmt, ...) {
	va_list vargs;
	va_start(vargs, fmt);

	while (*fmt) {
		if (*fmt == '%') {
			fmt++; // skip % sign
			switch (*fmt) {
				case '\0' : // % at the end of string to print
					putchar('%');
					goto end; // finished processing string
				case '%' :
					putchar('%');
					break;
				case 's' : { // printing a string
					const char *s = va_arg(vargs, const char *);
					while (*s) {
						putchar(*s);
						s++;
					}
					break;
				}
				case 'd' : { // printing an integer in decimal format
					int value = va_arg(vargs, int);
					if (value < 0) {
						putchar('-');
						value = -value;
					}

					// extracting the digits one by one as per decimal convention
					int divisor = 1;
					while (value / divisor > 9) { 
						divisor *= 10;
					}

					while (divisor > 0) {
						putchar('0' + value / divisor);
						value %= divisor;
						divisor /= 10;
					}

					break;
				}
				case 'x' : { // printing an integer in hexadecimal format
					int value = va_arg(vargs, int);
					for (int i = 7; i >= 0; i--) {
						int nibble = (value >> (i * 4)) & 0xf; // finding which digit to print
						putchar("0123456789abcdef"[nibble]); // convert digit b/w 0 and 15 to hexa
					}
				}
			}
		}
		else {
			putchar(*fmt);
		}

		fmt++;
	}

end :
	va_end(vargs);
}

// copy 'n' bytes from src to dst
void *memcpy(void *dst, const void *src, size_t n) {
	uint8_t *d = (uint8_t *) dst;
	const uint8_t *s = (const uint8_t *) src;
	while (n--) {
		*d++ = *s++;
	}
	return dst;
}

void *memset(void *buf, char c, size_t n) {
	uint8_t *p = (uint8_t *) buf;
	while (n--) {
		*p++ = c;
		// expanded version of above expression
		/*
		 *p = c;
		 p = p + 1;
		 */
	}
	return buf;
}

char *strcpy(char *dst, const char *src) {
	char *d = dst;
	while (*src) {
		*d++ = *src++; // *d = *src and then increment both
	}
	*d = '\0';
	return dst;
}

int strcmp(const char *s1, const char *s2) {
	while (*s1 && *s2) {
		if (*s1 != *s2) {
			break;
		}
		s1++;
		s2++;
	}

	return *(unsigned char *)s1 - *(unsigned char *)s2;
}
