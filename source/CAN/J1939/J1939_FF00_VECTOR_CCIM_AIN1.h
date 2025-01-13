//------------------------------------------------------------------------------
//  TITLE :          PGN FF00 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF00_H__
#define __PGN_FF00_H__

#define PGN_FF00 65280 // 0xFF00 in decimal
void J1939_FF00_VECTOR_CCIM_AIN1(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF00_H__
