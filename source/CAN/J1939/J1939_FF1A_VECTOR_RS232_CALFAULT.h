//------------------------------------------------------------------------------
//  TITLE :          PGN FF1A Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF1A_H__
#define __PGN_FF1A_H__

#define PGN_FF1A 65306 // 0xFF1A in decimal
void J1939_FF1A_VECTOR_RS232_CALFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF1A_H__
