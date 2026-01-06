/*
 * I/O Operations
 */

#include "../include/io.h"

uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ __volatile__("inb %1, %0" :  "=a"(result) : "dN"(port));
    return result;
}

void outb(uint16_t port, uint8_t data) {
    __asm__ __volatile__("outb %1, %0" : : "dN"(port), "a"(data));
}

uint16_t inw(uint16_t port) {
    uint16_t result;
    __asm__ __volatile__("inw %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

void outw(uint16_t port, uint16_t data) {
    __asm__ __volatile__("outw %1, %0" : :  "dN"(port), "a"(data));
}
