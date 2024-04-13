	@SCREEN
	D=A
	@addr
	M=D		// addr = 16384 (screen base address)

	@0
	D=M
	@n
	M=D		// n = RAM[0]

	@i
	M=0 	// i = 0

(LOOP)
	@i
	D=M
	@n
	D=D-M
	@END
	D;JGT		// if i > n goto END

	@addr
	A=M
	M=-1 	// RAM[addr] = 1111111111111111

	@i
	M=M+1
	@32
	D=A
	@addr
	M=D+M 	// addr = addr + 32
	@LOOP
	0;JMP 	// goto LOOP

(END)
	@END
	0;JMP
