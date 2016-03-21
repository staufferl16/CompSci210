;; Author: Leigh Stauffer
;; Project: 6-2

;; This program computes the sum of 5 numbers in the array named LIST and stores
;; this sum in the variable named SUM.

	ORIG. x3000

;;Pseudocode design:
; sum(LIST) = SUM

;; Main program register usage:
;  R1 = base address of array
;  R2 = logical size of array
;  R3 = sum of numbers in array

; Main program code
	LEA	R1, LIST
	LD	R2, SIZE
	JSR	SUM
	ST	R3, SUM
	HALT

; Data for main program
ARRAY	.BLKW 10
SIZE	.FILL 5
THESUM	.BLKW 1

;; Subroutine SUM
;  Returns the sum of the values in the array LIST
;  Parameters R4 = index
;	      R2 = array size
;	      R1 = base address of array
;  Return value R3 = the sum of the values in LIST
;  Working storage R4 used for temporary variable of an array's value at position index

SUM	ST	R1, R1SUM	; Back up the registers
	ST	R2, R2SUM
	ST	R4, R4SUM
	AND	R3, R3, #0	; Set the inital sum register to zero

WHILE	ADD	R2, R2, #-1	; While logical size > 0
	BRz	ENDSUM
	ADD	R1, R1, #1	; index += 1
	LDR	R4, R1, #0	; temp = array[index]
	ADD	R3, R4		; adding temp to SUM
	BRnzp	WHILE

ENDSUM	LD	R4, R4SUM	;Restor the registers
	LD	R3, R3SUM
	LD	R2, R2SUM
	LD	R1, R1SUM
	RET

;; Data for subroutine SUM
R1SUM	.BLKW 1
R2SUM	.BLKW 1
R3SUM	.BLKW 1
R4SUM	.BLKW 1
	


