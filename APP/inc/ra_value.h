#ifndef __RA_VALUE_H__
#define __RA_VALUE_H__

#include "main.h"

#ifdef __cplusplus
extern "C"{
#endif

#pragma pack(push,1)

typedef struct
{
    uint16_t soc_ocv_table[103];
    uint16_t res_c1t1[103];
    uint16_t res_c1t2[103];
    uint16_t res_c1t3[103];
    uint16_t res_c2t1[103];
    uint16_t res_c2t2[103];
    uint16_t res_c2t3[103];
    uint16_t res_c3t1[103];
    uint16_t res_c3t2[103];
    uint16_t res_c3t3[103];
    uint16_t soc_ocv_new_table[103];
}RA_VALUE;


#define SOC_OCV_TBL    ra_value.soc_ocv_table
#define SOC_OCV_103_TBL  ra_value.soc_ocv_new_table
#define Res_C1T1      ra_value.res_c1t1
#define Res_C1T2      ra_value.res_c1t2
#define Res_C1T3      ra_value.res_c1t3
#define Res_C2T1      ra_value.res_c2t1
#define Res_C2T2      ra_value.res_c2t2
#define Res_C2T3      ra_value.res_c2t3
#define Res_C3T1      ra_value.res_c3t1
#define Res_C3T2      ra_value.res_c3t2
#define Res_C3T3      ra_value.res_c3t3

extern const volatile RA_VALUE ra_value;


#pragma pack(pop)


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __RA_VALUE_H__