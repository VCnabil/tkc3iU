//------------------------------------------------------------------------------
//  TITLE :          PGN FF05 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF05_H__
#define __PGN_FF05_H__

#define PGN_FF05 65285 // 0xFF05 in decimal
void J1939_FF05_VECTOR_CCIM_AIN6(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF05_H__
