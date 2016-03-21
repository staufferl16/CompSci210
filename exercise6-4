;; Author: Leigh Stauffer
;; Project: 6-4

;; This program manipulates the numbers expressed with the variables SMALLER
;; and LARGER.  When the program halts, the number held in variable SMALLER
;; will be less than the number held in the variable LARGER.

	.ORIG x3000

;; Pseudocode design:

;  if larger - smaller >= 0:
;	smaller = smaller
;	larger = larger
;  else:
;	smaller = larger
;	larger = smaller

;; Main program register usage:
;  R1 = SMALLER
;  R2 = LARGER
;  R3 = COMPARE

;  Main program code
	LD	R1, SMALLER
	LD	R2, LARGER
	NOT	R1, SMALLER		;invert SMALLER
	ADD	R3, R2, R1		;LARGER + (-SMALLER)
	BRn	SWAP			;loop to subroutine if COMPARE is negative
	ST	R1, SMALLER
	ST	R2, LARGER
	HALT

;  Data for the main program
SMALLER		.BLKW 1
LARGER		.BLKW 1
COMPARE		.BLKW 1

;; Subroutine SWAP
;  If COMPARE proves to be negative, the value held by SMALLER will be moved to LARGER and
;  the value held by LARGER will be moved to SMALLER.
;  Working storage R4 used to hold the value of LARGER before moving it to SMALLER.
SWAP	LD	R4, R2		;moving value LARGER to working storage 
	LD	R2, R1		;moving value in SMALLER to register LARGER
	LD	R1, R4		;moving value in working storage to register SMALLER
	RET	
