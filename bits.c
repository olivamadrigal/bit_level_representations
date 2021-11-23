int bitAnd(int, int);
int test_bitAnd(int, int);
int getByte(int, int);
int test_getByte(int, int);
int logicalShift(int, int);
int test_logicalShift(int, int);
int bitCount(int);
int test_bitCount(int);
int bang(int);
int test_bang(int);
int tmin();
int test_tmin();
int fitsBits(int, int);
int test_fitsBits(int, int);
int divpwr2(int, int);
int test_divpwr2(int, int);
int negate(int);
int test_negate(int);
int isPositive(int);
int test_isPositive(int);
int isLessOrEqual(int, int);
int test_isLessOrEqual(int, int);
int ilog2(int);
int test_ilog2(int);
unsigned float_neg(unsigned);
unsigned test_float_neg(unsigned);
unsigned float_i2f(int);
unsigned test_float_i2f(int);
unsigned float_twice(unsigned);
unsigned test_float_twice(unsigned);


#include "fshow.h"




/*
 * < Samira C. Oliva Madrigal -- >
 * 
 * bits.c - Source file with my solutions to the Lab.
 * 
 */

/********************** BIT MANIPULATIONS ***********************/
/* 
 *   logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating:  3
 */
int logicalShift(int x, int n)
{
    /* Unlike an arithmetic shift, a logical shift does not preserve a number's sign bit or distinguish a number's exponent from its significand (mantissa); every bit in the operand is simply moved a given number of bit positions, and the vacant bit-positions are filled, usually with zeros (contrast with a circular shift).
     */
    
    return (x >> n);
}


/********************** BIT MANIPULATIONS ***********************/
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
// REFERENCES: Hacker's Delight -- Henry S. Warren
int bitCount(int x)
{
    //divide & conque of adjacent bit fields
    //simplified using first two terms of formula:
    //   pop(x) = x - floor(x/2) - floor(x/4) - ... - floor(x/2ˆ31)
    //   which gives the number of 1s in the number x
    //   apply first two terms in parallel on each 2-bit field
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    
    return (x & 0x0000003F);

}

/********************** TWO'S COMPLEMENT MANIPULATIONS ***********************/
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x)
{
    
    //assuming int x is 32-bits
    //In 32-bit system: range of values using Two's Complement is:
    //  -(2ˆ(32-1))  to + (2ˆ(32-1) - 1) ===>     -2,147,483,648 to +2,147,483,647
    //last bit will be either a 1 if negative or a 0 if positive
    //return 1 if (+) or 0 otherwise

    int signBit = (x >> 31);
    
    return(!signBit);    
}

/********************** TWO'S COMPLEMENT MANIPULATIONS ***********************/
/*
 *   isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
    int two_compx    = (~y) + 1;
    int result1      = x + two_compx; // x - y
    int two_compy    = (~x) + 1;
    int result2      = y + two_compy; // y - x
    
    int MSBres1      = result1 >> 31;
    int MSBres2      = result2 >> 31;
    
    /*
     x < y <-->   MSB(result1)=1 & MSB(result2) = 0
     x > y <-->   MSB(result1)=0 & MSB(result2) = 1
     x = y <-->   MSB(result1)=0 & MSB(result2) = 0
     
     if(x <= y) return (!MSB(result1) & !MSB(result2) ) | (MSB(result1) & !MSB(result2) ).
     */

    return ( ((!MSBres1) & (!MSBres2)) | ((MSBres1) & (!MSBres2)) );
    
}

/********************** FLOATING-POINT OPERATIONS ***********************/
/* 
 *   float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops:
     Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
// REFERENCES: https://users.cs.duke.edu/~raw/cps104/TWFNotes/floating.html
unsigned float_i2f(int x)
{
    
    //clear sign bit 31 [s] because unsigned int
    unsigned result = 0; //just set to 0 since positive numbers only
    
    //Conversion from Decimal to Floating Point Representation
    //IEEE 754 floating-point standard.
    // Single precision 32-bit floating point number [s:1bit][exponent:8bits][mantissa:23bits]

    unsigned mantissa = x; //bits 22:0 [number to left of decimal point]
    
    //count the number of bits used to represent x
    int base10 = x;
    int xbits  = 0;
    while (base10)
    {
            xbits  = xbits + 1;
            base10 = base10 >> 1; //divide by 2
    }

    mantissa = mantissa << (22 - (xbits - 2)); //left align mantissa up to bit 22
                                               //discard MSB of mantissa
    mantissa = mantissa & (0x007fffff);//clear all  bits to the left of bit 22
    
    unsigned exp = (xbits - 1) + 127;//bits 30:23
    exp = exp << 23; //align up to bit 30
    
    result = (result | mantissa | exp);
    
    return  result;
}


int main(void)
{
    int result;
    char *res;
    
    printf("*Bit Manipulations function \"logicalShift\": \n");
    int n = 24;
    printf("%d >> 4 = %d\n", n, logicalShift(n,4)); // 11000 >> 4 = 0 means => 00001
    n = 128;
    printf("%d >> 4 = %d\n", n, logicalShift(n,4)); // 11000 >> 4 = 0 means => 00001
    n =  256;
    printf("%d >> 4 = %d\n", n, logicalShift(n,4)); // 11000 >> 4 = 0 means => 00001

    
    printf("\n\n*Bit Manipulation function \"bitCount\": \n");
    int num = 33;
    printf("TEST 1: There are %d 1s in %d.\n", bitCount(num), num);
    num = 128;
    printf("TEST 2: There are %d 1s in %d.\n", bitCount(num), num);
    num = 15;
    printf("TEST 3: There are %d 1s in %d.\n", bitCount(num), num);
    num = -50;
    printf("TEST 3: There are %d 1s in %d.\n", bitCount(num), num);
    

    printf("\n\n*Two's Complement function \"isPositive\": \n");
    printf("sizeof(int) %lu bytes.\n", sizeof(int));
    n = 128;
    printf("Is %d positive? result is = %d\n",n, isPositive(n));
    n = -4000;
    printf("Is %d positive? result is = %d\n",n, isPositive(n));
    
    printf("\n\n*Two's Complement function \"isLessOrEqual\": \n");
    int x, y;
    
    x = 10; y = 1;
    result   = isLessOrEqual(x,y);
    res      = (result)?"yes":"no";
    printf("TEST1: %d <= %d? %s\n", x, y, res);
    x = -1; y = -10;
    result   = isLessOrEqual(x,y);
    res      = (result)?"yes":"no";
    printf("TEST2: %d <= %d? %s\n", x, y, res);
    x = 10; y = 10;
    result   = isLessOrEqual(x,y);
    res      = (result)?"yes":"no";
    printf("TEST3: %d <= %d? %s\n", x, y, res);
    x = 5; y = 51;
    result   = isLessOrEqual(x,y);
    res      = (result)?"yes":"no";
    printf("TEST4: %d <= %d? %s\n", x, y, res);
    x = -5; y = -1;
    result   = isLessOrEqual(x,y);
    res      = (result)?"yes":"no";
    printf("TEST5: %d <= %d? %s\n", x, y, res);
    
    
    printf("\n\n*FLOATING-POINT OPERATIONS \"float_i2f()\": \n");
    
    int IEEEfloatRep = 12;
    printf("int %d has single-point representation: %x\n", IEEEfloatRep, float_i2f(IEEEfloatRep));

    return 0;
    
}


/* TEST RESULTS
 
 
* Bit Manipulations function "logicalShift":
24 >> 4 = 1
128 >> 4 = 8
256 >> 4 = 16


* Bit Manipulation function "bitCount":
TEST 1: There are 2 1s in 33.
TEST 2: There are 1 1s in 128.
TEST 3: There are 4 1s in 15.
TEST 3: There are 29 1s in -50.


* Two's Complement function "isPositive":
sizeof(int) 4 bytes.
Is 128 positive? result is = 1
Is -4000 positive? result is = 0


* Two's Complement function "isLessOrEqual":
TEST1: 10 <= 1? no
TEST2: -1 <= -10? no
TEST3: 10 <= 10? yes
TEST4: 5 <= 51? yes
TEST5: -5 <= -1? yes


* FLOATING-POINT OPERATIONS "float_i2f()":
There are 4 bits!

int 12 has single-point representation: 41400000

 
 */






