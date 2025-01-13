//------------------------------------------------------------------------------
//  TITLE :          PGN FF14 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF14_H__
#define __PGN_FF14_H__

#define PGN_FF14 65300 // 0xFF14 in decimal
void J1939_FF14_VECTOR_RS232_STBDTRIMTAB(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF14_H__
