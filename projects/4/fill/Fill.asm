// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.

	@start
	M=0

(LOOP)
	@KBD
	D=M
	@WHITE
	D;JEQ // if keyboard value == 0, goto WHITE
	@BLACK
	0;JMP // otherwise goto BLACK

(WHITE)
	@start
	D=M
	@LOOP
	D;JLT // goto loop if less than 0

	@start
	D=M
	@SCREEN
	A=A+D // calculate place on the screen
	M=0 // fill pixel with white
	@start
	M=M-1
	@LOOP
	0;JMP

(BLACK)
	@start
	D=M
	@8192
	D=D-A
	@LOOP
	D;JGE // goto LOOP if at max (start - 8191 >= 0)
	@start
	D=M
	@SCREEN
	A=A+D // calculate start place
	M=-1 // fill with black
	@start
	M=M+1
	@LOOP
	0;JMP

(END)
	@END
	0;JMP
