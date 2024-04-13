@R0
D = M
@n
M = D			// n = RAM[0]

@i
M = 0			// i = 0

@SCREEN
D = A
@address
M = D			// address = 16384 (base address of the Hack screen)

(LOOP)
   @i
   D = M
   @n
   D = D - M
   @END
   D;JGT		// if i > n goto END

   @address
   A = M		// writing to memory using a pointer
   M = -1		// RAM[address] = -1 (16 pixels)
 
   @i
   M = M + 1	// i = i + 1
   @32
   D = A
   @address
   M = D + M	// address = address + 32
   @LOOP
   0;JMP		// goto LOOP

  (END)
     @END		// program's end
     0;JMP		// infinite loop
