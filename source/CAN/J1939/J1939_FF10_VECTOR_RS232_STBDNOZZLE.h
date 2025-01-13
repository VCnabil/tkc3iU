//------------------------------------------------------------------------------
//  TITLE :          PGN FF10 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF10_H__
#define __PGN_FF10_H__

#define PGN_FF10 65296 // 0xFF10 in decimal
void J1939_FF10_VECTOR_RS232_STBDNOZZLE(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF10_H__
