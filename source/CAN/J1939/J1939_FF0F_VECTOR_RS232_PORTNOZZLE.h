//------------------------------------------------------------------------------
//  TITLE :          PGN FF0F Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF0F_H__
#define __PGN_FF0F_H__

#define PGN_FF0F 65295 // 0xFF0F in decimal
void J1939_FF0F_VECTOR_RS232_PORTNOZZLE(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF0F_H__
