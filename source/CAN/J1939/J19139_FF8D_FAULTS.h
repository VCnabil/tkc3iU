//------------------------------------------------------------------------------
//  TITLE :          PGN FF8D Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FF8D_FAULTS_H__
#define __PGN_FF8D_FAULTS_H__

#define PGN_FF8D_FAULTS 65421 // 0xFF8D in decimal

 
void J1939_FF8D_FAULTS(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FF8D_FAULTS_H__