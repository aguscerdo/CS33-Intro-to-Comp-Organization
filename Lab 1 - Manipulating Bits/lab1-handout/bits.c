/* 
 *  * CS:APP Data Lab 
 *   * 
 *    * Agustin Marinovic Sfeir - 004636016
 *     * 
 *      * bits.c - Source file with your solutions to the Lab.
 *       *          This is the file you will hand in to your instructor.
 *        *
 *         * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 *          * compiler. You can still use printf for debugging without including
 *           * <stdio.h>, although you might get a compiler warning. In general,
 *            * it's not good practice to ignore compiler warnings, but in this
 *             * case it's OK.  
 *              */

#if 0
/*
 *  * Instructions to Students:
 *   *
 *    * STEP 1: Read the following instructions carefully.
 *     */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
 *    * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
 *       */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
 *    * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 *       */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 *  * STEP 2: Modify the following functions according the coding rules.
 *   * 
 *    *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *     *   1. Use the dlc compiler to check that your solutions conform
 *      *      to the coding rules.
 *       *   2. Use the BDD checker to formally verify that your solutions produce 
 *        *      the correct answers.
 *         */


#endif
/*
 *  * isTmin - returns 1 if x is the minimum, two's complement number,
 *   *     and 0 otherwise 
 *    *   Legal ops: ! ~ & ^ | +
 *     *   Max ops: 10
 *      *   Rating: 1
 *       */
int isTmin(int x) {
/* The min 2s number is 10…001. Its complement is 011…111. By adding 2 to the complement,
 *  * 100…00001 is obtained again. Both are compared for equality.
 *   */
int alpha;
int delta;
alpha = (~x+1);
delta = ~(x ^ ~alpha);

  return !(delta) & !(!x);
}
/* 
 *  * bitXor - x^y using only ~ and & 
 *   *   Example: bitXor(4, 5) = 1
 *    *   Legal ops: ~ &
 *     *   Max ops: 14
 *      *   Rating: 1
 *       */
int bitXor(int x, int y) {
/* The XOR is defined as (x | y) & (~x | ~y)
 *  * By applying DeMorgans, it is obtained: ~(~x & ~y) & ~(x & y)
 *   */
int alpha;
int beta;
int omicorn;
alpha = ~(x & y);
beta = ~(~x & ~y);
omicorn = alpha & beta;



  return omicorn;

}
/* 
 *  * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *    *   Legal ops: ! ~ & ^ | + << >>
 *     *   Max ops: 12
 *      *   Rating: 2
 *       */
int allOddBits(int x) {
/* The int 0xAA 8 least significant bits are 10101010, which has all odd bits up. 
 *  * the variable a, which is 0xAA is & with the variable x. If x doesn’t have an odd bit
 *   * up, a will therefore have a 0 where it shouldnt. Then x is shifted four times to the
 *    * right to get the next 8 significant bits. This is done 3 more times. Finally, 
 *     * the equality between a and 0xAA is found as done in lab 0.
 *      */

int aa;

aa = (0xAA << 24) + (0xAA << 16) + (0xAA << 8) + 0xAA;

return ! ((x&aa)^aa);

}
/* 
 *  * sign - return 1 if positive, 0 if zero, and -1 if negative
 *   *  Examples: sign(130) = 1
 *    *            sign(-23) = -1
 *     *  Legal ops: ! ~ & ^ | + << >>
 *      *  Max ops: 10
 *       *  Rating: 2
 *        */
int sign(int x) {

/* First, to check sign, we shift x 31 times, the result is all 1s if negative or all 0s if positive
 *  * Then, to check if 0 or not, we ! twice. If 0 the result is 0, if non-zero the result is 1
 *   * Finally | sign and null, if negative, the result is all 1s, which is -1. If the result is 0,
 *    * sign is all 0s and null is all 0s. If positive, sign is all 0s and null is 1.
 *     */

int negative;
int null;

negative = x >> 31;
null = !(!x);


    return negative | null;
}
/* 
 *  * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *    *   Legal ops: ! ~ & ^ | + << >>
 *     *   Max ops: 12
 *      *   Rating: 2
 *       */
int allEvenBits(int x) {

/* The int 0x55 8 least significant bits are 01010101, which has all even bits up. 
 *  * the variable a, which is 0x55 is & with the variable x. If x doesn’t have an even bit
 *   * up, a will therefore have a 0 where it shouldnt. Then x is shifted four times to the
 *    * right to get the next 8 significant bits. This is done 3 more times. Finally, 
 *     * the equality between a and 0x55 is found as done in lab 0.
 *      */

int five;
five = (0x55 << 24) + (0x55 << 16) + (0x55 << 8) + 0x55;



return !((x&five)^five);

}
/* 
 *  * getByte - Extract byte n from word x
 *   *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *    *   Examples: getByte(0x12345678,1) = 0x56
 *     *   Legal ops: ! ~ & ^ | + << >>
 *      *   Max ops: 6
 *       *   Rating: 2
 *        */
int getByte(int x, int n) {

/* To isolate the required byte, x is shifted to the right 4n times. This gets rid of lower bits
 *  * and gets the byte in the least significant byte location.
 *   * Then the resulting x is & with 0xFF which gets rid of the more significant bits.
 *    */ 

int omicorn = 0xFF;

x = x >> (n << 3);
omicorn = omicorn & x;

  return omicorn;
}
/* 
 *  * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *    *   Legal ops: ! ~ & ^ | + << >>
 *     *   Max ops: 6
 *      *   Rating: 3
 *       */
int isNonNegative(int x) {

/* x is shifted 31 times. Because of arithmetic shifts, if x is negative, after the shift the result will be all 1s.
 *  * If non-negative, the result will be all 0s. The result is ! to obtain a binary result.
 *   */

x = x >> 31;
x = ~x;

  return !( !(x));

}
/* 
 *  * rotateRight - Rotate x to the right by n
 *   *   Can assume that 0 <= n <= 31
 *    *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *     *   Legal ops: ~ & ^ | + << >> !
 *      *   Max ops: 25
 *       *   Rating: 3 
 *        */
int rotateRight(int x, int n) {

int alpha;
int beta;
int gamma;
int delta;
int chi;

chi = (~n+1);

beta = x >> n;

alpha = x << (31 + chi);

gamma = 1 << (31 + chi);
gamma = ~(~gamma + 1);

beta = gamma & beta;

delta = beta + alpha;

  return delta;
}
/*
 *  * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *    *   Note that no negative number is a power of 2.
 *     *   Legal ops: ! ~ & ^ | + << >>
 *      *   Max ops: 20
 *       *   Rating: 4
 *        */
int isPower2(int x) {

/* Start by checking if the number is 0. If it is, then 0 and its 2s complement should be equal.
 *  * If they are, null becomes 0. If not, it is some other non-zero number.
 *   * Then check for sign. By shifting 31 times, if positive, the result is 0, if not it is all 1s. 
 *    * By ~ this, if the number is positive, sign is all 1s, if negative sign will be 0.
 *     * For it to be a power of 2, only 1 bit can be up. The 2s complement of that number will have 1s from
 *      * the bit location to the left, and 0 to the right. Therefore, doing & with the original number and the 2s
 *       * complement returns the original number if it is a power of 2. So we check equality between these 2.
 *        * Power is all 1s if x is a power of 2, or all 0s if its not. Finalize by & null, sign and power and doing ! twice.
 *         */

int sign;
int null;
int power;
int result;

null = !!x;

sign = x >> 31;
sign = (!sign);
power =! (x ^ (x & (~x + 1)));


result = sign & null & power;

  return !(!(result));
}
/* 
 *  * sm2tc - Convert from sign-magnitude to two's complement
 *   *   where the MSB is the sign bit
 *    *   Example: sm2tc(0x80000005) = -5.
 *     *   Legal ops: ! ~ & ^ | + << >>
 *      *   Max ops: 15
 *       *   Rating: 4
 *        */
int sm2tc(int x) {

/* To get the sign, we shift x 31 times, all 1s if negative or all 0s if nonnegative
 *  * Then to get the magnitude we make the MSB 0. This is done via complementing 2^31 and then ~.
 *   * The result, magHelp, is 011…1111. Then the 2s complement is found, which returns the negative of the magnitude.
 *    * To return, if positive, return the magnitude. If negative return the 2s complement.
 *     */

int sign;
int magnitude;
int complement;
int magHelp;

magHelp = ~(~(1 << 31)+1);

magnitude = x & magHelp;

complement = ~magnitude + 1;

sign = x >> 31;

  return (~sign & magnitude) | (sign & complement);

}
/* howManyBits - return the minimum number of bits required to represent x in
 *  *             two's complement
 *   *  Examples: howManyBits(12) = 5
 *    *            howManyBits(298) = 10
 *     *            howManyBits(-5) = 4
 *      *            howManyBits(0)  = 1
 *       *            howManyBits(-1) = 1
 *        *            howManyBits(0x80000000) = 32
 *         *  Legal ops: ! ~ & ^ | + << >>
 *          *  Max ops: 90
 *           *  Rating: 4
 *            */

int howManyBits(int x) {


  return (!(~x) | !x) & 1 ;
}

