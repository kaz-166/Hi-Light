#ifndef CRC_H
#define CRC_H

/* CRC名の型定義 */
typedef enum {
    CRC_1,
    CRC_4_ITU,
    CRC_5_ITU,
    CRC_7
} CRC_NAME;

extern char calcCRCValue(CRC_NAME crc_name, int value, int* crc_value);

#endif