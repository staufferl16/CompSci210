;; Author: Ken Lambert

.ORIG x2000             ; ERROR: start address too low

; Program code	
	LEA R0, PROMPT	; Display the prompt
	PUTS
	LD R1, RT	; Initialize the return character
	LEA R2, ARRAY	; Get the base address of the array

CHLOOP	GETC		; Read and echo a character (stored in R0)
	OUT	
	ADD R3, R0, R1	; Quit if character = return
	BRz ENDMAIN
	STR R0, R2, #0	; Store that character in the array
	ADD R2, R2, #1	; Increment the address of the array cell
	BR CHLOOP	; Return to read another character
CHLOOP  OUT             ; ERROR: duplicate declaration
	
ENDMAIN	STR R3, R2, #0	; Store the null character at the end of the array
	HALT

; Data variables
RT	.FILL 		x-000D	; The return character (negated)
PROMPT	.STRINGZ 	"Enter your name: "
ARRAY	.BLKW 30		; Array of 30 characters (including null)
DATA    .BLKW                   ; ERROR: no integer literal for size

.END