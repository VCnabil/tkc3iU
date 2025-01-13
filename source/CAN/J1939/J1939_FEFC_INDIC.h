//------------------------------------------------------------------------------
//  TITLE :          PGN FEE5 Decode
//  DESCRIPTION :    CAN Decode
//  AUTHOR :         Nabil Lamriben 1/13/2025
//------------------------------------------------------------------------------
#ifndef __PGN_FEFC_INDIC_H__
#define __PGN_FEFC_INDIC_H__

#define PGN_FEFC_INDIC 65276 // 0xFEFC in decimal
void J1939_FEFC_INDIC(CAN_PORTS_T canPort, CAN_MSG_T* pMsg);

#endif // #ifndef __PGN_FEFC_INDIC_H__