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
		;push ACC		;this should push the value
		lcall sndchr 	; -> and then echoes the character to the PC screen
		lcall sndpsoc	;this function sends acc val to psoc
		;djnz R2, loop	;jump back to loop if not 64 lines
		;ljmp endline
		
		sjmp loop
		
	endline:			;METHOD: called after the 3 digit number has been inputed
		mov R2, #03h	;reset the counter
		lcall newline
		djnz R3, loop ;go to +/- operation but only every other time we do new line
		ljmp calculate	;do the actual calculation
		
	back:	
		mov R3, #02h	;reset calculate counter
		mov R5, #00h	;reset r5
		mov R6, #00h	;reset r6
		ljmp loop
	
	newline:
		mov a, #10d 	;line feed
		lcall sndchr
		mov a, #13d 	;carriage return
		lcall sndchr
		ret
	
	calculate:
		lcall getval	;get second number out of stack
		mov A, r5		;move second number to r6
		mov r6, A
		lcall getval	;get first number out of stack	
		
		lcall getkey	;get + or -
		clr c
		mov r4, A		;store the operation sign in r4
		lcall sndchr
		lcall newline	
		mov A, r4		;move operation sign back to accumulator
		subb A, #43d	;is it a + sign?
		jz addition
		subb A, #02d	;is it a - sign?
		jz subtraction
		ljmp back		;else no operation
		
	addition:
		mov A, r5		;move second value to A 
		addc A, r6		;add first value to second value
		clr c
		;mov P1, A		;display on LED
		ljmp printresult
	
	subtraction:
		mov A, r5
		subb A, r6
		clr c
		;mov P1, A
		ljmp printresult 
	
	printresult:		;this method unpacks what is in A and 
						;outputs the ASCII numerical value onto terminal
		mov b, #10d
		div ab			;b will become the 1s digit, a will have been divided by 10
		clr c
		mov r4, b		;temporarily store the 1s digit in r4
		mov b, #10d
		div ab			;b will become the 10s digit
		
		add a, #30h		;convert number to ascii
		lcall sndchr	;print out the 100s
		mov a, b
		add a, #30h
		lcall sndchr	;print out the 10s
		mov a, r4		
		;mov P1, A		;light up the 1s digit
		add a, #30h
		lcall sndchr	;print out the 1s
		lcall newline
		ljmp back
	
	getval:				;gets the past 3 numbers in the stack and converts to its value from ascii
						;output in R5
		pop ACC
		mov R0, A
		pop ACC
		mov R1, A
		
		pop ACC			;1s digit
		subb A, #48d	;convert ascii to numerical value
		clr c			;clr the carry bit
		mov r5, A
		
		pop ACC			;10s 
		subb A, #48d 	;convert ascii to value
		mov b, #10d
		mul ab			;multiply tens digit by 10
		clr c
		add A,r5		;add tens digit to sum
		mov r5, A		;move back into r5
		
		pop ACC			;100s
		subb A, #48d 	;convert ascii to value
		mov b, #100d	
		mul ab			;multiply the 100s digit by 100
		clr c
		add A, r5
		mov r5, A
				
		mov A,R1
		push ACC
		mov A,R0
		push ACC
		ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

sndpsoc:
	mov dptr, #0fe30h	;move dptr to 8255 port A
	movx @dptr, a		;move keypad press to 8255
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
	