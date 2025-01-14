//------------------------------------------------------------------------------
//  TITLE :          PGN FF50 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF50_H__
#define __PGN_FF50_H__

#define PGN_FF50 65360 // 0xFF50 in decimal
void J1939_FF50_VECTOR_ALARM_ACKNOWLEDGE(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF50_H__
