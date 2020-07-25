#include "crc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char createCRCPolynomial(CRC_NAME crc_name, unsigned char* poly);

/***************************************************
 * [関数名] calcCRCValue(CRC_NAME crc_name, int value, int* crc_value)
 * [概要]   CRCの計算を行う関数
 * [引数]   crc_name  : CRC多項式名
 *          value     : CRCを計算したいデータの値
 *          crc_value :【出力】CRC値
 * [返戻値] 0: 処理成功
 *         -1: 多項式名が不正
 ***************************************************/
char calcCRCValue(CRC_NAME crc_name, int value, int* crc_value){
    unsigned char poly[10] = {0};
    /* CRC多項式を生成する */
    if (createCRCPolynomial(crc_name, poly) != 0) return -1;
    
    

    return 0;
}

/***************************************************
 * [関数名] createCRCPolynomial(char* crc_name, unsigned char* poly)
 * [概要]   CRC多項式を生成する関数
 * [引数]   crc_name: CRC多項式名
 *          poly    : 【出力】生成された多項式
 * [返戻値] 0: 処理成功
 *         -1: 多項式名が不正
 *         -2: 構造体のアドレスが不正
 ***************************************************/
static char createCRCPolynomial(CRC_NAME crc_name, unsigned char* poly){
    if(poly == 0) return -2;
    /* CRC名に応じて多項式を生成する */
    memset(poly, 0, sizeof(poly));
    switch(crc_name){
        case CRC_1: // x + 1
            poly[0] = 1;
            break;
        case CRC_4_ITU: // x^4 + x + 1
            poly[3] = 1;
            poly[0] = 1;
            break;
        case CRC_5_ITU: // x^5 + x^4 + x^2 + 1
            poly[4] = 1;
            poly[3] = 1;
            poly[1] = 1;
            break;
        case CRC_7: // x^7 + x^3 + 1
            poly[6] = 1;
            poly[2] = 1;
            break;
        default:
            return -1;
            break;
    }

    return 0;
}