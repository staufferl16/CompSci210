;; Author: Ken Lambert

.ORIG x3000             


; Program code
LD R1, X
ST R1, Y
LD R1, Z
HALT

; Data declarations	
X .BLKW 1
Y .BLKW 2
Z .BLKW 1


.END