//------------------------------------------------------------------------------
//  TITLE :          PGN FF16 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF16_H__
#define __PGN_FF16_H__

#define PGN_FF16 65302 // 0xFF16 in decimal
void J1939_FF16_VECTOR_RS232_NFUFAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF16_H__
