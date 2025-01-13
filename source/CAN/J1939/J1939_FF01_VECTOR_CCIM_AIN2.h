//------------------------------------------------------------------------------
//  TITLE :          PGN FF01 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF01_H__
#define __PGN_FF01_H__

#define PGN_FF01 65281 // 0xFF01 in decimal
void J1939_FF01_VECTOR_CCIM_AIN2(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF01_H__
