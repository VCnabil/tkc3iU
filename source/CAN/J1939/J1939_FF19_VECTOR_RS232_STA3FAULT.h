//------------------------------------------------------------------------------
//  TITLE :          PGN FF19 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF19_H__
#define __PGN_FF19_H__

#define PGN_FF19 65305 // 0xFF19 in decimal
void J1939_FF19_VECTOR_RS232_STA3FAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF19_H__
