/***************************************************
 * [モジュール名] lfsr
 * [概要] 線形帰還シフトレジスタのソフトウェア上での実装を提供する
 *
 ***************************************************/
#include "lfsr.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define MAX_DIMENTION 10    // LFSR生成多項式の最大次元数
#define INVERSE(n) (n == 0) ? 1 : 0

static char createLFSRPolynomial(unsigned char dim, unsigned char* poly);

/***************************************************
 * [関数名] updateLFSR(lfsr_st lfsr_obj)
 * [概要]   LFSR値の更新を行う関数
 * [引数]   obj: LFSR構造体
 * [返戻値] 0: 処理成功
 *         -1: 次元数が不正
 *         -2: 構造体のアドレスが不正
 ***************************************************/
char updateLFSR(lfsr_st *lfsr_obj){
    unsigned char intarnal_val = 0;
    unsigned char LFSRpolynomial[MAX_DIMENTION] = {0};

    /* 生成多項式の取得 */
    if(createLFSRPolynomial(lfsr_obj->dimension, LFSRpolynomial) != 0) return -1;

    for(int i = 0; i < lfsr_obj->dimension; i++){
        if(LFSRpolynomial[i] == 1){
            // [Check!] ビットシフトしたときに0でパディングされることを前提としている実装である。
            // 　　　　　パディングに関してはコンパイラ依存だったような気もするので要確認
            // 排他的論理和の計算
            intarnal_val = util_xor(intarnal_val, (lfsr_obj->value & (1 << i)) >> i);
        }
    }
    /* シフト動作 */
    lfsr_obj->value = (lfsr_obj->value >> 1) | (intarnal_val << (lfsr_obj->dimension - 1));
    return 0;
}

/***************************************************
 * [関数名] createLFSRPolynomial(unsigned char dim, unsigned char* poly)
 * [概要]   生成多項式の係数を返す関数
 *          第二引数のpolyで係数の値を格納する配列を返します。
 * [引数]   dim ：多項式の次元数(0～MAX_DIMENSION)
 *          poly：配列
 * [返戻値] 0: 処理成功
 *         -1: 次元数が不正
 *         -2: 配列のアドレスが不正
 ***************************************************/
static char createLFSRPolynomial(unsigned char dim, unsigned char* poly){
    /* エラー処理：指定された生成多項式の次元数が最大次元数を超過していた場合はエラーを返す */
    if((dim > MAX_DIMENTION) || (dim < 4)) return -1;
    /* エラー処理：配列のポインタがNULLの場合はエラーを返す */
    if(poly == 0) return -2;

    memset(poly, 0, sizeof(poly));
    switch(dim){
        case 4: // x^4 + x^3 + 1
            poly[dim-4] = 1;
            poly[dim-3] = 1;
            break;
        case 5: // x^5 + x^3 + 1
            poly[dim-5] = 1;
            poly[dim-3] = 1;
            break;
        case 6: // x^6 + x^5 + 1
            poly[dim-6] = 1;
            poly[dim-5] = 1;
            break;
        case 7: // x^7 + x^6 + 1
            poly[dim-7] = 1;
            poly[dim-6] = 1;
            break;
        case 8: // x^8 + x^6 + x^5 + x^4 + 1
            poly[dim-8] = 1;
            poly[dim-6] = 1;
            poly[dim-5] = 1;
            poly[dim-4] = 1;
            break;
        case 9: // x^9 + x^5 + 1
            poly[dim-9] = 1;
            poly[dim-5] = 1;
            break;
        case 10: // x^10 + x^7 + 1
            poly[dim-10] = 1;
            poly[dim-7] = 1;
            break;
    }

    return 0;
}


/******************* テストコード *******************/
void unitTestLFSR(void){
    for(int n = 4; n < MAX_DIMENTION; n++){
        lfsr_st testObj = {n, 1};
        int init_value = 1;

        /* テスト1 生成ビット列が前回の値と異なることを確認する */
        for(int i = 0; i < (int)pow(2.0, (double)testObj.dimension) - 1; i++){
            int before_value = testObj.value;
            updateLFSR(&testObj);
            if(testObj.value == before_value){
                printf("Test1(dim=%d) [生成ビット列が前回の値と異なることを確認する] was failed.\n", n);
                break;
            }
        }

        /* テスト2 生成ビット列が2^n-1周期を持っていることを確認する */
        testObj.value = init_value; //前回のテストと独立させるため値を初期化
        for(int i = 0; i < (int)pow(2.0, (double)testObj.dimension) - 1; i++){
            updateLFSR(&testObj);
        }
        if(testObj.value != init_value) printf("Test2(dim=%d) [生成ビット列が2^n-1周期を持っていることを確認する] was failed.\n", n);
        }

    /* テスト3 最大次元数を超えた値が指定されたときエラーを出力することを確認する */    
    lfsr_st testObj = {MAX_DIMENTION+1, 1};
    if(updateLFSR(&testObj) == 0) printf("Test3 [最大次元数を超えた値が指定されたときエラーを出力することを確認する] was failed.\n");
}