//------------------------------------------------------------------------------
//  TITLE :          PGN FF11 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF11_H__
#define __PGN_FF11_H__

#define PGN_FF11 65297 // 0xFF11 in decimal
void J1939_FF11_VECTOR_RS232_PORTBUCKET(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF11_H__
