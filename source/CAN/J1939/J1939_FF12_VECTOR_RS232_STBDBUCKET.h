//------------------------------------------------------------------------------
//  TITLE :          PGN FF12 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF12_H__
#define __PGN_FF12_H__

#define PGN_FF12 65298 // 0xFF12 in decimal
void J1939_FF12_VECTOR_RS232_STBDBUCKET(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF12_H__
