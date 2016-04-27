; Andrew Xia
; 6.115
; Apri; 27 2016
; Testing 8051 to vga

.org 0h
ljmp start

.org 100h
start:
    lcall init      ;initialize baud connection
    
    mov a, #80h
    lcall sndchr    

    mov a, #0x80
    acall sndchr            ; set resolution 16x12
    mov dptr, #data
    acall sndimg            ; send the image

sndchr: 
    ;;; sndchr: send accumulator contents over the serial port.
    clr ti
    mov sbuf, a
waitloop:
    jnb ti, waitloop        ; wait until the byte is sent
    ret

sndimg: 
    ;;; sndimg: send the image currently pointed to by dptr.
    movx a, @dptr           ; load the next data byte
    cjne a, #0xff, *+4      ; jump over the ret unless at end of image
    ret
    acall sndchr            ; send the data byte
    inc dptr
    sjmp sndimg
    ;;; data: the image itself, terminated by 0xff.
data: ;192 values to feed in
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch, 30h, 0ch
    .db 0ffh
    
    
;=================================================================
; subroutine init
; this routine initializes the hardware
; set up serial port with a 11.0592 MHz crystal,
; use timer 1 for 19200 baud serial communications
;=================================================================
init:
   orl   pcon, #80h       ; set smod = 1 so k =2 for 19200 baud
   mov   tmod, #20h       ; set timer 1 for auto reload - mode 2
   mov   tcon, #41h       ; run counter 1 and set edge trig ints
   mov   th1,  #0fdh      ; set 19200 baud with xtal=11.059mhz
   mov   scon, #50h       ; set serial control reg for 8 bit data
                          ; and mode 1
   ret

;sends a char
; sndchr:
   ; clr  scon.1            ; clear the tx  buffer full flag.
   ; mov  sbuf,a            ; put chr in sbuf
; txloop:
   ; jnb  scon.1, txloop    ; wait till chr is sent
   ; ret