//------------------------------------------------------------------------------
//  TITLE :          PGN FF13 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF13_H__
#define __PGN_FF13_H__

#define PGN_FF13 65299 // 0xFF13 in decimal
void J1939_FF13_VECTOR_RS232_PORTTRIMTAB(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF13_H__
