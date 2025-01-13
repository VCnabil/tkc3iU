//------------------------------------------------------------------------------
//  TITLE :          PGN FF51 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF51_H__
#define __PGN_FF51_H__

#define PGN_FF51 65361 // 0xFF51 in decimal
void J1939_FF51_VECTOR_ALARM_ACKNOWLEDGE(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF51_H__
