;; Author: Leigh Stauffer
;; Project: 6-3

;; This program performs multiplication.  The program multiplies the variable FIRST
;; by the variable SECOND and stores the result in the variable PRODUCT.

	.ORIG x3000

;; Pseudocode design:

;  PRODUCT = FIRST * SECOND

;; Main program register usage:
;  R1 = FIRST
;  R2 = SECOND
;  R3 = PRODUCT

;; Main program code
	LD	R1, FIRST
	LD	R2, SECOND
	AND	R3, R3, #0
	JSR	AGAIN
	ST	R3, PRODUCT
	HALT

;; Data for the main program:
FIRST	.BLKW 1
SECOND	.BLKW 1
PRODUCT .BLKW 1

;; Subroutine:
;
AGAIN	ADD	R3, R3, R2
	ADD	R1, R1, #-1	; R1 keeps track of the iteration
	BRp	AGAIN
	RET
