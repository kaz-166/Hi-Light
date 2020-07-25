#include "util.h"
#include <stdio.h>
 // [Caution] 三項演算子はAND演算等より優先順位が低いため
 //           括弧で括り優先させること
#define INVERSE(n) ((n == 0) ? 1 : 0)

/***************************************************
 * [関数名] util_xor(unsigned char x1, unsigned char x2)
 * [概要]   排他的論理和の計算を行う関数
 ***************************************************/
unsigned char util_xor(unsigned char x1, unsigned char x2){
    return x1 & INVERSE(x2) | INVERSE(x1) & x2;
}