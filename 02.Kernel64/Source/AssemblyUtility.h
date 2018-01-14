#ifndef MINT64_ASSEMBLYUTILITY_H
#define MINT64_ASSEMBLYUTILITY_H

#include "Types.h"
BYTE kInPortByte(WORD wPort);
void kOutPortByte(WORD wPort, BYTE bData);
void kLoadGDTR(QWORD qwGDTRAddress);
void kLoadTR(WORD wTSSSegmentOffset);
void kLoadIDTR(QWORD qwIDTRAddress);

#endif