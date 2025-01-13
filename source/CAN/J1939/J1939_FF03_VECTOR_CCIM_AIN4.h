//------------------------------------------------------------------------------
//  TITLE :          PGN FF03 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF03_H__
#define __PGN_FF03_H__

#define PGN_FF03 65283 // 0xFF03 in decimal
void J1939_FF03_VECTOR_CCIM_AIN4(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF03_H__
