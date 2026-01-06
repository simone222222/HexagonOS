/*
 * Interrupt Descriptor Table (IDT)
 */

#include "../include/idt.h"

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

void idt_init() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt;
    
    // Set all gates
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, (uint32_t)isr_stub, 0x08, 0x8E);
    }
    
    idt_flush((uint32_t)&idt_ptr);
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num]. base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void isr_stub() {
    __asm__ __volatile__("cli; hlt");
}
