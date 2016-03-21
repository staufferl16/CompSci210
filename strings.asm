;; Author: Leigh Stauffer
;; Project: 7-1

;; Defines subroutines for some string manipulations.

	.ORIG x3000

;; Pseudocode design:
;	inputString = input("Enter a string: ")
;	length = str
;	len(inputString)
;	print(inputString)
;	inputString = reverse(inputString)
;	print(inputString)


;; Register usage:
; R1 = the base address of the array
; R2 = length of the string
; R3 = temporary working storage

; Program code	
        LEA     R0, PROMPT	; Display the prompt
	PUTS
	LEA     R1, ARRAY	; Get the base address of the array
	LD      R4, RT	        ; Initialize the return character
	JSR	STRLEN		; Jump to subroutine STRLEN
	ST	R2, LENGTH	; Storing the string's length
	JSR	REV		; Jump to subroutine REV to reverse string
	PUTS
	JSR	GETS
	LEA	R0, ARRAY	; Output the string
	PUTS
	
	HALT

; Data variables
RT	.FILL 	x-000D	        ; The return character (negated)
PROMPT	.STRINGZ "Enter a string: "
LENGTH	.BLKW	1
ARRAY	.BLKW 30		; Array of 30 characters (including null)


;; Subroutine STRLEN
;; Return the len of the input string
;  Pseudocode for subroutine:
;	INDEX = 0
;	SUM = 0
;	while STRING[INDEX] != NULL:
;		SUM += 1
;		INDEX += 1
;  Parameters	R1 = base address of the string array
;		R2 = output parameter
;		R3 = temporary working register

STRLEN	ST	R1, R1STRLEN		; Backing up the registers
	ST	R3, R3STRLEN
	AND	R2, R2, #0		; Set output parameter to 0

COUNT	LDR	R3, R1, #0		
	BRz	ENDCOUNT
	ADD	R2, R2, #1		; Increment sum by one (SUM += 1)
	ADD	R1, R1, #1		; Increment the string position
	BR	COUNT

ENDCOUNT	LD	R1, R1STRLEN
		LD	R3, R3STRLEN
		RET

;  Subroutine Data Variables
R1STRLEN	.BLKW	1
R3STRLEN	.BLKW	1

;; Subroutine REV
;; Returns a string with its characters in reverse order. 
;  Pseudocode for subroutine:
;	FRONT = 0
;	REAR = LENGTH
;	while FRONT < REAR:
;		TEMPVAR = STRING[FRONT]
;		STRING[FRONT] = STRING[REAR]
;		FRONT += 1
;		REAR += -1
;  Subroutine parameters:
;	R1 = FRONT
;	R2 = REAR
;	R3 = STRING[FRONT] & working storage
;	R4 = STRING[REAR]

REV	ST	R1, R1REV			; Backing up the registers
	ST	R2, R2REV
	ST	R3, R3REV
	ST	R4, R4REV
	ST	R7, R7REV
	JSR	STRLEN				
	ADD	R2, R2, #-1			; Get the string length
	ADD	R2, R1, R2			; Set up REAR [FRONT + (LENGTH-1)]

WHILE	NOT	R3, R1
	ADD	R3, R3, #1
	ADD	R3, R3, R2
	BRnz	ENDREV				; If diff of FRONT and REAR = 0, end loop
	LDR	R3, R1, #0			; Load STRING[FRONT] into storage
	LDR	R4, R2, #0			; Load REAR into STRING[REAR]
	STR	R3, R2, #0			; swap REAR value and STRING[FRONT]
	STR	R4, R1, #0			; swap FRONT and STRING[REAR]
	ADD	R1, R1, #1			; Increment FRONT
	ADD	R2, R2, #-1			; Decrement REAR
	BR	WHILE				; Return to REV for FRONT and REV comparison

ENDREV	LD	R1, R1REV			; Backing up the registers
	LD	R2, R2REV
	LD	R3, R3REV
	LD	R4, R4REV
	LD	R7, R7REV			; Backing up R7 for return to main loop
	RET

;  Subroutine REV Data Variables
R1REV		.BLKW	1
R2REV		.BLKW	1
R3REV		.BLKW	1
R4REV		.BLKW	1
R7REV		.BLKW	1

;; Subroutine GETS
;; Stores characters input from the keyboard into the array and return when the user presses
;; a newline key or when the array becomes full (including the null character at the end).
;  Pseudocode for subroutine:
;	INDEX = 0
;	DO
;	CH = GETC()
;	PUTC (CH)
;	IF CH == RETURN:
;		STRING[INDEX] = 0
;		BREAK
;	STRING[INDEX] = CH
;	INDEX += 1
;	WHILE INDEX < UPPER - 1
;	IF CH != RETURN:
;		STRING[INDEX + 1] = 0
;  Subroutine parameters:
;	R0 = the input character
;	R1 = base address of the array
;	R2 = LENGTH of the string
;	R3 = temporary working storage
;	R4 = newline character

GETS	ST	R0, R0GETS				; Backing up registers
	ST	R1, R1GETS
	ST	R2, R2GETS
	ST	R3, R3GETS
	ST	R4, R4GETS
	ST	R7, R7GETS

WGETS	GETC
	OUT						; Read and echo a character (stored in R0)
	ADD	R3, R0, R4				; Quit if character = return
	BRz	ENDGETS
	JSR	STRLEN					; LENGTH put in R2
	NOT	R1, R1					; make length negative for camparison
	ADD	R1, R1, #1				; add 1 for 2's Complement
	ADD	R3, R1, R2				; compare ARRAY and LENGTH - break if 0
	BRnz	ENDGETS
	STR	R0, R1, #0				; Store that character in the array
	ADD	R1, R1, #1				; Increment the address of the array cell
	BR	WGETS					; Return to read another character

ENDGETS	STR	R3, R1, #0				; Store the null after the last input
	LD	R0, R0GETS				; Restore registers
	LD	R1, R1GETS
	LD	R2, R2GETS
	LD	R3, R3GETS
	LD	R4, R4GETS
	LD	R7, R7GETS				; Backing up R7 for return to main loop
	RET

;  Subroutine GETS Data Variables:
R0GETS	.BLKW	1
R1GETS	.BLKW	1
R2GETS	.BLKW	1
R3GETS	.BLKW	1
R4GETS	.BLKW	1
R7GETS	.BLKW	1	
		
.END	

