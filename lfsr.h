#ifndef LFSR_H
#define LFSR_H

/* LFSR構造体 */
typedef struct{
    const unsigned char dimension; // 生成多項式の次元数
    unsigned long value;           // LSRFの初期値
} lfsr_st;

extern char updateLFSR(lfsr_st *lfsr_obj);
extern void unitTestLFSR(void);

#endif