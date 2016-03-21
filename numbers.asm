;; Author: Leigh Stauffer
;; Project: 7-2

;; Defines subroutines for multiplication and converting digits to integers.

	.ORIG x3000

;; Pseudocode design:
;	product = first * second
;	index = 0
;	for digit in "9876543210":
;		integerArray[index] = chrtoint(digit)
;	number = strtoint("8320")

;; Main program register usage:
;	R1 = FIRST
;	R2 = SECOND
;	R3 = TOTAL


;  Program code:
	LD	R1, FIRST
	LD	R2, SECOND
	JSR	MUL
	ST	R3, TOTAL
	JSR	STRTOINT
	HALT



;  Data variables
MFIRST	.FILL	4
MSECOND	.FILL	3
MTOTAL	.BLKW	1

;; Subroutine MUL:
;; Multiplies variables FIRST and SECOND.  Will multiply in the most
;; efficient way possible.
;  Pseudocode for subroutine:
;	TOTAL = 0
;	if FIRST > SECOND:
;		TEMP = FIRST
;		FIRST = SECOND
;		SECOND = TEMP
;	for count in FIRST:
;		TOTAL += SECOND
;	return PRODUCT
;  Subroutine parameters:
;	R1 = FIRST
;	R2 = SECOND
;	R3 = TOTAL
;	R4 = TEMP

MUL	ST	R1, FIRST			; Backing up registers
	ST	R2, SECOND
	ST	R3, TOTAL
	ST	R4, TEMP
	NOT	R3, R1				; Inverting FIRST
	ADD	R3, R3, #1			; 2's complement FIRST
	ADD	R3, R3, R2			; if FIRST > SECOND
	BRzp	PROD
	STR	R4, R1, #0			; TEMP = FIRST
	STR	R1, R2, #0			; FIRST = SECOND
	STR	R2, R4, #0			; SECOND = TEMP

PROD	AND	R3, R3, #0			; clearing TOTAL
AGAIN	ADD	R3, R2, R3			; TOTAL += SECOND
	ADD	R1, R1, #-1			; decrement FIRST
	BRp	AGAIN
ENDMUL	LD	R1, FIRST
	LD	R2, SECOND
	ST	R3, TOTAL
	LD	R4, TEMP
	RET



;  Subroutine data variables:
FIRST	.BLKW	1
SECOND	.BLKW	1
TEMP	.BLKW	1
TOTAL	.BLKW	1

;; Subroutine to CHRTOINT:
;; A type conversion routine that converts an entire string of digits to an integer value.
;  Pseudocode for subroutine:
;	character = input()
;	integerValue = character - 48
;  Subroutine parameters:
;	R1 = base address of string

CHRTOINT	ADD	R1, R1, #-16		; converts from ASCII to integer
		ADD	R1, R1, #-16
		ADD	R1, R1, #-16
		ST	R1, R1CHRTOINT
		RET

;  Data variables:
R1CHRTOINT	.STRINGZ	"9876543210"

;; Subroutine to STRTOINT:
;; Converts an entire string of digits to an integer value.
;  Pseudocolde for subroutine:
;	sum = 0
;	for digit in inputString:
;		sum = 10 * sum + chrtoint(digit)
;  Subroutine parameters:
;	R1 = base address of the string
;	R2 = integer expressed by the digits
;	R3 = string length
;	R4 = 10
;	R5 = working storage
;; Subroutine code:

STRTOINT	ST	R1, BASE		; backing up the registers
		ST	R2, SUM
		ST	R3, LENGTH
		ST	R4, TEN
		ST	R5, WORK
		ST	R7, R7STRTOINT		; backing up R7 (for subroutine JSR)
		AND	R2, R2, #0		; clearing R2
		JSR	STRLEN			; jumping to get string length
		STR	R3, R2, #0		; storing the length
FOR		JSR	MUL			; jumping to MUL
		ST	R2, SUM
		JSR	CHRTOINT		; jumping to CHRTOINT
		ST	R5, WORK		; storing  the CHRTOINT
		ADD	R2, R5, R2		; sum = 10 * sum + chrtoint(digit)
		ADD	R3, R3, #-1		; decrement 10
		BRp	FOR
		LD	R1, BASE
		ST	R2, SUM
		LD	R3, LENGTH
		LD	R4, TEN
		LD	R5, WORK
		LD	R7, R7STRTOINT
		RET

;  Data variables:
BASE		.STRINGZ	"8320"
SUM		.BLKW	1
LENGTH		.BLKW	1
TEN		.FILL	10
WORK		.BLKW	1
R7STRTOINT	.BLKW	1


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
.END
			
