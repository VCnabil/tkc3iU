//------------------------------------------------------------------------------
//  TITLE :          PGN FF18 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF18_H__
#define __PGN_FF18_H__

#define PGN_FF18 65304 // 0xFF18 in decimal
void J1939_FF18_VECTOR_RS232_STA2FAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF18_H__
