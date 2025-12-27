/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
//1
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  int pre_resultado = ~x & ~y; //Uso x negado e y negado, y hago un and entre los dos
  int resultado = ~pre_resultado; // Al resultado del and, lo niego
  return resultado; //Estas operaciones terminan siendo lo mismo que hacer un or a x e y
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) { 
  int mask1 = (0xFF << 8) | 0xFF;//Máscara para cuando trabajo con 16 bits
  int mask2 = 0xFF;//Con 8
  int mask3 = 0xF;//Con 4
  int mask4 = 0x3;//Con 2
  int mask5 = 0x1;//Con 1
  int separacion_16bits = x ^ (x >> 16);//Hago un xor con la primera mitad de x y la segunda
  /*Me quedo sólo con los primero 16 bits de la comparación, que son los que tienen el resultado del Xor de la primera y 
  segunda parte*/
  int primer_resultado = separacion_16bits & mask1;
  //Hago lo mismo que en la línea 163 pero ahora divido a primer_resultado
  int separacion_8bits = primer_resultado ^ (primer_resultado >> 8);
  int segundo_resultado = separacion_8bits & mask2;//Me quedo sólo con los bits que me interesan gracias a la máscara
  
  /*Luego sigue ocurriendo lo mismo, osea voy haciendo un Xor de una mitad de los resultados y la otra hasta que me quede 
  sólo 1 bit. Esto lo logro quedándome sólo con el resultado del Xor gracias a una máscara que terminará devolviendo sólo 
  los bits que me interesan y a los demás los pondrá en 0*/
  int separacion_4bits = segundo_resultado ^ (segundo_resultado >> 4);
  int tercer_resultado = separacion_4bits & mask3;
  int separacion_2bits = tercer_resultado ^ (tercer_resultado >> 2);
  int cuarto_resultado = separacion_2bits & mask4;
  int separacion_1bit = cuarto_resultado ^ (cuarto_resultado >> 1);
  int resultado_final = separacion_1bit & mask5;//El resultado final será la Xor del bit0 y el bit1 del cuarto resultado
  return resultado_final;
}
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  int not_x = ~x;
  int not_y = ~y;
  int result = (not_x & not_y);
  return result;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    /**
     * La compuerta XOR se escribe como (a + b) . (~a + ~b).
     * Como no podemos usar + y por leyes de Morgan, la compuerta OR
     * se escribe como ~(~a . ~b) y (~a + ~b) por Morgan se escribe
     * como ~(a . b).
     */
    int a = ~(x & y);
    int b = ~((~x) & (~y));
    int result = a & b;
    return result;
}
//2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  int byte3 = 0x55; //Declaro una constante que va a ser mi máscara y a la vez mi byte número 3
  int byte2 = (byte3 << 8) | byte3; //Usando shifteos a izquierda, muevo el byte3 1 byte, para así tener ya los bytes 3 y 2
  int byte1 = (byte2 << 8) | byte3;//Sucede lo mismo que antes pero ahora tendré los bytes 1, 2 y 3
  /*En este último paso, haciendo lo mismo que antes ya tendré los 32 bits que necesito para ya poder retornar el resultado 
  final*/
  int byte0 = (byte1 << 8) | byte3;
  return byte0;
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  int pre_mask = (0xAA << 8) | 0xAA; //Declaro una premáscara que será igual a 0xAAAA
  
  /*Shifteando la premáscara 16 veces a la izquierda y agregándola al final me queda la máscara que quiero. La cual es 
  0xAAAAAAAA*/
  int mask = (pre_mask << 16) | pre_mask;
  /*Utilizo un and entre x y la máscara para que todos los bits impares queden igual, y los pares se me seteen a 0 para que 
  no se tengan en cuenta, ya que no me interesan*/
  int bits_impares = x & mask;
  /*Niego dos veces a bits_impares debido a que si no tenía 1 en los bits impares, bits_impares = 0->!!bits_impares = 0, 
  y entonces devuelvo 0. Donde realmente me servirá la doble negación es cuando me quede algún bit impar en 1 y ahí niego 
  una vez para que me de 0, osea paso de n-bits a 1 sólo bit, y luego vuelvo a negar para devolver 1*/
  int resultado = !!bits_impares;
  return resultado;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    int mascara = 0xFF; // 0x000000FF
    /**
     * Un byte son 8 bits, por eso al numero lo multiplico
     * por 8, para desplazar en bytes y no bits.
     * Al aplicar la mascara conservo los bits requeridos,
     * ya que anteriormente los desplace a la primera posicion.
     */
    int byte_n = (x >> (n << 3)) & mascara;
    int byte_m = (x >> (m << 3)) & mascara;

    /**
     * Desplazo 0xFF a la posicion del byte n y al negarlo
     * deja todos los bits en 1 menos los de dicha posicion.
     * Lo mismo para el byte m.
     */
    int limpiar_byte_n = ~(mascara << (n << 3));
    int limpiar_byte_m = ~(mascara << (m << 3));
    
    /**
     * Desplazo el byte n a la posicion m y viceversa.
     */
    int insertar_byte_n = byte_n << (m << 3);
    int insertar_byte_m = byte_m << (n << 3);

    /**
     * Aplico a x la mascara para limpiar que unicamente tiene
     * en 0 las posiciones de los bytes. Luego aplico la mascara
     * con los bytes en las posiciones rotadas.
     */
    x &= (limpiar_byte_n & limpiar_byte_m);
    x |= (insertar_byte_n | insertar_byte_m);
    return x;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    /**
     * Desplazar a la derecha en numeros signed inserta el
     * msb bit copiado, por lo que si el bit de signo es 1,
     * quedaria una mascara con todo 1's. En numeros unsigned
     * inserta 0.
     */
    int result;
    int comparison;
    int shift = 33 + ~n;
    /**
     * Quiero lograr desplazar 32 - n bits para conseguir el numero
     * representado con nbits, ~n = -n -1 entonces 33 + (-n -1) resultaría
     * en 32 - n.
     */

    int n_bits = x << shift; // conservo los n bits
    n_bits = n_bits >> shift; // los devuelvo a su posicion original
    /**
     * Si al mover los bits de izquierda a derecha sigue manteniendose el
     * mismo numero, al compararlos con el original, la diferencia debería ser
     * 0, ya que XOR actua como detector de desigualdad
     */
    comparison = x ^ n_bits;
    /**
     * Como comparison devuelve 0 si son iguales, la función requiere lo
     * contrario y por esto mismo se niega
     */
    result = !comparison;

    return result;
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  // Creo el resultado con los bits en posicion 1,3,5,7 en 1
  int result = 0xaa;

  // Desplazo 8 bits a la izquierda y le vuelvo a agregar los bits en 1 en posiciones 1,3,5,7
  result = (result << 8) | 0xaa;

  // Ahora result tiene bits 1 en las posiciones 15,13,11,9,7,5,3,1
  // Vuelvo a desplazar otros 8 bits a la derecha y a poner en 1 las posiciones impares
  result = (result << 8) | 0xaa;

  //Repito el proceso para los ultimos 8 bits
  result = (result << 8) | 0xaa;

  return result;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
    // Declaro una variable que vale 0 cuando x es cero y 1 cuando es distinto de 0
    int es_cero = !!x;

    // Cuando el numero es negativo vale -1, cuando es positivo vale 0 y cuando es cero vale 0 
    int msb_x = (x >> 31);

    return (msb_x | es_cero);
}
//3
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int mask = 0x1;//Declaro una máscara que será usada para sólo quedarme con el último bit
  int bms_x = (x >> 31) & mask;//Agarro el bit más significativo de x usando la máscara
  int bms_y = (y >> 31) & mask;//Agarro el bms de y de la misma forma
  
  /*Los comparo con Xor ya que si no son iguales, el resultado será 1 porque no puede haber overflow si sumo cosas con 
  distinto signo, en el caso que sean iguales, no puedo decir nada*/
  int comparacion_x_y = bms_x ^ bms_y; 
  int suma = x + y;//Sumo x e y
  int bms_suma = (suma >> 31) & mask;//Agarro el bms de la suma

  /*Comparo con Xor el bms de la suma y el de x o y(ya que si estoy en este paso es porque los bms de x e y son iguales). 
  Si los bits son iguales(no hay overflow), uso "!" para negar el resultado debido a que cuando comparo cosas iguales con 
  Xor, el resultado es 0. En el caso de que los bits sean distintos la Xor dará 1, por lo tanto niego el resultado ya que en 
  ese caso habrá overflow*/
  int comparacion_res = !(bms_x ^ bms_suma);
  /*Hago un or entre las dos comparaciones porque si alguna de las dos da 1 es porque no hay overflow, y pongo la de x e y 
  primero ya que puedo devolver 1 si sus bms son distintos sin la necesidad de fijarme lo que pasa con la suma*/
  int resultado = comparacion_x_y | comparacion_res;
  return resultado;
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  // Declaro las variables arriba para poder compilar con grade
  int todo_1_desde_lowbit = ~0; // Todos los bits en 1
  int todo_1_hasta_highbit = 1;
  int bitMask = 0; 

  // Verifico el caso en el que lowbit > highbit
  int condicion = highbit + (~lowbit + 1);    // condicion deberia ser un numero positivo. Si lowbit > highbit es negativo (Devuelvo 0)
  condicion = condicion >> 31;           // Propago el msb para que me quede una mascara de todos 0 o todos 1. Cuando lowbit > highbit son todos 1

  // Desplazo una posicion mas alla que el indice highbit. Lo hago en dos operaciones por caso borde highbit = 31.
  // Haciendo dos shift, me aseguro de no desplazar 32 bits
  todo_1_hasta_highbit = todo_1_hasta_highbit << (highbit);
  todo_1_hasta_highbit = todo_1_hasta_highbit << 1; 
  todo_1_hasta_highbit = todo_1_hasta_highbit + (~1 + 1); // Le resto 1 para que todos los bits hasta la posicion highbit queden en 1

  // Creo otra mascara que tenga todos los bits en 1 desde la posicion highbit.
  todo_1_desde_lowbit = (todo_1_desde_lowbit << lowbit);  // Desplazo para que antes de lowbit queden los bits en 0

  bitMask = todo_1_hasta_highbit & todo_1_desde_lowbit;   // El resultado la interseccion entre estas dos mascaras

  return bitMask & ~condicion;  // Niego condicion, ahora tiene todos ceros si lowbit > highbit
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    /**
     * El operador ternario es basicamente un if, si se cumple la
     * condicion debe devolver Y y si no se cumple devuelve Z.
     * El 1 es el elemento neutro en la multiplicacion, por lo que si 
     * la condicion es true devuelvo Y * 1 y Z * 0, al hacer un OR queda
     * Y | 0 = Y y viceversa.
     */
    int x_bool = !!x; // Si x > 1 lo convierte en 1 y si x = 0 lo deja en 0
    /**
     * Si x_bool = 1
     * mascara_bool = 11111111 11111111 11111111 11111110 + 1
     * Si x_bool = 0
     * mascara_bool = 11111111 11111111 11111111 11111111 + 1
     */
    int mascara_bool = ~x_bool + 1; 
    int true = mascara_bool & y;
    int false = ~mascara_bool & z;
    int result = true | false;

    return result;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
/**
 * Si no tuviesemos limite de operaciones, la forma mas
 * sencilla sería desplazando bits a la derecha, haciendo
 * and con una mascara de 0X01 y sumando a la cuenta. Como
 * tenemos un limite,  podemos implementar el algoritmo de
 * Hamming Weight o Population Count
 */
int bitCount(int x) {
    /**
     * Este algoritmo se usa para contar los simbolos distintos de
     * cero del alfabeto usado, en nuestro caso base binaria. Por 
     * ejemplo:
     * String   |   Hamming weight
     * 1110     |   4
     * 1234056  |   6
     * 
     * 0x55 = 0101 0101
     * 0x33 = 0011 0011
     * 0x0F = 0000 1111
     * 0xFF = 1111 1111
     */
    int mascara_1_bit = 0x55 | (0x55 << 8);     // 01010101 01010101
    int mascara_2_bit = 0x33 | (0x33 << 8);     // 00110011 00110011
    int mascara_4_bit = 0x0F | (0x0F << 8);     // 00001111 00001111
    int mascara_8_bit = 0xFF | (0xFF << 16);    // 00000000 11111111 00000000 11111111
    int mascara_16_bit = 0xFF | (0xFF << 8);    // 00000000 00000000 11111111 11111111

    mascara_1_bit |= (mascara_1_bit << 16);     // Las convierto a mascaras de 32 bits
    mascara_2_bit |= (mascara_2_bit << 16);
    mascara_4_bit |= (mascara_4_bit << 16);

    x = (x & mascara_1_bit) + ((x >> 1) & mascara_1_bit);       // Cuenta los 1 en slice de 2 bits
    x = (x & mascara_2_bit) + ((x >> 2) & mascara_2_bit);       // Cuenta los 1 en slice de 4 bits
    x = (x & mascara_4_bit) + ((x >> 4) & mascara_4_bit);       // Cuenta los 1 en slice de 8 bits
    x = (x & mascara_8_bit) + ((x >> 8) & mascara_8_bit);       // Cuenta los 1 en slice de 16 bits
    x = (x & mascara_16_bit) + ((x >> 16) & mascara_16_bit);    // Cuenta los 1 en todo el numero

    return x;
}
/* 
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and & 
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y) {
  // Busco los bits en 1 que se comparten entre x e y
  int match_1 = (x & y);

  // Busco los bits en 0 que se comparten entre x e y
  int match_0 = (~x & ~y);

  // Devuevo el numero representado por todos los bits que coinciden
  return match_1 | match_0;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  // Creo una mascara que tenga 1 en todas las posiciones menos en las de byte n
  int mask = 0xFF;

  // Necesitamos desplazar bytes, no bits. Por lo que hay que multiplicar n*8. Esto se puede con n << 3, para aumentar las potencias de 2 (2³ = 8)
  mask = (mask << (n << 3));

  // Ahora mask tiene todos ceros menos en el byte n, donde tiene todos 1. Lo niego y obtengo la mascara final
  mask = ~mask;

  // Limpio el byte n de x.
  x = x & mask;

  // Desplazo c a la posicion correcta donde tiene que insertarse.
  c = c << (n << 3);

  // Agrego el byte c en x y lo devuelvo
  return x | c;
}
//4
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum negative value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  int max = ~(0x8 << 28); //Declaro el elemento máximo 
  int suma = x + y;//Sumo los elementos
  int bms_x = (x >> 31);//Agarro el bit más significativo de x
  int bms_y = (y >> 31);//Agarro el más significativo de y
  int distinto_signo_x_y = bms_x ^ bms_y;// Se calcula si x e y tienen distinto signo

  /*Si no tienen distinto signo, distinto_signo_x_y vale FFFFFFFF y distinto_signo vale la suma. Se retorna este valor*/
  int distinto_signo = suma & distinto_signo_x_y;
  int bms_suma = suma >> 31;//En el caso de que sean iguales los msb, agarro el bit más significativo de la suma

  /*Si el bit más significativo de la suma es distinto del de x o y, hay overflow, sino, no lo hay*/
  int overflow = bms_x ^ bms_suma;
  /*Si no hay overflow, la función devuelve la suma, ya que se hace un and entre la suma y el overflow negado(FFFFFFFF)
  y el otro and sirve para que en el caso de que los signos no sean iguales, ~distinto_signo_x_y valga 00000000 y no
  se haga el or bit a bit. Por lo tanto se retorna la suma */
  int signos_iguales_sin_overflow = ((~overflow) & suma) & ~distinto_signo_x_y;
  int tipo_overflow = bms_x & bms_y;//Se verifica si el overflow es positivo o negativo
  
  /*Si hay overflow, se hace un Xor entre max y tipo_overflow, que será 00000000 si los bms son 0 o FFFFFFFF si es 1, si es 
  0  max sigue siendo max y si es 1, max pasa a ser min. Los otros ands sirven para que si se cumple alguna de las 
  condiciones anteriores, esta condición no influya en nada*/
  int overflow_positivo_negativo = ((max ^ tipo_overflow) & ~distinto_signo_x_y) & overflow;
  return distinto_signo | signos_iguales_sin_overflow | overflow_positivo_negativo;
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
    // Para multiplicar x2 desplazo un bit a la izquierda
    int multiplicado = x << 1;

    // Si x < 0, cuando la desplace, se desplaza su signo tambien. Sino se desplazan ceros.
    int signo_x = x >> 31;
    // Ocurre lo mismo que lo mencionado anteriormente pero ahora con x *2
    int signo_multiplicado_x = multiplicado >> 31;

    /**
     * Para que haya overflow entre un numero y su multiplicado, los bits mas significantes de
     * ambos deben diferir. Por ejemplo si multiplico 0100 *2 me da 1000 y eso en complemento
     * a dos es un numero negativo cuando en realidad yo multiplique un positivo. En caso
     * contrario cuando multiplico 1000 *2 me da 0000, teniendo distintos MSB.
     * Si hay overflow vale 1, sino vale 0.
     */
    int overflow = signo_x ^ signo_multiplicado_x;

    int tmin = 1 << 31; // Mascara con el valor de devolucion 0x80000000
    int tmax = ~tmin;   // Mascara contraria a tmin para devolver 0x7FFFFFFF

    /**
     * Si hubo overflow hay que devolver tmin o tmax segun el signo de x,
     * si el signo es 0 debe devolver tmax y si es 1 debe devolver tmin. Si 
     * no hubo overflow devuelve el valor multiplicado.
     * Hay que usar una implementacion parecida a la funcion conditional()
     */
    int tmin_or_tmax = (signo_x & tmin) | (~signo_x & tmax);
    int true = overflow & tmin_or_tmax;
    int false = ~overflow & multiplicado;
    int result = true | false;

    return result;
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
  int menos_x = ~x + 1;

  // Si hago un OR entre x y menos_x el msb va a quedar en 1 a menos que x=0.
  int x_or_menos_x = x | menos_x;

  // Hago un shift para propagar el msb en todo el numero. Esta variable va a ser 0 cuando x=0 o va a ser -1 en caso contrario
  int propagado = (x_or_menos_x >> 31);

  // cambio el signo de propagado para que devuelva 0 con x=0 y 1 con x != 0

  return (~propagado + 1);
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  // Declaro una mascara que voy a usar mas adelante. Lo hago ahora por el make grade
  int limpiador = 0;

  // Creo una mascara que tiene todos los 1 hasta la posicion n
  int mask = (1 << n) + (~1 + 1);   // Puedo usar ~0 pero opte por usar ~1+1 para ser mas consistente al invertir numeros

  // Me guardo los bits que se perderian por hacer el shift a la derecha
  int perdidos_por_shift = x & mask;

  int menos_n = ~n + 1;

  // Muevo los bits que se perderian en el shift en las nuevas posiciones de la izquierda.
  perdidos_por_shift = perdidos_por_shift << (32 + menos_n);

  // Shifteo x las n posiciones
  x = x >> n;

  // Necesito limpiar (poner en 0) los bits en los que se arrastro el msb de x.
  // Para limpiar uso una mascara con todos los bits que se agregaron por el shifteo en 0, los demas en 1.
  limpiador = ~(mask << (32 + menos_n));

  // Dejo en 0 todos los bits que se agregaron a la izquierda
  x = x & limpiador;

  // Combino los numeros que estaban a la derecha (ahora a la izquierda) con el x shifteado
  return perdidos_por_shift | x;  
}
//float
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  unsigned exp = uf & (0xFF << 23);// Obtengo el exponente
  unsigned frac = uf & 0x7FFFFF;// Obtengo el frac
  if(exp == (0xFF << 23) && frac != 0)// Caso borde si el argumento es NaN
    return uf;
  /*Se hace una and con la máscara. El primer byte de esta es 0111 y los siguientes todos 1, lo que permitirá que si el bms 
  es 1, cambia a 0 y sino se mantiene en 0. Nótese que sólo se modifica el primer bit*/
  return uf & 0x7FFFFFFF;
}
/* 
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
    // signo 1 bit, exp 8 bits, frac 23 bits

    // Si los numeros son iguales devuelve 1
    int result = uf == ug;

    // Mascara con signo y exp todo en 1
    unsigned mascara_signo_exp = 0xFF << 23;
    // Mascara con frac todo en 1
    unsigned mascara_frac = 0x007FFFFF;
    // Mascara con signo en 1
    unsigned mascara_signo = 0x80000000;

    unsigned s_exp1 = uf & mascara_signo_exp;   // signo y exp de uf
    unsigned frac1 = uf & mascara_frac;         // frac de uf

    unsigned s_exp2 = ug & mascara_signo_exp;   // signo y exp de uf
    unsigned frac2 = ug & mascara_frac;         // frac de uf

    // Caso uf o ug son NaN, signo y exp todo en uno y frac != 0
    if ((s_exp1 == mascara_signo_exp && frac1 != 0) || (s_exp2 == mascara_signo_exp && frac2 != 0))
        return 0;

    // Caso para +0.0 o -0.0 
    if ((uf == 0 || uf == mascara_signo) && (ug == 0 || ug == mascara_signo))
        return 1;

    return result;
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  // Agarro diferentes las partes del float

  // Consigo el valor de exp, el signo y frac quedan en 0
  unsigned exp = uf & (0xFF << 23);

  // Consigno el valor de frac, el resto queda en 0
  unsigned frac  = uf & 0x7FFFFF;

  // Caso NaN, exp es todos 1 y la mantisa no son todos 0
  if (exp == (0xFF << 23) && frac != 0){
    return uf;
  }

  // Inverto el signo del float
  return uf ^ (1 << 31);
}
/* 
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug) {
  unsigned mask_sign = 0x80000000;
  unsigned mask_exp = 0xFF;
  unsigned mask_frac = 0x7FFFFF;
  unsigned sign_uf = uf & mask_sign;//Obtengo el bit de signo de uf
  unsigned sign_ug = ug & mask_sign;//Obtengo el bit de signo de ug
  unsigned exp_uf = (uf >> 23) & mask_exp;//Obtengo el exponente de uf
  unsigned exp_ug = (ug >> 23) & mask_exp;//Obtengo el exponente de ug
  unsigned uf_frac = uf & mask_frac;// Obtengo el frac de uf
  unsigned ug_frac = ug & mask_frac;//Obtengo el frac de ug
  // Caso borde para cuando uf o ug son Nan 
  if ((exp_uf == 0xFF && uf_frac != 0) || (exp_ug == 0xFF && ug_frac != 0))
    return 0;
  // Caso para cuando uf = 0 o -0 y ug = 0 o -0
  if ((uf == 0 || uf == mask_sign) && (ug == 0 || ug == mask_sign))
    return 0;

  // Caso para cuando uf es negativo y ug positivo
  if (sign_uf && !sign_ug) {
    return 1; 
  }
  if (!sign_uf && sign_ug) {
    return 0; // uf es positivo y ug es negativo, se retorna 0
  }
  //Si los dos tienen el mismo signo se los compara directamente
  if (sign_uf == 0) {
    return uf < ug;
  } else {
    return uf > ug;
  }
}



/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  // Consigo los valores de las partes del float
  unsigned signo = uf >> 31;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  unsigned mantisa = frac | (1 << 23);    
  int E = exp - 127;

  // Caso NaN, -inf, inf (exp todos 1) || numero demasiado grande para int (mayor a 2³¹)
  if(exp == (0xFF << 23) || E >= 31){
    return 0x80000000;
  }

  // Si el numero esta entre 0 y 1 redondeo a 0
  if (E < 0){
    return 0;
  }

  // Si el exponente es mayor a 23 (cantidad de bits de frac), quiere decir que hay que el entero que se tiene que representar
  // No entra en 23 bits, por lo que se desplaza la mantisa a la izquierda. Asi, representa un entero mas grande
  if (E > 23){
    mantisa = mantisa << (E-23);
  }
  // Mismo caso pero al reves, el numero es pequeño y hay que representar un entero mas chico, entonces se mueve a la derecha.
  else{
    mantisa = mantisa >> (23-E);
  }

  if(signo == 0){
    return mantisa;
  }
  return -mantisa;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    /**
     * (-1)^S * M * 2^E
     * msb = signo, exp codifica E pero no es E, frac codifica M pero no es M
     * 
     * E = exp - bias       x = E     bias = 127
     * bias = 2^(k-1) - 1, k = n° bits de exp
     * 1 < exp < 254  |  -126 < E < 127 
     * Si E esta entre 
     */
    unsigned infinito_positivo = 0x7F800000;
    int exp = x + 127;

    /**
     * signo = 0 porque 2.0^x siempre es mayor a 0
     * exp = 2 ^ exp para ver si es posible representarlo
     * frac = 0 porque 2.0^x no tiene parte fraccionaria con coma 
     */
    unsigned result = exp << 23;

    // Analizo los casos donde exp se sale de los rangos permitidos
    if (exp >= 255)
        return infinito_positivo;

    if (exp <= 0)
        return 0;

    return result;
}
