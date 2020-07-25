#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "lfsr.h"

int main(int argc, char** argv){
    if(argc == 1){
        /* ユーザ入力の受け付け */
        char input_dim[255];
        printf("Please Input the Dimension of LFSR Polynomial.\n");
        scanf("%255s", input_dim);

        /* LFSRによる数列の生成 */
        lfsr_st lfsr_obj = {(unsigned char)atoi(input_dim), (unsigned long)1};
        printf("Generate Numbers by LFSR.\n");
        for(int i = 0; i < (int)pow(2.0, lfsr_obj.dimension) - 1; i++){
            if(updateLFSR(&lfsr_obj) == 0){
                printf("%d\n", (int)lfsr_obj.value);
            }else{
                printf("Invalid Value.\n");
                break;
            }
        }
    /* -tオプションを付加するとテストモードで起動する */
    }else if(strncmp(argv[1], "-t", 2) == 0){
        printf("LFSR on Test Mode.\n");
        unitTestLFSR();
    }else{
        printf("Invalid Option.\n");
    }
    return 0;
}




