/*
 * Keyboard Driver
 */

#include "../include/keyboard.h"
#include "../include/io.h"

static const uint8_t scancode_table[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*',
    0, ' '
};

uint8_t keyboard_read() {
    uint8_t status;
    uint8_t scancode;
    
    do {
        status = inb(0x64);
    } while ((status & 0x01) == 0);
    
    scancode = inb(0x60);
    
    if (scancode < 128) {
        return scancode_table[scancode];
    }
    
    return 0;
}
