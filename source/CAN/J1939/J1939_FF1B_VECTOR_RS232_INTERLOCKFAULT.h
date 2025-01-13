//------------------------------------------------------------------------------
//  TITLE :          PGN FF1B Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF1B_H__
#define __PGN_FF1B_H__

#define PGN_FF1B 65307 // 0xFF1B in decimal
void J1939_FF1B_VECTOR_RS232_INTERLOCKFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF1B_H__
