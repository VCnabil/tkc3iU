//------------------------------------------------------------------------------
//  TITLE :          PGN FF15 Decode SIG_FAULT
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF15_H__
#define __PGN_FF15_H__

#define PGN_FF15 65301 // 0xFF15 in decimal
void J1939_FF15_VECTOR_RS232_SIGFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF15_H__
