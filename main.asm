org 0x7C00
bits 16

start:
	jmp main

strput:
	push ax
	push bx
	push si
.do:
	lodsb
	or al, al
	jz .done
	mov ah, 0x0E
	mov bx, 0
	int 10h
	jmp .do
.done:
	pop ax
	pop bx
	pop si
	ret

main:
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00
	mov si, msg
	call strput
	hlt
.halt:
	jmp .halt

msg db "Hello, World!", 0x0A, 0x0D, 0x00
times 510-($-$$) db 0
dw 0xAA55


























































































