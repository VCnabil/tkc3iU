//------------------------------------------------------------------------------
//  TITLE :          PGN FF02 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF02_H__
#define __PGN_FF02_H__

#define PGN_FF02 65282 // 0xFF02 in decimal
void J1939_FF02_VECTOR_CCIM_AIN3(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF02_H__
