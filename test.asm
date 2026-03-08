org 0x7C00
bits 16

start:
	jmp main

puts:
	push ax
	push bx
	push si
.loop:
	lodsb
	or al, al
	jz .done
	mov ah, 0x0E
	mov bh, 0x07
	int 0x10
	jmp .loop
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
	call puts

	hlt
.loop_main:
	jmp .loop_main

msg db "Test Message", 0x0A, 0x0D, 0x00
times 510-($-$$) db 0
dw 0xAA55
[UPDATE TAG: 8429292771]
