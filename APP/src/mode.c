#include "mode.h"

uint32_t CB_TimeCelldelta = 0; // LifeTimes_CB_Time_Cell_1
uint8_t CB_Delay_cycles;       // CB:Delay cycles
int16_t Max_Qmax_Cell, Min_Qmax_Cell, Qmax_Pack;
uint8_t QIM_Delay_times; // QIM:Delay updates
uint16_t lastQmaxcyclecount, Qmaxcyclecount;
uint8_t CD_Delay_cycles;               // CD:Delay cycles
int32_t IntTemp, MosFetTemp; // Internal Temperature
uint16_t IntTempK;

uint8_t f_rsoc_hold;
// uint16_t k_CEDV  ;


uint8_t old_rsoc;
// Qmax
uint16_t QmaxControl;
uint16_t Cnt_update_soc_CEDV ;

int32_t at_startqmax_cnt; // Start Count
int32_t at_endqmax_cnt;   // End  Count
int32_t QmaxCapcity_Calc; // QMax Capcity

int32_t  QmaxCapcity_Calc_deadband ; 
uint8_t Qamx1InitSOC;
uint8_t Qamx2InitSOC;
uint8_t Qamx3InitSOC;
uint8_t Qamx4InitSOC;
uint8_t PackQamxInitSOC = 0 ;
uint8_t PackQamxEndSOC_leiji_Qcap_soc ;

uint8_t PackQamxEndSOC = 0 ;
uint8_t Qamx1EndSOC;
uint8_t Qamx2EndSOC;
uint8_t Qamx3EndSOC;
uint8_t Qamx4EndSOC;

uint8_t calc_Res_k_EndSOC = 0  ;
uint16_t calc_Res_k_InitSOC_OCV ;

int16_t g_QamxPack;
uint16_t QmaxUpdataCnt;
uint16_t Qmax1UpdataCnt;
uint16_t Qmax2UpdataCnt;
uint16_t Qmax3UpdataCnt;
uint16_t Qmax4UpdataCnt;
uint16_t LastQMaxUpdataCycle;
uint16_t LastQMaxUpdataValue;

 
uint8_t f_chg_dsg_confirmed = 0 ;
// uint8_t f_calc_init_dynamic_res ;
// uint8_t chg_dsg_confirmed_count ;
// uint16_t calc_Res_k_Init_voltage ;
// uint16_t calc_Res_k_Init_voltage1 ;
// uint16_t calc_Res_k_Init_voltage2 ;
// uint16_t calc_Res_k_Init_voltage3 ;
// uint16_t calc_Res_k_Init_voltage4 ;

uint16_t qmax_CEDV_temp;



uint8_t f_CHG_CEDV = 0;
uint8_t f_DSG_CEDV = 0;
uint8_t f_relax_last_CEDV  = 0 ;

uint8_t f_first_prepared ;


volatile uint32_t COFF_delay = 0;
// CB
uint16_t ex_CB1Cnt = 0;
uint16_t ex_CB2Cnt = 0;
uint16_t ex_CB3Cnt = 0;
uint16_t ex_CB4Cnt = 0;
uint16_t acb_w;            // Cell balance select flag

// uint16_t V_min_CEDV_last ;



uint8_t awork1_CEDV, awork2_CEDV, awork3_CEDV, awork4_CEDV;

const uint8_t acond_tbl[4] // Conditioning table
    = {DTDRV_CVBLC_CB_VC1, DTDRV_CVBLC_CB_VC2, DTDRV_CVBLC_CB_VC3, DTDRV_CVBLC_CB_VC4};

uint16_t CBstatus;

        uint16_t twork1_out, twork2_out;
/*      void Calc_FCC_CEDV()     */

uint8_t b_aidx;
uint16_t k_CEDV = 1000 ;
uint16_t k_CEDV1 = 1000 ;
uint16_t k_CEDV2 = 1000 ;
uint16_t k_CEDV3 = 1000 ;
uint16_t k_CEDV4 = 1000 ;


uint16_t calc_Res_k_InitSOC ;
uint16_t calc_static_k_InitRes ;
uint16_t calc_static_k_InitRes1 ;
uint16_t calc_static_k_InitRes2 ;
uint16_t calc_static_k_InitRes3 ;
uint16_t calc_static_k_InitRes4 ;
uint16_t  calc_k_initRES ;
uint16_t calc_Res_k_EndRes;

/*    Calc_k_CEDV     */
uint16_t voltage_last_5_times[4];

uint8_t i_j_CEDV = 0 ; 
uint8_t f_discharge_CEDV_last ;
/*    Calc_k_CEDV     */

uint16_t Res_Temp_CEDV_Inner_temp  ;


uint8_t f_relax_cal_k_CEDV_last ;
uint8_t f_charge_cal_k_last ;



// uint16_t voltage_last_8_times_temp[6]  ;
uint16_t Res_Temp_CEDV_Inner[9] = {0} ;

int32_t Record_lrc_w_CEDV_fcc_show ;
int32_t  Record_lrc_w_CEDV_fcc_show_last ; 
int32_t Record_lrc_w_CEDV ;

uint16_t t_com0f_CEDV_show ;
uint16_t t_com0f_CEDV;
int32_t dsg_CEDV_Record_lrc_w_update_k ;
uint8_t SOC_CEDV ;
// uint8_t f_yanshi_CEDV  ;
// uint8_t yanshi_CEDV_k ;

uint16_t calc_k_res_chabiao;
uint8_t calc_RES_soc_chabiao;

uint16_t calc_k_res_jisuan;
uint8_t calc_RES_soc_jisuan;
uint16_t fcc_use_qmax  ;
// uint32_t qmax_chu_fcc = 10000 ;


/*  full charge  */
uint16_t tfc_cnt_CEDV = 0;
uint32_t rc_integral_CEDV = 0;
 /*  full charge  */

 uint16_t  Res_C1T1[103] = {3943,3943,3943,3943,3943,3943,3943,3943,3943,3943,3943,3943,3943,3943,2964,2703,2506,2333,2208,2079,\
1973,1872,1782,1716,1654,1606,1558,1511,1484,1450,1425,1394,1362,1342,1320,1293,1284,1268,1253,1251,\
1244,1236,1233,1230,1231,1224,1231,1230,1233,1230,1234,1233,1237,1246,1252,1269,1306,1350,1395,1417,\
1421,1429,1433,1429,1427,1421,1414,1412,1406,1395,1387,1386,1384,1381,1379,1370,1367,1368,1363,1361,\
1358,1362,1363,1359,1357,1346,1345,1340,1331,1323,1309,1300,1281,1264,1247,1228,1206,1184,1165,1138,\
1107,1107,1107,}  ;
  uint16_t    Res_C1T2[103] = {1386,1386,1386,827,652,583,553,494,448,424,399,374,359,359,359,354,340,335,339,329,\
329,318,317,319,323,334,339,339,354,359,364,365,364,359,359,344,353,344,339,340,\
329,326,324,319,319,310,314,305,304,299,299,298,298,304,299,314,339,369,394,399,\
391,384,379,374,368,364,354,353,349,340,339,334,334,334,329,327,323,323,318,318,\
318,324,323,324,324,319,324,323,324,329,329,329,329,324,329,326,324,335,334,333,\
318,318,318,}  ;
  uint16_t    Res_C1T3[103] = {474,474,474,391,362,342,331,274,240,233,231,220,214,238,248,237,241,234,243,234,\
233,224,224,229,226,228,222,209,214,208,205,201,189,190,185,177,184,172,167,171,\
170,162,159,156,157,150,153,154,149,148,150,145,150,156,152,163,182,205,222,217,\
211,209,209,202,206,203,200,200,196,192,188,187,192,194,192,188,174,188,186,188,\
185,187,186,190,190,186,188,187,188,190,191,192,187,186,189,188,183,189,192,202,\
209,209,209,}  ;
 uint16_t    Res_C2T1[103] = {1650,1650,1650,1650,1650,1650,1650,1650,1650,1650,1650,1650,1650,1650,1650,1650,1650,1552,1484,1418,\
1367,1318,1276,1244,1216,1190,1163,1140,1121,1101,1084,1064,1044,1031,1014,997,985,971,960,951,\
941,932,925,919,914,908,906,901,900,898,895,894,895,898,900,909,923,943,961,969,\
973,977,982,983,986,987,986,988,988,988,988,988,989,988,990,989,988,989,988,987,\
987,989,987,987,985,982,982,981,980,977,974,970,969,963,960,956,951,948,941,934,\
899,899,899,}  ;
 uint16_t    Res_C2T2[103] = {1386,1386,1386,960,946,741,655,575,515,475,444,413,392,387,390,385,379,376,375,369,\
369,364,361,362,364,368,369,369,376,379,381,381,380,378,378,373,373,368,365,366,\
360,357,356,352,351,345,344,340,337,336,333,331,331,331,330,339,351,368,381,392,\
394,395,398,395,400,397,395,395,394,392,389,387,388,387,386,383,383,383,381,381,\
381,381,381,381,383,384,386,385,385,388,392,394,391,392,391,392,389,390,387,383,\
370,370,370,}  ;
 uint16_t    Res_C2T3[103]= {404,404,404,369,355,369,371,334,297,285,273,260,252,256,266,269,265,263,267,261,\
261,252,250,252,252,257,257,256,261,262,263,262,260,259,257,254,254,249,246,246,\
243,239,237,233,232,227,227,223,221,219,218,217,217,217,218,224,238,254,266,274,\
274,275,275,273,273,271,268,268,266,264,261,253,257,256,255,253,251,250,249,248,\
247,249,246,246,244,243,243,244,243,243,242,244,243,239,241,239,240,241,243,242,\
240,240,240,}  ;
 uint16_t    Res_C3T1[103] = {868,868,868,868,868,868,868,868,868,868,868,868,868,868,868,868,868,868,868,868,\
868,819,799,781,765,754,742,730,722,711,703,693,683,676,667,658,652,643,637,631,\
626,620,614,610,607,603,601,597,596,594,592,591,591,592,592,596,604,615,624,630,\
632,636,639,640,643,645,645,648,650,651,653,655,658,660,662,665,667,670,672,676,\
678,683,686,690,695,698,702,706,712,717,722,729,736,742,751,758,768,777,782,774,\
727,727,727,}  ;
 uint16_t    Res_C3T2[103] = {1386,1386,1386,894,556,457,440,409,382,387,365,345,331,326,326,324,321,321,322,321,\
319,317,315,315,316,316,316,316,317,317,317,317,313,313,312,309,310,307,306,306,\
303,301,300,298,297,296,294,292,291,289,288,287,286,286,286,289,295,304,310,314,\
315,317,319,319,319,319,318,319,318,317,318,318,319,319,319,319,319,320,320,320,\
321,323,323,324,325,326,327,329,330,331,332,334,335,336,337,337,337,337,337,335,\
321,321,321,}  ;
 uint16_t   Res_C3T3[103] = {347,347,347,347,348,355,349,322,296,276,263,249,243,242,245,246,245,246,249,246,\
245,242,240,241,240,242,242,241,243,244,245,245,243,243,242,240,240,238,236,236,\
234,232,230,228,226,225,224,222,220,217,218,216,216,216,215,218,224,233,240,244,\
245,246,248,247,248,248,247,248,247,246,245,245,246,245,245,243,243,242,241,241,\
240,240,240,239,239,238,239,238,238,239,237,237,237,236,235,235,235,234,233,231,\
225,225,225,}  ;

 uint16_t  SOC_OCV_103_TBL[103] = {3100,3200,3392,3497,3568,3621,3655,3666,3671,3674,3676,3677,3680,3687,3695,3702,3708,3714,3722,3727,\
3732,3735,3739,3745,3749,3755,3759,3764,3769,3773,3778,3782,3785,3789,3793,3796,3801,3804,3808,3813,\
3818,3822,3827,3832,3837,3842,3848,3854,3860,3866,3873,3880,3887,3895,3903,3914,3926,3940,3954,3965,\
3975,3986,3996,4006,4016,4027,4037,4048,4058,4069,4080,4091,4103,4114,4126,4138,4149,4162,4173,4186,\
4198,4211,4223,4235,4248,4259,4272,4283,4295,4307,4318,4329,4339,4349,4360,4370,4379,4390,4400,4412,\
4425,4448,4465} ;



// 为什么计算放电开始的内阻没有用到 单位放大缩小 ？ 

/*     void Calc_FCC_CEDV()      */

void AlarmWarning_Check(void)
{
    if (SafetyStatus(OC))
    {
        if (f_charge)
        {
            BatteryStatus(OCA) = ON;
        }
    }
    else
    {
        BatteryStatus(OCA) = OFF;
    }

    if (f_gs_tc)
    {
        // Condition: CLEAR V
        if (D_SOC_Flag_Config_A_TCCLEARV)
        {
            if (V_max <= D_TC_Clear_Voltage_Threshold)
            {
                f_gs_tc = OFF;
            }
        }
        // Condition: CLEAR RSOC
        if (D_SOC_Flag_Config_A_TCCLEARRSOC)
        {
            if (t_com0d <= D_TC_Clear_RSOC_Threshold)
            {
                f_gs_tc = OFF;
            }
        }
    }
    else
    {
        // Condition: SET V
        if (D_SOC_Flag_Config_A_TCSETV)
        {
            if (V_max >= D_TC_Set_Voltage_Threshold) // 
            {
                f_gs_tc = ON;
            }
        }
        // Condition: SET RSOC
        if (D_SOC_Flag_Config_A_TCSETRSOC)
        {
            if (t_com0d >= D_TC_Set_RSOC_Threshold)
            {
                f_gs_tc = ON;
            }
        }
        // Condition: SET VCT
        if (D_SOC_Flag_Config_A_TCSETVCT)
        {
            if (f_VCT)
            {
                f_gs_tc = ON;
            }
        }
    }

    if (f_gs_fc)
    {
        // Condition: CLEAR V
        if (D_SOC_Flag_Config_B_FCCLEARV)
        {
            if (V_max <= D_FC_Clear_Voltage_Threshold)
            {
                f_gs_fc = OFF;
            }
        }
        // Condition: CLEAR RSOC
        if (D_SOC_Flag_Config_B_FCCLEARRSOC)
        {
            if (t_com0d <= D_FC_Clear_RSOC_Threshold)
            {
                f_gs_fc = OFF;
            }
        }
    }
    else
    {
        // Condition: SET V
        if (D_SOC_Flag_Config_B_FCSETV)
        {
            if (V_max >= D_FC_Set_Voltage_Threshold)
            {
                f_gs_fc = ON;
            }
        }
        // Condition: SET RSOC
        if (D_SOC_Flag_Config_B_FCSETRSOC)
        {
            if (t_com0d >= D_FC_Set_RSOC_Threshold)
            {
                f_gs_fc = ON;
            }
        }
        // Condition: SET VCT
        if (D_SOC_Flag_Config_A_FCSETVCT)
        {
            if (f_VCT)
            {
                f_gs_fc = ON;
            }
        }
    }

    if (f_gs_td)
    {
        // Condition: CLEAR V
        if (D_SOC_Flag_Config_A_TDCLEARV)
        {
            if (V_min >= D_TD_Clear_Voltage_Threshold)
            {
                f_gs_td = OFF;
            }
        }
        // Condition: CLEAR RSOC
        if (D_SOC_Flag_Config_A_TDCLEARRSOC)
        {
            if (t_com0d >= D_TD_Clear_RSOC_Threshold)
            {
                f_gs_td = OFF;
            }
        }
    }
    else
    {
        // Condition: SET V
        if (D_SOC_Flag_Config_A_TDSETV)
        {
            if (V_min <= D_TD_Set_Voltage_Threshold)
            {
                f_gs_td = ON;
            }
        }
        // Condition: SET RSOC
        if (D_SOC_Flag_Config_A_TDSETRSOC)
        {
            if (t_com0d <= D_TD_Set_RSOC_Threshold)
            {
                f_gs_td = ON;
            }
        }
    }

    if (f_gs_fd)
    {
        // Condition: CLEAR V
        if (D_SOC_Flag_Config_B_FDCLEARV)
        {
            if (V_min >= D_FD_Clear_Voltage_Threshold)
            {
                f_gs_fd = OFF;
            }
        }
        // Condition: CLEAR RSOC
        if (D_SOC_Flag_Config_B_FDCLEARRSOC)
        {
            if (t_com0d >= D_FD_Clear_RSOC_Threshold)
            {
                f_gs_fd = OFF;
            }
        }
    }
    else
    {
        // Condition: SET V
        if (D_SOC_Flag_Config_B_FDSETV)
        {
            if (V_min <= D_FD_Set_Voltage_Threshold)
            {
                f_gs_fd = ON;
            }
        }
        // Condition: SET RSOC
        if (D_SOC_Flag_Config_B_FDSETRSOC)
        {
            if (t_com0d <= D_FD_Set_RSOC_Threshold)
            {
                f_gs_fd = ON;
            }
        }
    }
    // BatteryStatus
    if ((f_gs_td && f_discharge) || (!D_DA_Configuration_NR && !f_pres) ||  SafetyAlert(CUV) || SafetyAlert(OCD1) || SafetyAlert(OCD2) || SafetyAlert(OTF) || SafetyAlert(OTD) || SafetyStatus(UTD) || SafetyStatus(AOLD) || SafetyStatus(ASCD) || f_pf_suv_a || f_pf_socd_a || f_pf_cb_p || f_fuse_out)
    {
        BatteryStatus(TDA) = ON;
    }
    else
    {
        BatteryStatus(TDA) = OFF;
    }

    if ((f_gs_tc && f_charge) || (!D_DA_Configuration_NR && !f_pres) || SafetyAlert(COV) || SafetyAlert(OCC1) || SafetyAlert(OCC2) || SafetyStatus(ASCC) || SafetyAlert(OTC) || SafetyAlert(UTC)|| SafetyAlert(OC) || SafetyAlert(CHGC) || SafetyAlert(CHGV) || SafetyAlert(OTF) || SafetyAlert(PCHGC) || f_pf_sov_a || f_pf_socc_a || f_pf_cb_p || f_fuse_out)
    {
        BatteryStatus(TCA) = ON;
    }
    else
    {
        BatteryStatus(TCA) = OFF;
    }

    if (SafetyStatus(OTC) || SafetyStatus(OTD) || SafetyStatus(OTF) || f_pf_sot_p || f_pf_sotf_p)
    {
        BatteryStatus(OTA) = ON;
    }
    else
    {
        BatteryStatus(OTA) = OFF;
    }

    if (f_gs_fc)
    {
        BatteryStatus(FC) = ON;
    }
    else
    {
        BatteryStatus(FC) = OFF;
        // f_VCT = OFF; // battery charge termination f_VCT = ON;
        f_fullchg = OFF;
        f_fullchg_CEDV = OFF ;

        // t_com4c_out = f_fullchg;
        //  t_com4d_out = f_fullchg_CEDV ;

    }

    if (f_gs_fd || SafetyStatus(CUV) || f_pf_suv_p || SafetyStatus(CUVC) || f_pf_suv_p)
    {
        BatteryStatus(FD) = ON;
    }
    else
    {
        BatteryStatus(FD) = OFF;
    }

    if (t_com0fCap <= _RemainingCapacityAlarm)
    {
        if (BatteryStatus(DSG))
        {
            BatteryStatus(RCA) = ON;
        }
    }
    else
    {
        BatteryStatus(RCA) = OFF;
    }
    if (_AverageTimeToEmpty < D_Data_Remaining_Time_Alarm)
    {
        BatteryStatus(RTA) = ON;
    }
    else
    {
        BatteryStatus(RTA) = OFF;
    }
}
void QMaxUpdateReset(void)
{
    // f_Qmax_start = OFF;
    // f_Qmax_end = OFF;
    // at_endqmax_cnt = 0;
    // at_startqmax_cnt = 0;
    // QmaxCapcity_Calc = 0;
}

void QMaxUpdateJudge(uint8_t InitSOC, uint8_t EndSOC, int16_t *QamxCell)
{
//    uint8_t dropSoc;
//    if ((InitSOC < D_Qmax_SOC_low_limit || InitSOC > D_Qmax_SOC_high_limit) && (EndSOC < D_Qmax_SOC_low_limit || EndSOC > D_Qmax_SOC_high_limit))
//    {
//        dropSoc = ABS(InitSOC - EndSOC);
//        if (dropSoc > D_Qmax_update_min_delta_SOC)
//        {
//            *QamxCell = (int16_t)(QmaxCapcity_Calc / 144 / dropSoc);
//            f_ltreq = ON;
//            f_QmaxUpFsh = ON;
//             t_com0c = 1 ;
//        }
//        else
//        {
//            QMaxUpdateReset();
//        }
//    }
//    else
//    {
//        QMaxUpdateReset();
//    }
}

void QMax_Calc(void)
{
    // uint8_t aidx = 0;
    // int8_t dropSoc;

    // if (Ts_max >= D_Qmax_Temp_Low_limit && Ts_max <= D_Qmax_Temp_High_limit && _CycleCount > D_Qmax_Cycle_limit)
    // {
    //     if (f_relax)
    //     {
    //         if (!f_Qmax_start)
    //         {
    //             at_startqmax_cnt++;
    //             if (at_startqmax_cnt >= 72000)
    //             {
    //                 for (aidx = 0; (aidx < 19) && (V_min > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 PackQamxInitSOC = (char)aidx * 5 + (short)((short)(V_min - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 for (aidx = 0; (aidx < 19) && (_DAStatus1.CellVoltage1 > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 Qamx1InitSOC = (char)aidx * 5 + (short)((short)(_DAStatus1.CellVoltage1 - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 for (aidx = 0; (aidx < 19) && (_DAStatus1.CellVoltage2 > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 Qamx2InitSOC = (char)aidx * 5 + (short)((short)(_DAStatus1.CellVoltage2 - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 for (aidx = 0; (aidx < 19) && (_DAStatus1.CellVoltage3 > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 Qamx3InitSOC = (char)aidx * 5 + (short)((short)(_DAStatus1.CellVoltage3 - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 for (aidx = 0; (aidx < 19) && (_DAStatus1.CellVoltage4 > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 Qamx4InitSOC = (char)aidx * 5 + (short)((short)(_DAStatus1.CellVoltage4 - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 f_Qmax_start = ON;
    //                 f_Qmax_end = OFF;
    //                 at_endqmax_cnt = 0;
    //                 at_startqmax_cnt = 0;
    //             }
    //         }
    //         else
    //         {
    //             at_endqmax_cnt++;
    //             if (at_endqmax_cnt >= 72000)
    //             {
    //                 for (aidx = 0; (aidx < 19) && (V_min > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 PackQamxEndSOC = (char)aidx * 5 + (short)((short)(V_min - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 for (aidx = 0; (aidx < 19) && (_DAStatus1.CellVoltage1 > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 Qamx1EndSOC = (char)aidx * 5 + (short)((short)(_DAStatus1.CellVoltage1 - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 for (aidx = 0; (aidx < 19) && (_DAStatus1.CellVoltage2 > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 Qamx2EndSOC = (char)aidx * 5 + (short)((short)(_DAStatus1.CellVoltage2 - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 for (aidx = 0; (aidx < 19) && (_DAStatus1.CellVoltage3 > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 Qamx3EndSOC = (char)aidx * 5 + (short)((short)(_DAStatus1.CellVoltage3 - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
    //                 for (aidx = 0; (aidx < 19) && (_DAStatus1.CellVoltage4 > OCV_SOC[aidx + 1]); aidx++)
    //                     ;
    //                 Qamx4EndSOC = (char)aidx * 5 + (short)((short)(_DAStatus1.CellVoltage4 - OCV_SOC[aidx]) * 5) / (short)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);

    //                 f_Qmax_end = ON;
    //                 f_Qmax_start = OFF;
    //                 at_endqmax_cnt = 0;
    //                 at_startqmax_cnt = 0;
    //                 QmaxCapcity_Calc = 0;
    //             }
    //         }

    //         if (f_Qmax_end)
    //         {
    //             QMaxUpdateJudge(PackQamxInitSOC, PackQamxEndSOC, &g_QamxPack);
    //             QMaxUpdateJudge(Qamx1InitSOC, Qamx1EndSOC, &_GaugeStatus3.QMax0);
    //             QMaxUpdateJudge(Qamx2InitSOC, Qamx2EndSOC, &_GaugeStatus3.QMax1);
    //             QMaxUpdateJudge(Qamx3InitSOC, Qamx3EndSOC, &_GaugeStatus3.QMax2);
    //             QMaxUpdateJudge(Qamx4InitSOC, Qamx4EndSOC, &_GaugeStatus3.QMax3);
    //             if (f_QmaxUpFsh)
    //             {
    //                 f_QmaxUpFsh = OFF;
    //                 QmaxUpdataCnt++;
    //                 LastQMaxUpdataCycle = _CycleCount;
    //                 LastQMaxUpdataValue = g_QamxPack;
    //                 QMaxUpdateReset();
    //             }
    //         }
    //     }
    //     else
    //     {
    //         if (I_abs >= (long)D_Qmax_C_rate_low_limit * D_Design_Capacity_mAh / 10 && I_abs <= (long)D_Qmax_C_rate_high_limit * D_Design_Capacity_mAh / 10 && f_Qmax_start == ON) // 0.1C
    //         {
    //             if (D_Control_flag_1_Qmax_update_DSG)
    //             {
    //                 if (f_charge)
    //                 {
    //                     f_Qmax_start = OFF;
    //                     f_Qmax_end = OFF;
    //                     at_startqmax_cnt = 0;
    //                     QmaxCapcity_Calc = 0;
    //                 }
    //                 else
    //                 {
    //                     QmaxCapcity_Calc += I_abs;
    //                 }
    //             }

    //             if (D_Control_flag_1_Qmax_update_CHG)
    //             {
    //                 if (f_discharge)
    //                 {
    //                     f_Qmax_start = OFF;
    //                     f_Qmax_end = OFF;
    //                     at_startqmax_cnt = 0;
    //                     QmaxCapcity_Calc = 0;
    //                 }
    //                 else
    //                 {
    //                     QmaxCapcity_Calc += I_abs;
    //                 }
    //             }
    //         }
    //         else
    //         {
    //             f_Qmax_end = OFF;
    //             at_startqmax_cnt = 0;
    //         }
    //         at_endqmax_cnt = 0;
    //     }
    // }
    // else
    // {
    //     QMaxUpdateReset();
    // }
}



/* calculate k , only in discharge */

 void Calc_b_aidx(void)
    {
        uint8_t aidx_c;
        uint8_t awork1, awork2, awork3, awork4;
        uint16_t twork1, twork2;
        uint16_t tinreg;
        int32_t ccwork;
        int32_t dcwork;



        // Calc [C]x100 from current   current beilv .
        twork1 = (uint16_t)((long)I_abs * 100 / D_Design_Capacity_mAh);  // 1234 6169 0.2

        // - Make [C]index -
        // linear interporation: y = (y2-y1)*(x-x1)/(x2-x1) + y1
        //						   = y1 - (y1-y2)*(x-x1)/(x2-x1)
        // awork1: x-x1
        // awork2: x2-x1
        if (twork1 <= D_CRATE_TBL[1]) // <= C-rate2 ?
        {
            aidx_c = 0;                     // Table index = 0
            if (twork1 <= D_CRATE_TBL[0]) // <= C-rate1 ?
            {
                awork1 = 0; // SetC-rate1
            }
            else
            { // > C-rate1
                // Calculate value index
                awork1 = (uint8_t)(twork1 - D_CRATE_TBL[0]);  

            }
            // Data area is within C-rate1 to C-rate2
            awork2 = D_CRATE_TBL[1] - D_CRATE_TBL[0];   //50
        }
        else // > C-rate2 ?  di 2 ge C2            D_CRATE_TBL[1]
        {                                 // > C-rate2
            // if (twork1 <= D_CRATE_TBL[2]) // <= C-rate3 ?
            // {
                aidx_c= 3; // Table index = 5
                // Calculate value index
              //  awork1 = (uint8_t)(twork1 - D_CRATE_TBL[1]);
                // Data area is within C-rate2 to C-rate3
                awork2 = D_CRATE_TBL[2] - D_CRATE_TBL[1];
              //  awork1 = awork2;

             
               awork1 = (uint8_t)(twork1 - D_CRATE_TBL[1]);
              //   awork1 = (uint8_t)(twork1 - D_CRATE_TBL[0]);  wrong . 

                if(twork1 >= D_CRATE_TBL[2])
                {
                    awork1 = awork2 ;
                }

            // }
            // else
            // {
            //     aidx = 10; // Table index = 5
            //                // Calculate value index
            //     // awork1 = (uint8_t)(twork1 - D_CRATE_TBL[2]);
            //     // Data area is within C-rate2 to C-rate3
            //     awork2 = D_CRATE_TBL[3] - D_CRATE_TBL[2];
            //     awork1 = awork2;
            // }
        }

        // - Make Temperature index -
        awork3 = Ts_max - D_TRATE_TBL[0]; // Make the value of T-rate1 base
        if (Ts_max >= D_TRATE_TBL[1])     // >= T-rate2 ?
        {
            aidx_c++; // Increment table index
            awork4 = D_TRATE_TBL[2] - D_TRATE_TBL[1];
            if (Ts_max >= D_TRATE_TBL[2]) // >= T-rate3 ?
            {
                awork3 = awork4; // Value index is max value
            }
            else
            {                                     // T-rate2 <= Temp. < T-rate3
                awork3 = Ts_max - D_TRATE_TBL[1]; // Calculate value index
            }
        }
        else
        { // < T-rate2
            // Data area is within T-rate1 to T-rate2
            awork4 = D_TRATE_TBL[1] - D_TRATE_TBL[0];

            if (Ts_max <= D_TRATE_TBL[0]) // <= T-rate1 ?
            {
                awork3 = 0; // Value index = 0
            }
        }
        
        b_aidx = aidx_c;
        awork1_CEDV = awork1 ;
        awork2_CEDV = awork2 ;
        awork3_CEDV = awork3 ;
        awork4_CEDV = awork4 ;




        twork1_out = twork1 ;
        twork2_out = twork2 ; 



    }


void Calc_soc_to_res(uint8_t b_aidx, uint8_t b_soc_to_res_index)
{
    uint8_t awork1, awork2, awork3, awork4;
    uint16_t twork1, twork2;

    

    awork1 = awork1_CEDV;
    awork2 = awork2_CEDV;
    awork3 = awork3_CEDV;
    awork4 = awork4_CEDV;


    Res_Temp_CEDV_Inner[0] = Res_C1T1[b_soc_to_res_index];
    Res_Temp_CEDV_Inner[1] = Res_C1T2[b_soc_to_res_index];
    Res_Temp_CEDV_Inner[2] = Res_C1T3[b_soc_to_res_index];
    Res_Temp_CEDV_Inner[3] = Res_C2T1[b_soc_to_res_index];
    Res_Temp_CEDV_Inner[4] = Res_C2T2[b_soc_to_res_index];
    Res_Temp_CEDV_Inner[5] = Res_C2T3[b_soc_to_res_index];
    Res_Temp_CEDV_Inner[6] = Res_C3T1[b_soc_to_res_index];
    Res_Temp_CEDV_Inner[7] = Res_C3T2[b_soc_to_res_index];
    Res_Temp_CEDV_Inner[8] = Res_C3T3[b_soc_to_res_index];



    //  to do
    // 检测  match Res

    twork1 = Res_Temp_CEDV_Inner[b_aidx] -
             (uint16_t)((((long)Res_Temp_CEDV_Inner[b_aidx] - Res_Temp_CEDV_Inner[b_aidx + 3]) * awork1/awork2));

    twork2 = Res_Temp_CEDV_Inner[b_aidx + 1] -
             (uint16_t)((((long)Res_Temp_CEDV_Inner[b_aidx + 1] - Res_Temp_CEDV_Inner[b_aidx + 4]) * awork1 / awork2));


    // t_com8d_out  = twork1 ;
    // t_com8e_out  = twork2 ;

    // Res_Temp_CEDV_Inner_turn = twork1 + (uint16_t)((((long)twork2 - twork1) * awork3 / awork4)); // discharge Q
    Res_Temp_CEDV_Inner_temp = twork1 + (uint16_t)((((long)twork2 - twork1) * awork3 / awork4)); // discharge Q



    // // To do : 
    // // log k 
    // // log current 

    //  // t_com88_out = b_aidx;
    // // t_com89_out = awork1;
    // // t_com8a_out = awork2;
    // // t_com8b_out = awork3;
    // // t_com8c_out = awork4;

    // // t_com90_out = Res_Temp_CEDV_Inner[0];
    // // t_com91_out = Res_Temp_CEDV_Inner[1];
    // // t_com92_out = Res_Temp_CEDV_Inner[2];
    // // t_com93_out = Res_Temp_CEDV_Inner[3];
    // // t_com94_out = Res_Temp_CEDV_Inner[4];
    // // t_com95_out = Res_Temp_CEDV_Inner[5];
    // // t_com96_out = Res_Temp_CEDV_Inner[6];
    // // t_com97_out = Res_Temp_CEDV_Inner[7];
    // // t_com98_out = Res_Temp_CEDV_Inner[8];

    // t_com8f_out = Res_Temp_CEDV_Inner_temp ;  // log r 
    
}

void Calc_k_CEDV(void) // use leiji style
{


    uint16_t V_OCV;
    uint32_t qmax_CEDV_u32;
    static uint16_t cnt3600_relax; // when realx state , 3600 hours .
    //static uint16_t vol_calc[4];
    //static uint8_t cnt_vol_calc = 0;
    static uint8_t f_start_calc_k = 0;
  //   uint8_t index_SOC_OCV ;

    // if (cnt_vol_calc <= 3)
    // {
    //     vol_calc[cnt_vol_calc] = V_min;
    //     cnt_vol_calc++;
    // }
    // else
    // {
    //     cnt_vol_calc = 0;
    //     vol_calc[0] = V_min;
    // }
    // t_com8e_out = f_relax_cal_k_CEDV_last;
    // SOC_CEDV  ;
    if (f_relax)
    {
        cnt3600_relax++;
        {
            if (cnt3600_relax >= 3600)
            {
                cnt3600_relax = 3600;
                f_start_calc_k = 1;
            }
        }
    }

    if (f_start_calc_k == 0)
    {
        if (SOC_CEDV >= 101)
        {
            f_start_calc_k = 1;
        }
    }

    if ((f_charge) && (SOC_CEDV < 101))
    {
        cnt3600_relax = 0;
        f_start_calc_k = 0;
    }

    //  静置时间够了，   f_start_calc_k =  1 ；切换 ： 或者 soc
    if ((f_discharge == 1) && (f_relax == 0) && ((f_relax_cal_k_CEDV_last == 1) || (f_charge_cal_k_last == 1))) // from not fangdian to fangdian
    {
        if (f_start_calc_k == 0)
        {
            cnt3600_relax = 0; // 静置到放电的时刻 。充电到放电的时候
        }

        if ((cnt3600_relax < 3600) && (SOC_CEDV < 101)) //  kaishi fangdian ,
        {
            cnt3600_relax = 0;
            f_start_calc_k = 0;
        }
    }

    if (f_start_calc_k)
    {
        if ((f_discharge == 1) && (f_relax == 0)) // fangdian
        {
            qmax_CEDV_u32 = qmax_CEDV;
            if (dsg_CEDV_Record_lrc_w_update_k == 0) // calc_k leiji qmax * 0.01
            {
                // t_com90_out = 1;
                if (f_relax_cal_k_CEDV_last)
                {
                    //  t_com90_out = 2;
                    //t_com93_out = 3;
                }
                else
                {
                   //  t_com93_out = 666;
                    calc_RES_soc_chabiao = SOC_CEDV;
                    t_com96_out = calc_RES_soc_chabiao;

                    Calc_b_aidx();
                    Calc_soc_to_res(b_aidx, calc_RES_soc_chabiao); //
                    calc_k_res_chabiao = Res_Temp_CEDV_Inner_temp;
                }
            }

            // t_coma0_out = calc_k_res_chabiao;
            dsg_CEDV_Record_lrc_w_update_k += I_abs;
            if (dsg_CEDV_Record_lrc_w_update_k >= qmax_CEDV_u32 * 144) // if(dsg_CEDV_Record_lrc_w /14400 >= qmax_CEDV/100)
            {
                dsg_CEDV_Record_lrc_w_update_k = 0;
                //  chabiao


                calc_RES_soc_chabiao = SOC_CEDV;

                t_com96_out = calc_RES_soc_chabiao;


                Calc_b_aidx();
                Calc_soc_to_res(b_aidx, calc_RES_soc_chabiao); //



                // Calc_soc_to_res(b_aidx, index_SOC_OCV); //

                // for(index_SOC_OCV = 0 ; index_SOC_OCV <102;index_SOC_OCV++)
                // {

                // }
                
                calc_k_res_chabiao = Res_Temp_CEDV_Inner_temp;

                t_coma0_out = calc_k_res_chabiao;
                // chabiao neizu .

               // t_com98_out = 1;
                // jisuan neizu
                //  calc_k_res() ;
                calc_RES_soc_jisuan = SOC_CEDV;
                t_com97_out = calc_RES_soc_jisuan;

                V_OCV = SOC_OCV_103_TBL[SOC_CEDV];
                t_com8c_out = V_OCV;

                if (I_abs != 0)
                {
                    t_com1d_out = V_OCV;
                    t_com1e_out = V_min;
                    if (V_OCV > V_min)
                    {
                        calc_k_res_jisuan = (uint16_t)((long)(V_OCV - V_min) * 10000 / I_abs);
                    }

                    t_com99_out = calc_k_res_jisuan;
                }

                if (calc_k_res_chabiao != 0)
                {
                    k_CEDV = (uint16_t)((long)calc_k_res_jisuan * 1000 / calc_k_res_chabiao); //   calc_Res_k_EndRes enlarged 1000 times
                }
                else
                {
                    //  t_com8a_out = 1;
                    k_CEDV = 2345;
                }
            }
            else
            {
                // t_com98_out = 0;
            }
        }
        else
        {
            dsg_CEDV_Record_lrc_w_update_k = 0;
        }
    }

    t_com33_out = k_CEDV;
    // k  = jisuan / search table

    f_relax_cal_k_CEDV_last = f_relax;
    f_charge_cal_k_last = f_charge;
}

void QMaxUpdateReset_CEDV(void)
{
    f_Qmax_start = OFF;
    f_Qmax_end = OFF;
    at_endqmax_cnt = 0;
    at_startqmax_cnt = 0;
    QmaxCapcity_Calc = 0;
    QmaxCapcity_Calc_deadband = 0 ;
    f_CHG_CEDV = 0;
    f_DSG_CEDV = 0;
  //  chg_dsg_confirmed_count = 0 ;
  //  chg_dsg_confirmed_count = 0;
    f_chg_dsg_confirmed = 0;
  //  f_calc_init_dynamic_res = 0 ; 
}

uint16_t QMaxUpdateJudge_CEDV(uint8_t InitSOC, uint8_t EndSOC)
{
    uint8_t  dropSoc;

    // 结束静态
    // CEDV_soc_range = QmaxCapcity_Calc*5/72/t_com18 ; // soc differece  / Design capa *1000 
    dropSoc = ABS(InitSOC - EndSOC); 
    t_com90_out =  dropSoc  ;
    //    if (dropSoc > D_Qmax_update_min_delta_SOC)
    //  if (CEDV_soc_range >=350 )
    //    {
    // (QmaxCapcity_Calc/(3600*4)) leiji 
    //  fcc_CEDV_Ture = (QmaxCapcity_Calc/(3600*4))/(dropSoc/100) ;  // (dropSoc/100)  = soc / 100 
    // qmax_CEDV = QmaxCapcity_Calc/144/dropSoc ;   // (dropSoc/100)  = soc / 100 
    // qmax_CEDV = QmaxCapcity_Calc*100/144/dropSoc/100 ;   // (dropSoc/100)  = soc / 100 
    // qmax_CEDV_temp = QmaxCapcity_Calc*25/36/dropSoc/100 ;   // (dropSoc/100)  = soc / 100        
    // qmax_CEDV_temp = QmaxCapcity_Calc*1/36/dropSoc/4 ;   // (dropSoc/100)  = soc / 100   
    qmax_CEDV_temp = QmaxCapcity_Calc/dropSoc/144 ;   // (dropSoc/100)  = soc / 100   


    // 6350
    // 6355
    // t_com31_out = qmax_CEDV_temp ;


    return qmax_CEDV_temp  ;
}


void QMax_Calc_CEDV(void)
{
    uint16_t aidxq1 = 0;
    int8_t dropSoc;
    uint16_t CEDV_soc_range = 0 ;

    // uint16_t temp_result  ; //  temp_result  =  QmaxCapcity_Calc/qmax_CEDV  ;

    // if (Ts_max >= D_Qmax_Temp_Low_limit && Ts_max <= D_Qmax_Temp_High_limit && _CycleCount > D_Qmax_Cycle_limit)
    // if (Ts_max >= 10 && Ts_max <= 40 )

   //  t_com7e_out =  Ts_max ;
   //  t_com7f_out = f_relax;
   //  t_com80_out = f_Qmax_start ;
    //t_com81_out = V_min ; 
    // t_com82_out =  at_startqmax_cnt ;
    // t_com83_out = at_endqmax_cnt  ;
    // t_com84_out  =  f_Qmax_end  ;
    // t_com9e_out = PackQamxInitSOC;
    
    // t_com1d_out = f_relax_last_CEDV;
    // t_com1e_out = f_chg_dsg_confirmed;
    // t_com87_out =  QmaxCapcity_Calc/14400;

    if (f_relax)  // update soc_out_how every one hour .
    {
        Cnt_update_soc_CEDV++;
        if (Cnt_update_soc_CEDV >= 3600) // 1 minute = 60 * 4 = 240  , 1s at relax .
        {
            Cnt_update_soc_CEDV = 0;
            // for (aidxq1 = 0; (aidxq1 < 19) && (V_min > SOC_OCV_103_TBL[aidxq1 + 1]); aidxq1++)
            for (aidxq1 = 0; (aidxq1 < 102) && (V_min > SOC_OCV_103_TBL[aidxq1]); aidxq1++)
                ;
            if (aidxq1 >= 102)
            {
                if (V_min >= SOC_OCV_103_TBL[102])
                {
                    aidxq1 = 102;
                }
                else
                {
                    if ((SOC_OCV_103_TBL[102] - V_min) > (SOC_OCV_103_TBL[102] - SOC_OCV_103_TBL[101]) / 2)
                        {
                            aidxq1 = 102;
                        }
                    else
                    {
                        aidxq1 = 101;
                    }
                }


                SOC_CEDV = aidxq1;
            }
            else //  else  must < 102  <=101 , less than aidxq1
            {
                if ((V_min - SOC_OCV_103_TBL[aidxq1]) > (SOC_OCV_103_TBL[aidxq1 + 1] - SOC_OCV_103_TBL[aidxq1]) / 2)
                {
                    SOC_CEDV = aidxq1 + 1;
                }
                else
                {
                    SOC_CEDV = aidxq1;
                }
            }
            t_com8d_out = SOC_CEDV;
            Record_lrc_w_CEDV =  (uint32_t)qmax_CEDV*SOC_CEDV*144+(uint32_t)qmax_CEDV*SOC_CEDV*71/50; // capcity + capcity /100 ;
        }
    }
    else
    {
        Cnt_update_soc_CEDV = 0;
    }

    if (f_relax)
    {
         Cnt_update_soc_CEDV++;
        if ((V_min >=3671)&&(V_min<= 3818))
        {
            QMaxUpdateReset_CEDV();
        }
        else
        {
            if (Ts_max > 0 && Ts_max <= 40)
            {
                if ((!f_Qmax_start)) // -1.5 0 1 2 ....99 100 101
                {
                    if (V_min >= SOC_OCV_103_TBL[0]) // 20-40
                    {
                        at_startqmax_cnt++;
                        if (at_startqmax_cnt >= 3600) // 1 minute = 60 * 4 = 240  , 1s at relax .
                        {
                            at_startqmax_cnt = 3600;
                            // for (aidxq1 = 0; (aidxq1 < 19) && (V_min > SOC_OCV_103_TBL[aidxq1 + 1]); aidxq1++)
                            for (aidxq1 = 0; (aidxq1 < 102) && (V_min > SOC_OCV_103_TBL[aidxq1]); aidxq1++)
                                ;

                            if (aidxq1 >= 102)
                            {
                                if (V_min >= SOC_OCV_103_TBL[102])
                                {
                                    aidxq1 = 102;
                                }
                                else 
                                {
                                    if (( SOC_OCV_103_TBL[102]-V_min) > (SOC_OCV_103_TBL[102] - SOC_OCV_103_TBL[101]) / 2)
                                    {
                                        aidxq1 = 102;
                                    }
                                    else
                                    {
                                        aidxq1= 101;
                                    }
                                }
                                PackQamxInitSOC = aidxq1;

                            }
                            else //  else  must < 102  <=102 , less than aidxq1
                            {
                                if ((V_min - SOC_OCV_103_TBL[aidxq1]) > (SOC_OCV_103_TBL[aidxq1 + 1] - SOC_OCV_103_TBL[aidxq1]) / 2)
                                {
                                    PackQamxInitSOC = aidxq1 + 1;
                                }
                                else
                                {
                                    PackQamxInitSOC = aidxq1;
                                }
                            }
                            SOC_CEDV =  PackQamxInitSOC ;   // f_relax time sufficient time , update SOC .
                            t_com8d_out  =  SOC_CEDV  ;
                          //  t_com99_out = aidxq1;
                            Record_lrc_w_CEDV =  (uint32_t)qmax_CEDV*SOC_CEDV*144+(uint32_t)qmax_CEDV*SOC_CEDV*71/50; // capcity + capcity /100 ;

                            t_com9a_out = PackQamxInitSOC;
                            for (aidxq1 = 0; (aidxq1 < 102) && (_DAStatus1.CellVoltage1 > SOC_OCV_103_TBL[aidxq1]); aidxq1++)
                                ;

                            if (aidxq1 >= 102)
                            {

                                if (V_min >= SOC_OCV_103_TBL[102])
                                {
                                    aidxq1 = 102;
                                }
                                else
                                {
                                    if ((SOC_OCV_103_TBL[102] - _DAStatus1.CellVoltage1) > (SOC_OCV_103_TBL[102] - SOC_OCV_103_TBL[101]) / 2)
                                        {
                                            aidxq1 = 102;
                                        }
                                    else
                                    {
                                        aidxq1 = 101;
                                    }
                                }

                                Qamx1InitSOC = aidxq1;
                            }
                            else //  else  must < 102  <=101 , less than aidxq1
                            {
                                if ((_DAStatus1.CellVoltage1 - SOC_OCV_103_TBL[aidxq1]) > (SOC_OCV_103_TBL[aidxq1 + 1] - SOC_OCV_103_TBL[aidxq1]) / 2)
                                {
                                    Qamx1InitSOC = aidxq1 + 1;
                                }
                                else
                                {
                                    Qamx1InitSOC = aidxq1;
                                }
                            }
                            f_Qmax_start = ON;
                            f_Qmax_end = OFF;
                            at_endqmax_cnt = 0;
                        }
                        //     calc_Res_k_InitSOC = PackQamxInitSOC;
                        //     t_com9e_out = PackQamxInitSOC;
                        //     Calc_b_aidx();
                        //     Calc_soc_to_res(b_aidx, calc_Res_k_InitSOC); //
                        //     // Calc_soc_to_res(b_aidx,  PackQamxInitSOC);  //
                        //   //  calc_static_k_InitRes = Res_Temp_CEDV_Inner_temp;
                        //     calc_k_initRES =  Res_Temp_CEDV_Inner_temp;
                    }
                    else
                    {
                        QMaxUpdateReset_CEDV();
                    }
                }
                else // 1. relax 2.already qmax satrt finished  = frist Q alrady count  f_Qmax_start== 1
                {
                    if (f_chg_dsg_confirmed == 1) //  means  relax --> startqmax -->chg/dsg
                    {
                        if (V_min >= SOC_OCV_103_TBL[0]) // between 20-40
                        {
                            at_endqmax_cnt++;
                            if (at_endqmax_cnt >= 3600) // at relax , 1s / time   101 or 102 ?
                            {
                                at_endqmax_cnt = 3600;
                                for (aidxq1 = 0; (aidxq1 < 102) && (V_min > SOC_OCV_103_TBL[aidxq1]); aidxq1++)
                                    ;
                                if (aidxq1 >= 102)
                                {
                                    if (V_min >= SOC_OCV_103_TBL[102])
                                    {
                                        aidxq1 = 102;
                                    }
                                    else
                                    {
                                        if ((SOC_OCV_103_TBL[102] - V_min) > (SOC_OCV_103_TBL[102] - SOC_OCV_103_TBL[101]) / 2)
                                        {
                                            aidxq1 = 102;
                                        }
                                        else
                                        {
                                            aidxq1 = 101;
                                        }
                                    }
                                    PackQamxEndSOC = aidxq1;
                                }
                                else //  else  must < 102  <=101 , less than aidxq1
                                {
                                    if ((V_min - SOC_OCV_103_TBL[aidxq1]) > (SOC_OCV_103_TBL[aidxq1 + 1] - SOC_OCV_103_TBL[aidxq1]) / 2)
                                    {
                                        PackQamxEndSOC = aidxq1 + 1;
                                    }
                                    else
                                    {
                                        PackQamxEndSOC = aidxq1;
                                    }
                                }
                                t_com9b_out = aidxq1;         //
                                t_com9c_out = PackQamxEndSOC; // 
                            SOC_CEDV =  PackQamxEndSOC ;   // f_relax time sufficient time , update SOC .

                           //  Record_lrc_w_CEDV = SOC_CEDV * qmax_CEDV/100*14400 ;
                        // relax  + %0.09    
                          
                          //  t_com0f_CEDV =  SOC_CEDV *qmax_CEDV /100 ;
                           t_com8d_out  =  SOC_CEDV  ;  // this should in front of    Record_lrc_w_CEDV = 
                           Record_lrc_w_CEDV =  (uint32_t)qmax_CEDV*SOC_CEDV*144+(uint32_t)qmax_CEDV*SOC_CEDV*71/50; // capcity + capcity /100 ;

                                f_Qmax_end = ON; // t_com84_out  =  f_Qmax_end  ;
                                f_Qmax_start = OFF;
                            }
                        }
                        else
                        {
                            QMaxUpdateReset_CEDV();
                        }
                    }
                }

                if (f_Qmax_end)
                {
                    // CEDV_soc_range = QmaxCapcity_Calc/(3600*4)*1000/t_com18 ; // soc differece  / Design capa *1000
                    if (PackQamxInitSOC > PackQamxEndSOC)
                    {
                        CEDV_soc_range = PackQamxInitSOC - PackQamxEndSOC;
                    }
                    else
                    {
                        CEDV_soc_range = PackQamxEndSOC - PackQamxInitSOC;
                    }
                  //   t_com85_out = CEDV_soc_range;

                    if (CEDV_soc_range >= 55)
                    {
                        // when calc_fcc , calc_qmax first
                        // when calc_Qmax , calc_k first
                        // whe calc k , calc res_init and res_end_first .
                        // res_init already know when calc init soc
                        // calc res_end  , calc  PackQamxEndSOC_leiji_Qcap_soc first .
                        // Calc_k_CEDV() ;
                        qmax_CEDV = QMaxUpdateJudge_CEDV(PackQamxInitSOC, PackQamxEndSOC);
                        // qmax_CEDV1 = QMaxUpdateJudge_CEDV(Qamx1InitSOC, Qamx1EndSOC);
                        // qmax_CEDV2 = QMaxUpdateJudge_CEDV(Qamx2InitSOC, Qamx2EndSOC);
                        // qmax_CEDV3 = QMaxUpdateJudge_CEDV(Qamx3InitSOC, Qamx3EndSOC);
                        // qmax_CEDV4 = QMaxUpdateJudge_CEDV(Qamx4InitSOC, Qamx4EndSOC);
                        //  Record_lrc_w_CEDV_fcc_show = qmax_CEDV * 14400 * SOC_CEDV_show /100;




                        Record_lrc_w_CEDV =  (uint32_t)qmax_CEDV*SOC_CEDV*144+(uint32_t)qmax_CEDV*SOC_CEDV*71/50; // capcity + capcity /100 ;

                        Record_lrc_w_CEDV_fcc_show = (int32_t)(((long)qmax_CEDV * 144) * SOC_CEDV_show);
                        Record_lrc_w_CEDV_fcc_show_last = Record_lrc_w_CEDV_fcc_show ;
                        // Record_lrc_w_CEDV  =  (int32_t)(((long)qmax_CEDV * 144)*SOC_CEDV_show);
                        t_com0f_CEDV_show = (Record_lrc_w_CEDV_fcc_show/(60 * 60 * 4));
                        SOC_CEDV_show  = (uint16_t)((((long)t_com0f_CEDV_show*2000)/ qmax_CEDV + 10)/2)/10;
                        t_com45_out = SOC_CEDV_show ;

                        fcc_use_qmax = qmax_CEDV;
                        t_com31_out = qmax_CEDV;
                        t_com32_out = fcc_CEDV_Ture;
     
                        // QMaxUpdateReset_CEDV();
                    }
                    // else
                    {
                        f_Qmax_start = ON; // add this ,this in    QMaxUpdateReset_CEDV();  is   f_Qmax_start = OFF
                        PackQamxInitSOC = PackQamxEndSOC;
                        //  calc_static_k_InitRes =  calc_Res_k_EndRes ;
                        calc_k_initRES = calc_Res_k_EndRes;
                        Qamx1InitSOC = Qamx1EndSOC;
                        Qamx2InitSOC = Qamx2EndSOC;
                        Qamx3InitSOC = Qamx3EndSOC;
                        Qamx4InitSOC = Qamx4EndSOC;
                        f_Qmax_end = OFF;
                        at_endqmax_cnt = 0;
                        at_startqmax_cnt = 3600;
                        QmaxCapcity_Calc = 0;
                        f_chg_dsg_confirmed = 0;
                        f_CHG_CEDV = 0;
                        f_DSG_CEDV = 0;
                    }
                }
            }
            else
            {
                QMaxUpdateReset_CEDV();
            }
        }
    }
    else // not at relax state
    {
        if (f_Qmax_start) // not at relax state  , first relax already exist
        {
            // at first time into , then make it the state for dsg or chg .
            if (f_chg_dsg_confirmed == 0) //  chg or not dsg use have not confirm
            {

                f_chg_dsg_confirmed = 1;
                //    chg_dsg_confirmed_count = 1;
                // PackQamxInitSOC = (char)aidxq1 * 5 + (short)((short)(V_min - SOC_OCV_103_TBL[aidxq1]) * 5) / (short)(SOC_OCV_103_TBL[aidxq1 + 1] - SOC_OCV_103_TBL[aidxq1]);
            //     calc_Res_k_InitSOC = SOC_OCV_103_TBL[aidxq1];
            //     Calc_soc_to_res(b_aidx, calc_Res_k_InitSOC);
            //    //  calc_static_k_InitRes = Res_Temp_CEDV_Inner_temp;
            //     calc_k_initRES =  Res_Temp_CEDV_Inner_temp; 
                //   for( aidxq1=0; V_min >= SOC_OCV_103_TBL[aidxq1+1] && aidxq1 < 19; aidxq1++ );
                // first time checked ,and now not relax .

                    calc_Res_k_InitSOC = PackQamxInitSOC;
                    t_com9e_out = PackQamxInitSOC;
                    Calc_b_aidx();
                    Calc_soc_to_res(b_aidx, calc_Res_k_InitSOC); //
                    // Calc_soc_to_res(b_aidx,  PackQamxInitSOC);  //
                  //  calc_static_k_InitRes = Res_Temp_CEDV_Inner_temp;
                    calc_k_initRES =  Res_Temp_CEDV_Inner_temp; 

                if ((f_relax_last_CEDV != 0) && (f_relax == 0)) // last time relax , this time not relax .
                {
                   // t_com1d_out = f_relax_last_CEDV;
                    f_chg_dsg_confirmed = 1;
                   // t_com1e_out = f_chg_dsg_confirmed;
                    // can not be put here
                    if (f_charge)
                    {
                        f_CHG_CEDV = 1;
                        f_DSG_CEDV = 0;
                    }
                    else if ((f_discharge != 0) && (f_relax == 0))
                    {
                        f_CHG_CEDV = 0;
                        f_DSG_CEDV = 1;

                        // add calc_k here . 
                        // 1. use  dsg start 
                        // 2. use (ocv - realvolrage ) / r 

                      //   Calc_k_CEDV() ;  // if  add here will calculate right now . 
                      // need to put a place where and recongnize and hold several several minutes . 
                    }
                }
               // t_com1f_out = f_CHG_CEDV;
               // t_com41_out = f_DSG_CEDV;
            }
            else // confirmed CHG or DSG already   first time come in , not relax
            {
                if (f_CHG_CEDV)
                {
                    if ((f_discharge != 0) && (f_relax == 0))
                    {
                        QMaxUpdateReset_CEDV();
                    }
                    else
                    {
                       // t_com42_out = I_abs;
                        QmaxCapcity_Calc += I_abs;
                        // log

                        // to do dead band current limit .less than 1 %
                        // if (I_abs < cur_dead_band)
                        if (I_abs < D_Calibdata_Dead_Band) // < deadband current .   D_Calibdata_Dead_Band
                        {
                            QmaxCapcity_Calc_deadband += I_abs;
                            if (QmaxCapcity_Calc_deadband / 36 > t_com18 * 4) // QmaxCapcity_Calc_deadband > t_com18 *3600*4/100
                            {
                                QMaxUpdateReset_CEDV();
                            }
                        }else
                        {
                             QmaxCapcity_Calc_deadband = 0 ;
                        }
                    }
                }
                else if (f_DSG_CEDV)
                {
                    if (f_charge)
                    {
                        QMaxUpdateReset_CEDV();
                    }
                    else
                    {
                        QmaxCapcity_Calc += I_abs;
                        if (I_abs < D_Calibdata_Dead_Band) // < deadband current .   D_Calibdata_Dead_Band
                        {
                            QmaxCapcity_Calc += I_abs;
                            if (QmaxCapcity_Calc / 36 > t_com18 * 4) // QmaxCapcity_Calc_deadband > t_com18 *3600*4/100
                            {
                                QMaxUpdateReset_CEDV();
                            }
                        }
                        else
                        {
                            QmaxCapcity_Calc_deadband = 0;
                        }
                    }
                }
            }
        }
        else // not relax && not  f_Qmax_start , CHG or DSG
        {
            QMaxUpdateReset_CEDV();
        }
    }

   // t_com1f_out = f_CHG_CEDV;
  //  t_com41_out = f_DSG_CEDV;
   //  t_com42_out =  I_abs ;

   //  t_com43_out = QmaxCapcity_Calc%14400 ; 

    f_relax_last_CEDV = f_relax ; 
}

void Calc_FCC_CEDV(void)  // read four , % -1.5 0 1 2 3 4 ....101 res  , calc one 0% ---res ,  match from  0 1 2 3 
{
    uint8_t soc_to_res_index;
    uint16_t Res_Temp_CEDV_Inner_turn;
    uint16_t Res_Temp_CEDV_Inner_out;
    int16_t judge_greater_than_0;
    int16_t judge_greater_than_0_add_k;
    uint16_t Res_Temp_CEDV_Inner_turn_new;

    if ((f_discharge == 1) && (f_relax == 0))   // fangdian not jingzhi .
    {
        Calc_b_aidx();
        for (soc_to_res_index = 0; soc_to_res_index < 102; soc_to_res_index++)
        {
            // diao yong  获取 00 电电压内阻函数
            Calc_soc_to_res(b_aidx, soc_to_res_index);
            Res_Temp_CEDV_Inner_turn = Res_Temp_CEDV_Inner_temp;
                                                                     // Res_Temp_CEDV_Inner_turn_new = Res_Temp_CEDV_Inner_turn*(k_CEDV/1000) + Res_Temp_CEDV_Inner_turn*(k_CEDV%1000/100)/10 +  \
        //    Res_Temp_CEDV_Inner_turn*(k_CEDV%100/10)/100+Res_Temp_CEDV_Inner_turn*(k_CEDV%10/1)/1000; // ？
                                                                     // t_com39_out = Res_Temp_CEDV_Inner_turn_new ;
           //  judge_greater_than_0 = SOC_OCV_103_TBL[soc_to_res_index] - I_abs * Res_Temp_CEDV_Inner_turn/10000 - D_0PVOLT;
            // t_com45_out = Res_Temp_CEDV_Inner_turn;
           // t_com4c_out = SOC_OCV_103_TBL[soc_to_res_index];
            //   t_com4d_out  =  judge_greater_than_0  ;
            //  t_com4e_out = soc_to_res_index;
// with k  calc REs 



            Res_Temp_CEDV_Inner_turn_new = Res_Temp_CEDV_Inner_turn*(k_CEDV/1000) + Res_Temp_CEDV_Inner_turn*(k_CEDV%1000/100)/10 +  \
            Res_Temp_CEDV_Inner_turn*(k_CEDV%100/10)/100+Res_Temp_CEDV_Inner_turn*(k_CEDV%10/1)/1000; //

           
            judge_greater_than_0_add_k =  SOC_OCV_103_TBL[soc_to_res_index] \
            - (uint16_t)((long)I_abs * Res_Temp_CEDV_Inner_turn_new/10000) - D_Discharge_0_voltage ;  //  D_0PVOLT  staitc      
      
            // if (judge_greater_than_0 < 0)
            // {
            //     // t_com4d_out =10000+judge_greater_than_0  ;
            //     // t_coma1_out = 1  ;
            // }
            // else
            // {
            //     // t_com4d_out = judge_greater_than_0  ;
            //     // t_coma1_out = 0  ;
            // }

           // if (judge_greater_than_0 >= 0)
           if (judge_greater_than_0_add_k >= 0)
            {
               t_com4c_out = D_Design_Capacity_mAh;
               t_com4d_out = Res_Temp_CEDV_Inner[6];  
            //    t_com7e_out = I_abs;
            //    t_com7f_out = D_Discharge_0_voltage;
            //    t_com80_out = soc_to_res_index;
            //    t_com81_out = Res_Temp_CEDV_Inner_turn;
            //    t_com8f_out = Res_Temp_CEDV_Inner_temp; // log r
            //    t_com82_out = k_CEDV;
            //    t_com83_out = Ts_max;

            //      t_com85_out = Ts_max;

            //    t_com88_out = awork1_CEDV;
            //    t_com89_out = awork2_CEDV;
            //    t_com8a_out = awork3_CEDV;
            //    t_com8b_out = awork4_CEDV;
            //    t_com8e_out = b_aidx;

            // //    t_com90_out = Res_Temp_CEDV_Inner[0];
            // //    t_com91_out = Res_Temp_CEDV_Inner[1];
            // //    t_com92_out = Res_Temp_CEDV_Inner[2];
            // //     t_com93_out = Res_Temp_CEDV_Inner[3];
            //    t_com94_out = Res_Temp_CEDV_Inner[4];
            // //    t_com95_out = Res_Temp_CEDV_Inner[5];
            // //       t_com98_out = Res_Temp_CEDV_Inner[8];

            //    t_com95_out = twork1_out;
            //    t_com98_out = twork2_out;
                  t_com98_out = Res_Temp_CEDV_Inner[8];


               // t_com97_out = Res_Temp_CEDV_Inner[7];
              
                t_com1f_out = Res_Temp_CEDV_Inner_turn_new;

               Res_Temp_CEDV_Inner_out = Res_Temp_CEDV_Inner_turn;
               fcc_CEDV_Ture = (uint16_t)(long)qmax_CEDV * (102 - soc_to_res_index) / 102;
               t_com32_out = fcc_CEDV_Ture;
               t_com31_out = qmax_CEDV;
              // t_com8b_out = fcc_use_qmax;
            
               break;
            }
            else
            {
                // t_com4d_out = 0;
            }
        }
    }else
    {

    }
}


void Make_RC_CEDV(void)

{
	uint16_t	tworka;
    uint16_t	twork2;
	tworka = (uint16_t)(Record_lrc_w_CEDV_fcc_show/(60*60*4));			// RC = RC_W / (60min*60sec*4)
   
    // if( twork > fcc_CEDV_Ture  )						// RC > FCC ?
    if (tworka > qmax_CEDV)
    {

        t_com0f_CEDV_show = fcc_use_qmax; // RC = FCC
    }
    else
    {
        t_com0f_CEDV_show = tworka;
    }

    t_com42_out = t_com0f_CEDV_show;

     twork2 = (uint16_t)(Record_lrc_w_CEDV / (60*60*4));   // CEDV at most = 102 .
    if (twork2 >= qmax_CEDV+qmax_CEDV/50-1 )  // cause soc_CEDV index : less than 102 , can reach 101 .
    {
        t_com0f_CEDV = qmax_CEDV+qmax_CEDV/50-1;
    }
    else
    {
        t_com0f_CEDV = twork2;
    }
}



void Calc_fulchg_dsg_cap(void)   


// TO DO  
// 1. wendu beilv condition 
// 2.  add f_study_d3_ful 
{
	uint8_t beilv;

	static int32_t ful_dsg_cap;
	static uint8_t  Count_xiao_beilv_3s ;
	uint16_t ful_dsg_cap_FCC;
  

	// t_com2d_f_study_d3_ful = f_study_d3_ful  ;
	// t_com2e_ful_dsg_cap = ful_dsg_cap / 3600 ;  //single 

   //  t_com2e_ful_dsg_cap = ful_dsg_cap / 14400 ;  //muti

	// static uint16_t ful_dsg_cap_FCC;

	// beilv = (uint16_t)((long)I_abs * 100/D_Design_Capacity_mAh);  //D_Design_Capacity_mAh  _DesignCapacity

	if ((f_charge == ON) && (Current() > 0)) // Charging ?
	{
		if (f_fullchg == OFF)
		{
			f_study_d3_ful = OFF;
          //   ful_dsg_cap = 0 ;
		}
	}
 

	//if (((CellTemp > 15) && (CellTemp <= 45)) && ((beilv >= 10) && (beilv <= 70)))  // must charge or dsg .
	//{// chg clear . dsg : use 
		if (V_min >= D_Discharge_0_voltage)   
		{
			if (!f_charge) // must dsg not relax 
			{
				if (f_study_d3_ful == ON)
				{
                   
					ful_dsg_cap += I_abs;
                     t_com8b_out = ful_dsg_cap/14400;
                      t_com8e_out = 3 ;

				}else
				{
                    t_com8b_out = 2;
					f_study_d3_ful = OFF;
					ful_dsg_cap = 0;
				}
			} // else  no need else , cause f_charge will clear all 
		}else   //  V_min <= D_Discharge_0_voltage
		{
			if (!f_charge)
			{
				if (f_study_d3_ful == ON)  
				{

                      t_com94_out = 4 ;
					// can go here , must have updated cpl . 
					//cause  f_study_d3_ful == ON means have f_study_d2 have dupdated ..
					ful_dsg_cap += I_abs;
					f_study_d3_ful = OFF;
					// ful_dsg_cap_FCC = ful_dsg_cap/3600;  // single 

                    ful_dsg_cap_FCC = ful_dsg_cap/14400;   //14400 
					fcc_CEDV_Ture = ful_dsg_cap_FCC  ; //update 0_voltage FCC 
                    t_com32_out = fcc_CEDV_Ture;
				}
				else
				{

                     t_com94_out = 8 ;
					f_study_d3_ful = OFF;
					ful_dsg_cap = 0;

				}
			}
		}

	  t_com95_out = f_study_d3_ful;


}




void Calc_RC_CEDV(void)
{

   
	static uint8_t	adlogc;							// Power consumption 10times counter
	
	uint32_t	lwork;
	uint16_t	twork;
    static uint16_t VoltagetoRSOCcount_CEDV;

    uint16_t	I_abs_qmax_chu_fcc;
    uint16_t	qmax_chu_fcc = 10000;

    if (0 != fcc_CEDV_Ture)
    {
        qmax_chu_fcc = qmax_CEDV * 10000 / fcc_CEDV_Ture;
    }
    else
    {
        qmax_chu_fcc = 10000;
    }

    Calc_fulchg_dsg_cap();

    I_abs_qmax_chu_fcc = I_abs*(qmax_chu_fcc/10000) + I_abs*(qmax_chu_fcc%10000/1000)/10+ \
         I_abs*(qmax_chu_fcc%1000/100)/100 + I_abs*(qmax_chu_fcc%100/10)/1000+  \
         I_abs*(qmax_chu_fcc%10)/10000   ;

    // t_com8e_out =  I_abs_qmax_chu_fcc ;
    
	if (Current() > 0) 
    {
         VoltagetoRSOCcount_CEDV = 0 ;
       //  Record_lrc_w_CEDV_fcc_show += I_abs   ;
        Record_lrc_w_CEDV_fcc_show += I_abs_qmax_chu_fcc;
        Record_lrc_w_CEDV += I_abs ;

    }else   // Current()<=0 
    {
        Record_lrc_w_CEDV_fcc_show -= I_abs_qmax_chu_fcc ;
        Record_lrc_w_CEDV -= I_abs ;

		// if(V_min < D_Discharge_0_voltage)		// lower than 0% voltage ? D_0PVOLT
		if(V_min <= D_0PVOLT) 
		{
            
            VoltagetoRSOCcount_CEDV++ ;
			if(VoltagetoRSOCcount_CEDV >= D_Discharge_0_voltage_Delay*4 )  // D_Discharge_0_voltage_Delay*4
			{
				VoltagetoRSOCcount_CEDV = D_Discharge_0_voltage_Delay*4 ;
				Record_lrc_w_CEDV_fcc_show = 0;						// Correction capacity = 0
				// lrccr_w = 0;					// Charge relearn capacity = 0
	//			f_gs_fd = ON; //20230918
				t_com0f_CEDV_show = 0;					// RC[mAh] = 0
               //  t_com0f_CEDV = 0 ;
			    SOC_CEDV_show = 0  ;
              //   SOC_CEDV = 0 ;  soc right bubian .

				return;
			}
		}else
		{
			VoltagetoRSOCcount_CEDV= 0 ;
		}
    }


    if (Record_lrc_w_CEDV_fcc_show >= qmax_CEDV * 14400)  // this is show for out 
    {
        Record_lrc_w_CEDV_fcc_show = qmax_CEDV * 14400;
    }

   //  if (Record_lrc_w_CEDV >= qmax_CEDV * 14400+ qmax_CEDV * 286 + )  // qmax * 101.99
   // 
    if (Record_lrc_w_CEDV >= qmax_CEDV * 14686  )  // qmax * 101.99
    {
        Record_lrc_w_CEDV = qmax_CEDV *14686; 
    }


// no need more than  (V_min > D_0PVOLT)
    if (SOC_CEDV_show != 0)
    {
        if (Record_lrc_w_CEDV_fcc_show <= qmax_CEDV * 80)
        {
            Record_lrc_w_CEDV_fcc_show = qmax_CEDV * 80; // Set 0
        }
        if (Record_lrc_w_CEDV_fcc_show_last <= qmax_CEDV * 80)
        {
            Record_lrc_w_CEDV_fcc_show_last = qmax_CEDV * 80; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
        }
    }
    else //  (V_min > D_0PVOLT)  && soc == 0
    {
       if (!f_charge)
        {
            Record_lrc_w_CEDV_fcc_show = 0;
            Record_lrc_w_CEDV_fcc_show_last = 0;
        }
    }

	
    if (Record_lrc_w_CEDV_fcc_show <= 0)
    {
        Record_lrc_w_CEDV_fcc_show = 0; // Set 0
    }
    if (Record_lrc_w_CEDV_fcc_show_last <= 0)
    {
        Record_lrc_w_CEDV_fcc_show_last = 0; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
    }

    Record_lrc_w_CEDV_fcc_show_last = Record_lrc_w_CEDV_fcc_show ;

    Make_RC_CEDV() ;

    t_com91_out = t_com0f_CEDV ;


}


void Calc_RSOC_CEDV(void)
{
	uint16_t atwork1;
    uint16_t atwork2;
	// RSOC = RemainingCapacity / FullChargeCapacity * 100
	// Calc RSOC and store to temporary area.
	// The result is rounded off.
	atwork1 = (uint16_t)((((long)t_com0f_CEDV_show * 2000)/qmax_CEDV+10)/ 2);

	if(!f_charge)  // use on computer , if charge , sishewuru .
	{
		if(atwork1 >=10)   // soc more than 1%  .  jia 1 .
		{	
			atwork1 += 5 ;
		}
	}



	if(atwork1 > 995)
	{
		if(D_SBS_Gauging_Configuration_RSOCL == ON)							// More than 99% ?
		{
			if(f_VCT)
			{
				atwork1 = 100;						// Set to 100% (Don't make >100)
			}
			else
			{
				atwork1= 99;
			}
		}
		else
		{
			atwork1 /= 10;		
		}
	}
	else if(atwork1 <= 10 && D_SBS_Gauging_Configuration_1PERCENT_HOLD)
	{
		if(Current() < 0 && f_discharge&& f_relax == 0)//f_discharge -->relax with delay
		{
			// if(V_min >= D_Discharge_0_voltage) //  D_0PVOLT
			if(V_min > D_0PVOLT) 
			{
                if (SOC_CEDV_show > 0) // in case , when discharge , voltage raise up . still hold 1
                {
                    atwork1 = 1;
                }
                else
                {
                    atwork1 = 0;
                }
            }
			else
			{
				atwork1 /= 10; 
			}
		}
		else
		{
			atwork1 /= 10;
		}
	}
	else
	{
		atwork1/= 10;
	}

	SOC_CEDV_show = atwork1;		
    t_com45_out = SOC_CEDV_show ;					// Set to RSOC  RSOC 


    atwork2 = (uint16_t)((((long)t_com0f_CEDV*2000)/qmax_CEDV)/ 2);  // jia 0.99%    // to do 20250919
    SOC_CEDV = atwork2/10;		
    t_com8d_out  =  SOC_CEDV  ;
}


static void FullCharge_CEDV(void)
{
    uint16_t twork;
 
   // if (Ts_max < D_FCC_relearn_temp_limit || f_study_c == OFF) // Less than relearn limit temp  // or Charge relearn flag=OFF ?
    if (Ts_max < D_FCC_relearn_temp_limit ) 
    {
        // if (Record_trek_cnt != 0 && D_FCC_Deterioration_capacity != 0) // Degradation cnt is not 0 ?
        // {
        //     twork = (uint16_t)(((long)Record_trek_cnt * D_FCC_Deterioration_capacity) / 100);
        //     if (fcc_use_qmax > twork) // Not Under flow ?
        //     {
        //        fcc_use_qmax = fcc_use_qmax - twork;
        //         fcc_use_qmax = (uint16_t)((long)fcc_use_qmax * ABS(D_Cycle_Count_Percentage)/100);
        //     }
        //     else
        //     {
        //         // fcc_use_qmax = 10; // Under flow
        //         // tccup = (uint16_t)((long)fcc_use_qmax * ABS(D_Cycle_Count_Percentage)/100);
        //     }
        // }
    }
    else
    {                                            // Make relearning
      //  FCC_Limit_Chk();                         // FCC inc/dec limit check

        Record_lrc_w_CEDV_fcc_show =  (uint32_t)fcc_use_qmax * (60 * 60*4);   // idea rc * 14400
        //tccup = (uint16_t)((long)fcc_use_qmax * ABS(D_Cycle_Count_Percentage)/100);
        SOC_CEDV_show = 100;     // RSOC=100%
        t_com0f_CEDV_show = fcc_use_qmax; // Update RemainingCapacity()

        //Record_lrc_w_CEDV =  (uint32_t)qmax_CEDV * (60 * 60*4)/100*101.99;   
        Record_lrc_w_CEDV =  (uint32_t)qmax_CEDV*14686;
        SOC_CEDV = 101;     // soc_CEDV =101 ; 
       //  t_com0f_CEDV = qmax_CEDV+ qmax_CEDV/100; // Update RemainingCapacity()  // to do 20250919

    }

    if (f_fullchg_CEDV == OFF) // FULLY_CHARGED == OFF ?
    {
        Record_lrc_w_CEDV_fcc_show = (long)fcc_use_qmax * 14400; // Calc RC integration work
        t_com0f_CEDV_show = fcc_use_qmax; // Update RemainingCapacity()
        SOC_CEDV_show = 100;     // RSOC=100%
        t_com42_out = t_com0f_CEDV_show  ;

        Record_lrc_w_CEDV =  (uint32_t)qmax_CEDV * 14686;  // full qmax* 1.0199    casue calc soc_CEDV use :  rc /fcc 
        SOC_CEDV = 101;     // soc_CEDV =101 ; 

    }
    f_fullchg_CEDV = ON; // Set FULLY_CHARGED
    // f_ful_chg_once = 1 ;
    f_VCT = ON;
    //	acccv_cnt = 0;								// Clear CC/CV time counter
   // t_com0c = 0;     // Clear MaxError
    //lmaxerr_cnt = 0; // Clear MaxError counter
   //  _ChargingCurrent = 0;     // ChargingCurrent() = 0

   Record_lrc_w_CEDV_fcc_show_last = Record_lrc_w_CEDV_fcc_show ;
}



void FullCharge_Chk_CEDV(void)
{
    // FCCCEDV
    
    uint16_t twork;

    if (SOC_CEDV_show < 100)
    {
        f_fullchg_CEDV = OFF;
    }

    
 
    if (f_charge == ON && f_chg) // Charging current detection ?
    {
        // t_com80_out = V_max;
        t_com4e_out = I_abs ;
        // t_com92_out =  f_fullchg_CEDV ;

        if (f_fullchg_CEDV == ON) // FULLY_CHARGED = ON ?
        {
            if (t_com0f_CEDV_show >= fcc_use_qmax) // RC >= FCC ?
            {
                FullCharge_CEDV(); // Full Charge Processing
            }
        }
        else
        {
            if ((V_max >= (_ChargingVoltage/NUMBER_SERIES - D_Termination_Charge_Term_Voltage)) && (_AverageCurrent < Charge_Term))
            {
                tfc_cnt_CEDV++; // Full Charge check count + 1
                rc_integral_CEDV += I_abs;

                // Full charge determination time elapsed ?
                if (tfc_cnt_CEDV >= D_Termination_Fullcharge_judgement_time )
                {

                    // t_com7e_out = rc_integral_CEDV%14400  ;
                    //  t_com7f_out = rc_integral_CEDV/14400 ;


                    if (rc_integral_CEDV /4/ 3600 >= D_Termination_Charge_Term_Taper_Capacity)
                    {
                        tfc_cnt_CEDV = 0;
                        rc_integral_CEDV = 0;
                        FullCharge_CEDV(); // Full Charge Processing
                    }
                    else
                    {
                        tfc_cnt_CEDV = D_Termination_Fullcharge_judgement_time - 1;
                    }
                }
            }

        }
    }
    else
    {
        tfc_cnt_CEDV = 0; // Clear Full Charge check count
        rc_integral_CEDV = 0;
    }

      // t_com82_out = tfc_cnt_CEDV ;
     //   t_com85_out =D_Termination_Charge_Term_Taper_Capacity ;


    
}



void fuse_low()
{
    FUSE_OUT(0);
    f_fuse_out = OFF;
}

void FUSE_Contrl()
{
    if(f_fuse_out)
    {
        if(D_FETOptions_PACK_FUSE)
        {
            if(PackVoltage() > D_Fuse_Min_Blow_Fuse_Voltage)
            {
                FUSE_OUT(1);
                if (!getSoftTimerStatus(SOFT_TIMER_FUSE_LOW_ID))
                {
                    StartSoftTimer(SOFT_TIMER_FUSE_LOW_ID, SINGLE_MODE, D_Fuse_Blow_Timeout * 1000, fuse_low);
                }

                // fuse_blow_flag = 1;
                // // FUSE_OUT(1);
                // if(fuse_timeout/1000 > D_Fuse_Blow_Timeout)
                // {
                //     fuse_blow_flag = 0;
                //     fuse_timeout = 0;
                //     f_fuse_out = OFF;
                //     // FUSE_OUT(0);
                // }
            }
            
        }
        else
        {
            if(Voltage() > D_Fuse_Min_Blow_Fuse_Voltage)
            {
                FUSE_OUT(1);
                if (!getSoftTimerStatus(SOFT_TIMER_FUSE_LOW_ID))
                {
                    StartSoftTimer(SOFT_TIMER_FUSE_LOW_ID, SINGLE_MODE, D_Fuse_Blow_Timeout * 1000, fuse_low);
                }
            }
        }
    }
    
}
void FET_Contrl(void)
{
    static uint8_t flag = 0;
    if (((SafetyStatus(OTD) || SafetyStatus(UTD)) && f_fullchg) || SafetyStatus(COVL) || SafetyStatus(OCDL) || SafetyStatus(OTF) || SafetyStatus(ASCD) || SafetyStatus(ASCC) || SafetyStatus(AOLD) ||
        f_ship || SafetyStatus(AOLDL) || SafetyStatus(ASCDL) || SafetyStatus(ASCCL) ||
        (_PFStatus.value & 0xFFBFFFFF)) // D-ON && C-ON
    {
        Fet_Ctrl = FET_OFF;
        // flag = 0;
    }

    if (SafetyStatus(COV) || SafetyStatus(OCC1) || SafetyStatus(OCC2) || SafetyStatus(OTC) || SafetyStatus(UTC) || SafetyStatus(HWD) || SafetyStatus(PTO) || SafetyStatus(CTO) || SafetyStatus(OC) || SafetyStatus(PCHGC) || SafetyStatus(CHGC) || SafetyStatus(CHGV) || (!f_FET_EN && !f_CHG_EN)) // D-ON && C-OFF
    {
        Fet_Ctrl &= CFET_OFF;
        // flag = 0;
    }

    if ((SafetyStatus(CUV) &&(!f_charge))|| SafetyStatus(CUVC) || SafetyStatus(OCD1) || SafetyStatus(OCD2) ||
        SafetyStatus(OTD) || SafetyStatus(UTD) || SafetyStatus(OCDL) || (!f_FET_EN && !f_DSG_EN)) // D-OFF && C-ON
    {
        Fet_Ctrl &= DFET_OFF;
        // flag = 0;
    }

if(!f_IN_CFET || !f_SU_CFET)
{
    Fet_Ctrl &= CFET_OFF;
}
/************************** Sleep Mode ******************************/
    if(!f_sleepPCFET)
    {
        Fet_Ctrl &= PCFET_OFF;
    }
    if (!f_sleepCFET)
    {
        Fet_Ctrl &= CFET_OFF;
    }
    if(!f_sleepDFET)
    {
        Fet_Ctrl &= DFET_OFF;
    }
/*************************** Shutdown ********************************/
    if(!f_sdvDFET || !f_sdmDFET)
    {
        // printf("sdv %d\nsdm %d\n",f_sdvDFET,f_sdmDFET);
        Fet_Ctrl &= DFET_OFF;
    }
    if(!f_sdmCFET || !f_sdvDFET)
    {
        Fet_Ctrl &= CFET_OFF;
    }
/*********************************************************************/
    if (D_DA_Configuration_NR == 0) // 5.16
    {
        if (!f_pres) // 5.16
        {
            Fet_Ctrl &= (DFET_OFF & CFET_OFF);
            // flag = 0;
        }
    }
    if (f_gs_fc)
    {
        if ((t_com0d == 100) && !f_discharge)
        {
            if (COFF_delay / 1000 >= 2)
            {
                COFF_delay = 0;
                flag = 1;
            }
            if (flag)
            {
                Fet_Ctrl &= CFET_OFF;
            }
        }
        else
        {
            flag = 0;
            if (!f_discharge)
            {
                Fet_Ctrl &= CFET_OFF;
                // flag = 0;
            }
        }
    }

    if(f_discharge && !(_PFStatus.value & 0xFFFFFFFF))
    {
        Fet_Ctrl |= 0x02;
    }

    Set_FET();
}

static void FullCharge(void)
{
    uint16_t twork;
    if (D_Control_flag_1_DIS_DSG_Releaning == OFF) // Dischg relearn not disable ?
    {
        f_study_d = ON; // Set discharge relearn flag
        f_study_d1 = ON;
        f_study_d2 = ON;
        f_study_d3_ful = ON;
    }

    if (Ts_max < D_FCC_relearn_temp_limit || f_study_c == OFF) // Less than relearn limit temp  // or Charge relearn flag=OFF ?
    {
        if (Record_trek_cnt != 0 && D_FCC_Deterioration_capacity != 0) // Degradation cnt is not 0 ?
        {
            // FCC = FCC - (Degradation counter * Degradation capacity)
            twork = (uint16_t)(((long)Record_trek_cnt * D_FCC_Deterioration_capacity) / 100);
            if (t_com10 > twork) // Not Under flow ?
            {
                t_com10 = t_com10 - twork;
                tccup = (uint16_t)((long)t_com10 * ABS(D_Cycle_Count_Percentage)/100);
            }
            else
            {
                t_com10 = 10; // Under flow
                tccup = (uint16_t)((long)t_com10 * ABS(D_Cycle_Count_Percentage)/100);
            }
        }
    }
    else
    {                                            // Make relearning
        arelearn_cnt = 0;                        // Clear Relearning counter
        f_relearn = OFF;                         // Clear Relearning flag
        tcom10c_w = (uint16_t)(lrccr_w / 14400); // Calc new FCC
        FCC_Limit_Chk();                         // FCC inc/dec limit check
        t_com10 = tcom10c_w;                     // Set FullChargeCapacity()

        Record_lrc_w =  (uint32_t)t_com10 * (60 * 60*4);   // idea rc * 14400
        Record_Ilrc_w = (long)t_com89* 14400; // Calc RC integration work

        // Record_Ilrc_w =  (uint32_t)t_com88 * (60 * 60*4);   // idea rc * 14400
        tccup = (uint16_t)((long)t_com10 * ABS(D_Cycle_Count_Percentage)/100);

        t_com8a = 100 ;  // idea rsoc = 100 
        t_com0d = 100; 

        t_com0f = t_com10; // Update RemainingCapacity()
        t_com88 =  t_com89 ;  // idea rc = idea fcc 
        

    }
    Record_trek_cnt = 0; // Clear degradation counter
    f_study_c = OFF;

    if (f_fullchg == OFF) // FULLY_CHARGED == OFF ?
    {
        Record_lrc_w = (long)t_com10 * 14400; // Calc RC integration work
        Record_Ilrc_w = (long)t_com89 * 14400; // Calc RC integration work
        if (f_study_d == ON)           // Start discharge relearn ?
        {
            lrcdr_w = 0; // Clear discharge relarn cap.
        }
        t_com0d = 100;     // RSOC=100%
        t_com8a = 100 ;  // idea rsoc = 100 

        t_com0f = t_com10; // Update RemainingCapacity()
        t_com88 = t_com89 ;  // idea rc = idea fcc 
        
        // (To prevent changing CC when capacity is jumped.)
        toldrc = t_com10; // Update to RemCap value last time
                          // Update last RemCap
    }
    f_fullchg = ON; // Set FULLY_CHARGED
    f_ful_chg_once = 1 ;
    f_VCT = ON;
    //	acccv_cnt = 0;								// Clear CC/CV time counter
   // t_com0c = 0;     // Clear MaxError
    lmaxerr_cnt = 0; // Clear MaxError counter
    _ChargingCurrent = 0;     // ChargingCurrent() = 0
}

/********************************
 * Function Name: FullCharge_Chk
 * Return:        void
 * note: void
 *********************************/
void FullCharge_Chk(void)
{
    // FCC
    static uint16_t tfc_cnt = 0;
    static uint32_t rc_integral = 0;
    uint16_t twork;

    if (t_com0d < 100)
    {
        f_VCT = OFF;
    }

    // if(f_pi_mode)  // step into pimode , not dsg update .
	// {
    //     f_study_d = 0 ;
	// }
    


    // Not OVER_CHARGED_ALARMf_chg
    // if (f_chg) // C-FET = ON ?
    // {
    if (f_charge == ON && f_chg) // Charging current detection ?
    {
        if (f_fullchg == ON) // FULLY_CHARGED = ON ?
        {
            if (t_com0f >= t_com10) // RC >= FCC ?
            {
                FullCharge(); // Full Charge Processing
            }
        }
        else
        { // FULLY_CHARGED = OFF
          // MaxV >= Single cell CV-FCtaperV
          // & Full Charge Current less than ?
            // t_com3a_out = NUMBER_SERIES  ;
            if ((V_max >= (_ChargingVoltage/NUMBER_SERIES - D_Termination_Charge_Term_Voltage)) && (_AverageCurrent < Charge_Term))
            {
                // t_com15_test = _ChargingVoltage ;
                // if (!getSoftTimerStatus(SOFT_TIMER_FC_ID))
                // {
                //     StartSoftTimer(SOFT_TIMER_FC_ID, SINGLE_MODE, D_Termination_Fullcharge_judgement_time * 1000, FullCharge);
                // }
                tfc_cnt++; // Full Charge check count + 1
                rc_integral += I_abs;
                // Full charge determination time elapsed ?
                if (tfc_cnt >= D_Termination_Fullcharge_judgement_time * 4)
                {
                    // tfc_cnt = 0;  // Clear Full Charge check count
                    if (rc_integral / 4 / 3600 >= D_Termination_Charge_Term_Taper_Capacity)
                    {
                        tfc_cnt = 0;
                        rc_integral = 0;
                        FullCharge(); // Full Charge Processing
                    }
                    else
                    {
                        tfc_cnt = D_Termination_Fullcharge_judgement_time - 1;
                    }
                }
            }
            // else
            // {
            //     if (tfc_cnt != 0) // Full Charge check count = 0 ?
            //     {
            //         tfc_cnt-=Periodtime; // Full Charge check count - 1
            //     }
            //     rc_integral = 0;
            // }
        }
    }
    else
    {
        // Charging current undetected
        tfc_cnt = 0; // Clear Full Charge check count
        rc_integral = 0;
    }

   // }
}


void CellBalance_Chk(void)
{
   uint8_t i;
   uint8_t awork;
   static uint32_t balace_delay = 0;
   if (D_Balancing_Configuration_CB && (f_charge || (D_Balancing_Configuration_CBR && f_relax))) // Rest or Charging
   {
       if (V_max < D_Cell_Enable_voltage_upper_limit && V_min >= D_Cell_Enable_voltage_lower_limit) // Is voltage a cell balancing possible range ?
       {
           awork = 0;                      // Initialize work area
           if ((V_max - V_min) >= D_Cell_balancing_ON_voltage) // Is voltage "cell balancing On voltage" or more ?
           {
               for (i = 0; i < NUMBER_SERIES; i++) // Cell imbalance check loop
               {
                   // Is the voltage "cell balancing On voltage" or more ?
                   if ((afe_data.cell_vol_val[i] - V_min) >= D_Cell_balancing_ON_voltage)
                   {
                       awork |= acond_tbl[i]; // Set to cell balance list
                   }
               }
           }

           if (acb_w != 0) // Now controlling cell balance ?
           {
               for (i = 0; i < NUMBER_SERIES; i++) // imbalance check loop
               {
                   // Is it controlled cell ?
                   if ((acb_w & acond_tbl[i]) != 0)
                   {

                       lifetime_ram.cb_time_cell[i]+= Periodtime; // Cell balance time
                       // Is the voltage less than "Cell balance OFF voltage" ?
                       if ((afe_data.cell_vol_val[i] - V_min) < D_Cell_balancing_OFF_voltage)
                       {
                           // Clear it from cell balance list
                           acb_w ^= acond_tbl[i];
                       }
                   }
               }
               if (acb_w == 0 && awork == 0) // All cell stop cell balance ?
               {
                   f_cb = OFF;
                   acb_w = 0; // Clear the list
                    // balace_delay = 0; // Clear delay time
                    // printf("tuichubalancen!\n");
                   afe_dtdrv_vc_enable_ctrl(DTDRV_CVBLC_CB_VC1 | DTDRV_CVBLC_CB_VC2 | DTDRV_CVBLC_CB_VC3 | DTDRV_CVBLC_CB_VC4, DISABLE);
               }
           }

           acb_w |= awork; // Merge control and start list

           if ((acb_w != 0) )//&& (!f_cb)) // Is there cell balance control ?
           {
            //    balace_delay += Periodtime;
            //     if (balace_delay >= 30 * 1000) // Cell balancing delay time ?
            //     {
            //         printf("balancen!\n");
            //          balace_delay = 0; // Clear delay time
            //          //afe_cb_control(acb_w);
            //          afe_dtdrv_vc_enable_ctrl(DTDRV_CVBLC_CB_VC1, ENABLE);
                     
            //          f_cb = ON;
            //     }
             f_cb = ON;
               afe_dtdrv_vc_enable_ctrl(acb_w, ENABLE);

           }
       }
       else
       {
           f_cb = OFF;
           acb_w = 0;
       }
   }
   else
   {
       f_cb = OFF;
       acb_w = 0;
   }
   // a_com45[0] = acb_w;							// CellBalancing Status(Cell 1 - 4)
}

void Calc_ATTF(void)
{
    int num = 0;
    ATTF_SetChgFlag(f_charge);
    if (_AverageCurrent > 0)
    {
        ATTF_SetRC(t_com0f);
        ATTF_SetFCC(t_com10);
        ATTF_SetTEM(Ts_max); // set temperature
        ATTF_SetFCFlag(f_fullchg);

        _AverageTimeToFull = Calc_ATTF1(Current());
    }
    else
    {
        _AverageTimeToFull = 0xFFFF;
    }

    if (_AtRate > 0)
    {
        _AtRateTimeToFull = (long)(t_com10 - t_com0f) * 60 / ABS(_AtRate);
    }
    else
    {
        _AtRateTimeToFull = 0xFFFF;
    }
}

void Calc_ATTE(void)
{
    if (Current() < 0)
    {
        _RunTimeToEmpty = (long)t_com0f * 60 / ABS(Current());
    }
    else
    {
        _RunTimeToEmpty = 0xFFFF;
    }

    if (_AverageCurrent < 0)
    {
        _AverageTimeToEmpty = (long)t_com0f * 60 / ABS(_AverageCurrent);
    }
    else
    {
        _AverageTimeToEmpty = 0xFFFF;
    }

    //    if(_AverageTimeToEmpty <= t_com02)
    //    {
    //        f_rta_a = ON;
    //    }
    //    else
    //    {
    //        f_rta_a = OFF;
    //    }

    // if (_AtRate >= 0)
    // {
    //     _AtRateTimeToEmpty = 0xFFFF;
    // }
    // else
    // {
        _AtRateTimeToEmpty = (long)t_com0f * 60 / ABS(_AtRate);  
    // }

    if (_AtRate >= 0)
    {
        _AtRateOK = 0x0001;
    }

    if (_AtRate < 0 && (_AtRate + Current()) >= 0)
    {
        _AtRateOK = 0x0001;
    }

    if (_AtRate < 0 && (_AtRate + Current()) < 0)
    {
        if (((long)(t_com0f * 360) / ABS(_AtRate + Current())) != 0)
        {
            _AtRateOK = 0x0001;
        }
        else
        {
            _AtRateOK = 0x0000;
        }
    }
}


void afe_cb_control(uint8_t status)
{
    
    /* 控制vc1 */
    if(status & DTDRV_CVBLC_CB_VC1)
    {
        afe_dtdrv_vc_enable_ctrl(DTDRV_CVBLC_CB_VC1, ENABLE);
       // printf("enable cb vc1");
    }
   
    if(status & DTDRV_CVBLC_CB_VC2)
    {
        afe_dtdrv_vc_enable_ctrl(DTDRV_CVBLC_CB_VC2, ENABLE);
      // printf("enable cb vc2");
    }
 
    if(status & DTDRV_CVBLC_CB_VC3)
    {
        afe_dtdrv_vc_enable_ctrl(DTDRV_CVBLC_CB_VC3, ENABLE);
      //  printf("enable cb vc3");
    }
   
    /* 控制vc4 */
    if(status& DTDRV_CVBLC_CB_VC4)
    {
        afe_dtdrv_vc_enable_ctrl(DTDRV_CVBLC_CB_VC4, ENABLE);
       // printf("enable cb vc4");
    }
  
    #if(defined(CBM8581))
    /* 控制vc5 */
    if(status& DTDRV_CVBLC_CB_VC5)
    {
        afe_dtdrv_vc_enable_ctrl(DTDRV_CVBLC_CB_VC5, ENABLE);
        //printf("enable cb vc5");
    }
    
    #endif
}



void RSOC_HOLD(void)
{
    if (f_rsoc_hold)
    {
        if(!f_charge)
        {
            if(t_com0d>old_rsoc)
            {
                t_com0d = old_rsoc;
            }
            
        }
        old_rsoc = t_com0d;
    }
}

void pi_blance_enable(void)
{
    uint16_t awork;
    uint8_t i=0;
    for (i = 0; i < NUMBER_SERIES; i++) // Cell imbalance check loop
    {

        awork |= acond_tbl[i]; // Set to cell balance list
    }
    f_cb = ON;
    afe_dtdrv_vc_enable_ctrl(awork, ENABLE);
}

void pi_blance_disable(void)
{
    f_cb = OFF;
    afe_dtdrv_vc_enable_ctrl(DTDRV_CVBLC_CB_VC1 | DTDRV_CVBLC_CB_VC2 | DTDRV_CVBLC_CB_VC3 | DTDRV_CVBLC_CB_VC4, DISABLE);
}