
CMPE 220 INSTRUCTIONS: 
Your goal is to modify your copy of bits.c (as in assignment instructions, select any 5 of the stubs to implement).


*********

0. Files:

*********

README		- This file

bits.c		- The file you will be modifying and handing in

bits.h		- Header file

fshow.c		- Utility for examining floating-point representations

ishow.c		- Utility for examining integer representations


*******************

1. Helper Programs

*******************


We have included the ishow and fshow programs to help you decipher
integer and floating point representations respectively. Each takes 
a single decimal or hex number as an argument. To build them type:

unix> make

Example usages:

    

	unix> ./ishow 0x27
    
	Hex = 0x00000027,	Signed = 39,	Unsigned = 39

    
	
	unix> ./ishow 27
    
	Hex = 0x0000001b,	Signed = 27,	Unsigned = 27

    

	unix> ./fshow 0x15213243
    
	Floating point value 3.255334057e-26
    
	Bit Representation 0x15213243, sign = 0, exponent = 0x2a, fraction = 0x213243
    
	Normalized.  +1.2593463659 X 2^(-85)

    

	linux> ./fshow 15213243
    
	Floating point value 2.131829405e-38
    
	Bit Representation 0x00e822bb, sign = 0, exponent = 0x01, fraction = 0x6822bb
    
	Normalized.  +1.8135598898 X 2^(-126)
