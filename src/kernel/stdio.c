/*
 * Standard I/O
 */

#include "../include/stdio.h"

static uint32_t cursor_position = 0;

void print_char(char c) {
    uint8_t *video_memory = (uint8_t *)0xB8000;
    
    if (c == '\n') {
        cursor_position = (cursor_position + 80) - (cursor_position % 80);
    } else {
        video_memory[cursor_position * 2] = c;
        video_memory[cursor_position * 2 + 1] = 0x07;
        cursor_position++;
    }
    
    if (cursor_position >= 80 * 25) {
        scroll_screen();
    }
}

void print_string(const char *str) {
    while (*str) {
        print_char(*str++);
    }
}

void print_int(int num) {
    if (num < 0) {
        print_char('-');
        num = -num;
    }
    
    char buffer[32];
    int i = 0;
    
    if (num == 0) {
        print_char('0');
        return;
    }
    
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    
    while (i > 0) {
        print_char(buffer[--i]);
    }
}

void print_hex(uint32_t num) {
    const char *hex_chars = "0123456789ABCDEF";
    print_string("0x");
    
    for (int i = 28; i >= 0; i -= 4) {
        print_char(hex_chars[(num >> i) & 0xF]);
    }
}

void scroll_screen() {
    uint8_t *video_memory = (uint8_t *)0xB8000;
    
    // Move everything up one line
    for (int i = 0; i < (80 * 24) * 2; i += 2) {
        video_memory[i] = video_memory[i + 160];
        video_memory[i + 1] = video_memory[i + 161];
    }
    
    // Clear last line
    for (int i = (80 * 24) * 2; i < (80 * 25) * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x07;
    }
    
    cursor_position = 80 * 24;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int strlen(const char *str) {
    int len = 0;
    while (*str++) len++;
    return len;
}
