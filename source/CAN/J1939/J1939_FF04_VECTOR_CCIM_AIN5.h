//------------------------------------------------------------------------------
//  TITLE :          PGN FF04 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF04_H__
#define __PGN_FF04_H__

#define PGN_FF04 65284 // 0xFF04 in decimal
void J1939_FF04_VECTOR_CCIM_AIN5(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF04_H__
