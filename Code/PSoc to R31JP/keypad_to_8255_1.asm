; Andrew Xia
; Prof Leeb
; 6.115 Microcontrollers
; Final Project Code

; segment 1: The main loop or body of our typewriter program
.org 00h 				;power up and reset vector
	ljmp start			;when the micro wakes up, jump to the beginning 
						;of the main body or loop in the program, called 'start'
.org 100h				;and located at address location 100h in external mem
start:
	lcall init			;start the serial port by calling subroutine 'init'.	
	loop:				;METHOD: main running loop
		lcall getkey 	; <- gets a character from the pc keyboard
		lcall sndchr 	; -> and then echoes the character to the PC screen
		lcall sndpsoc	;this function sends acc val to psoc
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
	mov scon, #50h
	
	mov R0, #00h		;register to track address high bit
	mov R1, #00h		;register to store address low bit
	mov R2, #03h		;register for counting down from 3 inputs before needing a new line
	mov R3, #02h		;register to determine whether to enter calculations or not
	
	mov P1, #0fh		;initialize lower 4 bits of P1 as an input
	setb P3.3			;p3.3 is the data available input
	clr P3.2			;set data enable to ground
	
	mov dptr, #0fe33h	;move dptr to 8255 config port
	mov a, #80h			;configure 8255 to be input all
	movx @dptr, a
	mov dptr, #0fe30h	;move dptr to 8255 port A
	mov a, #30h			;print a 0 to start
	movx @dptr, a		;move keypad press to 8255
	
	ret		

;segment 3 getkey routine
getkey:				;get value from keypad
	jnb P3.3, getkey;wait till key pressed down
	mov a, P1
	lcall keytab	;map key press to according number	
	add a, #30h		;convert numerical to ascii
	press:
		jb P3.3, press	;wait in the loop until key released
	ret
	
keytab:			;input: press on keypad. output: numerical value (not ascii)
	inc a
	movc a, @a+pc
	ret
	.DB 1,2,3,251,4,5,6,253,7,8,9,12,13,0,14,15	;251 is +, 253 is -
	
;segment 4 sndchr routine
sndchr:
	clr scon.1		;clear the ti complete flag
	mov sbuf,a		;move a character from acc to the sbuf
txloop:
	jnb scon.1, txloop ;wait till chr is sent
	ret
	