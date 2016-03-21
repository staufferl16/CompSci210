;; Author: Leigh Stauffer
;; Project: 6-1

;; This program subtracts the number in the variable SECOND from the number
;; in the variable FIRST and stores the result in the variable DIFF.

		.ORIG x3000

;;pseudocode design:

; FIRST - SECOND = DIFF

;; Main program register usage:
; R1 = FIRST
; R2 = SECOND
; R3 = DIFF

; Main program code
	LD	R1, FIRST	
	LD	R2, SECOND
	NOT	R2, R2, SECOND	; invert SECOND
	ADD	R2, R1, R2	; FIRST + (-SECOND)
	ST	R3, R2, DIFF
	HALT

; Data for the main program
FIRST	.BLKW 1
SECOND	.BLKW 1
DIFF	.BLKW 1

