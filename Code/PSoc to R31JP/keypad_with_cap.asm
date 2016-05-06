; Andrew Xia
; Prof Leeb
; 6.115 Microcontrollers
; Final Project Code

; segment 1: The main loop or body of our typewriter program
.org 00h 				;power up and reset vector
	ljmp start			;when the micro wakes up, jump to the beginning 
						;of the main body or loop in the program, called 'start'
						
.org 03h ;this is the P3.2 IE0 interrupt loc
	mov a, #30h			;print a 0
	lcall sndchr
	reti

.org 13h ;this is the P3.3 IE1 interrupt loc
	mov a, P1
	lcall keytab	;map key press to according number	
	add a, #30h		;convert numerical to ascii )and beyond)
	lcall sndchr
	lcall sndpsoc
	reti
		
.org 100h				;and located at address location 100h in external mem
start:
	lcall init			;start the serial port by calling subroutine 'init'.	
	loop:				;METHOD: main running loop
		sjmp loop
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

sndpsoc:
	mov dptr, #0fe30h	;move dptr to 8255 port A
	movx @dptr, a		;move keypad press to 8255
	mov R0, #080h
	bob:
		bob1: djnz R1, bob1 ;wait some more
		djnz R0, bob	;wait a bit
	mov a, #00h
	movx @dptr, a		;go back to our default 8255 state of 0
	ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;segment 2: init routine
init:
;set up serial port with a 11.0592 MHz crystal
;use timer 1 for 9600 baud serial commuications
	mov tmod, #20h 
	mov tcon, #40h
	mov th1, #0FDh
	mov scon, #50h		;set up serial connection
	
	mov R0, #00h		;register to track address high bit
	mov R1, #00h		;register to store address low bit
	mov R2, #03h		;register for counting down from 3 inputs before needing a new line
	mov R3, #02h		;register to determine whether to enter calculations or not
	
	mov P1, #0fh		;initialize lower 4 bits of P1 as an input
	setb tcon.0			;detect high edge for P3.2
	setb tcon.2			;detect high edge for P3.3
	mov IE, #85h		;allow for Ext int 0/1 which is p3.2/3
	
	mov dptr, #0fe33h	;move dptr to 8255 config port
	mov a, #80h			;configure 8255 to be input all
	movx @dptr, a
	mov dptr, #0fe30h	;move dptr to 8255 port A
	mov a, #30h			;print a 0 to start
	movx @dptr, a		;move keypad press to 8255
	
	mov dptr, #0fe13h	;move dptr to 8254 config port
	mov a, #36h			;configure 8254 clock 0 mode 2 ?
	movx @dptr, a
	mov dptr, #0fe10h	;move dptr to 8254 port 0
	mov a, #23h			;config for 34khz random generator LOw
	movx @dptr, a		
	mov a, #01h			;config for 34khz random generator HIGH
	movx @dptr, a		
	
	ret		

;segment 3 getkey routine
getkey:				;get value from keypad
	jnb P3.3, getkey;wait till key pressed down
	mov a, P1
	lcall keytab	;map key press to according number	
	add a, #30h		;convert numerical to ascii )and beyond)
	press:
		jb P3.3, press	;wait in the loop until key released
	ret
keytab:			;input: press on keypad. output: numerical value (not ascii)
	inc a
	movc a, @a+pc
	ret
	.DB 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 ;keypad as in relation to 3D ttc
	
;segment 4 sndchr routine
sndchr:
	clr scon.1		;clear the ti complete flag
	mov sbuf,a		;move a character from acc to the sbuf
txloop:
	jnb scon.1, txloop ;wait till chr is sent
	ret
	