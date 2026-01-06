; HexagonOS 1.0 - Bootloader
; Simple x86 bootloader

[BITS 16]
[ORG 0x7C00]

start:
    cli                          ; Disable interrupts
    mov ax, 0x0000
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti                          ; Enable interrupts
    
    ; Display boot message
    mov si, boot_msg
    call print_string
    
    ; Load kernel
    mov ah, 0x02                 ; Read sectors
    mov al, 10                   ; Number of sectors to read
    mov ch, 0                    ; Cylinder
    mov cl, 2                    ; Sector
    mov dh, 0                    ; Head
    mov dl, 0x80                 ; Drive (first hard drive)
    mov bx, 0x1000              ; Load address
    int 0x13
    
    jmp 0x1000                   ; Jump to kernel

print_string:
    mov ah, 0x0E                 ; TTY output
. loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp . loop
.done:
    ret

boot_msg: 
    db 'HexagonOS 1.0 Booting... ', 0x0D, 0x0A, 0

times 510 - ($ - $$) db 0
dw 0xAA55                        ; Boot signature
