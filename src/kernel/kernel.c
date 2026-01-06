/*
 * HexagonOS 1.0 - Kernel
 * Main kernel implementation
 */

#include "../include/kernel.h"
#include "../include/stdio.h"
#include "../include/memory.h"

void kernel_main() {
    clear_screen();
    
    print_string("========================================\n");
    print_string("  Welcome to HexagonOS 1.0\n");
    print_string("  A Minimalist Operating System\n");
    print_string("========================================\n\n");
    
    // Initialize subsystems
    print_string("[*] Initializing memory manager...\n");
    memory_init();
    print_string("[+] Memory manager initialized\n\n");
    
    print_string("[*] Initializing IDT...\n");
    idt_init();
    print_string("[+] IDT initialized\n\n");
    
    print_string("[*] Initializing GDT...\n");
    gdt_init();
    print_string("[+] GDT initialized\n\n");
    
    print_string("System ready. Type 'help' for commands.\n");
    print_string("hexagon-os> ");
    
    // Simple shell loop
    shell_loop();
}

void clear_screen() {
    uint8_t *video_memory = (uint8_t *) 0xB8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x07;
    }
    cursor_position = 0;
}

void shell_loop() {
    char buffer[256];
    int position = 0;
    
    while (1) {
        uint8_t key = keyboard_read();
        
        if (key == '\n') {
            print_string("\n");
            buffer[position] = '\0';
            execute_command(buffer);
            print_string("hexagon-os> ");
            position = 0;
        } else if (key == '\b' && position > 0) {
            position--;
            print_string("\b \b");
        } else if (position < 255) {
            buffer[position++] = key;
            print_char(key);
        }
    }
}

void execute_command(const char *cmd) {
    if (cmd[0] == '\0') return;
    
    if (strcmp(cmd, "help") == 0) {
        print_string("Available commands:\n");
        print_string("  help     - Show this help message\n");
        print_string("  clear    - Clear the screen\n");
        print_string("  reboot   - Reboot the system\n");
        print_string("  meminfo  - Display memory information\n");
        print_string("  version  - Show system version\n");
    } else if (strcmp(cmd, "clear") == 0) {
        clear_screen();
    } else if (strcmp(cmd, "version") == 0) {
        print_string("HexagonOS 1.0\n");
    } else if (strcmp(cmd, "meminfo") == 0) {
        print_string("Total Memory: 4096 MB\n");
        print_string("Free Memory: 2048 MB\n");
        print_string("Used Memory: 2048 MB\n");
    } else if (strcmp(cmd, "reboot") == 0) {
        system_reboot();
    } else {
        print_string("Unknown command:  ");
        print_string(cmd);
        print_string("\n");
    }
}

void system_reboot() {
    print_string("Rebooting...\n");
    // Wait for keyboard to be empty
    uint8_t temp;
    do {
        temp = inb(0x64);
    } while ((temp & 0x01) == 0);
    
    inb(0x60);
    // Reset CPU
    outb(0x64, 0xFE);
    __asm__ __volatile__("hlt");
}
