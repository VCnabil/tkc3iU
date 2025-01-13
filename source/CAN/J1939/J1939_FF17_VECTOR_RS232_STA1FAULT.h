//------------------------------------------------------------------------------
//  TITLE :          PGN FF17 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF17_H__
#define __PGN_FF17_H__

#define PGN_FF17 65303 // 0xFF17 in decimal
void J1939_FF17_VECTOR_RS232_STA1FAULT(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF17_H__
