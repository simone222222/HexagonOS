/*
 * Memory Management
 */

#include "../include/memory.h"
#include "../include/stdio.h"

#define HEAP_START 0x10000
#define HEAP_SIZE  0x100000

static uint8_t heap[HEAP_SIZE];
static uint32_t heap_offset = 0;

void memory_init() {
    heap_offset = 0;
}

void *malloc(uint32_t size) {
    if (heap_offset + size > HEAP_SIZE) {
        return NULL;
    }
    
    void *ptr = (void *)(HEAP_START + heap_offset);
    heap_offset += size;
    
    return ptr;
}

void free(void *ptr) {
    // Simple allocator - no true deallocation yet
    (void)ptr;
}

void memcpy(void *dest, const void *src, uint32_t size) {
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    
    for (uint32_t i = 0; i < size; i++) {
        d[i] = s[i];
    }
}

void memset(void *ptr, uint8_t value, uint32_t size) {
    uint8_t *p = (uint8_t *)ptr;
    
    for (uint32_t i = 0; i < size; i++) {
        p[i] = value;
    }
}
