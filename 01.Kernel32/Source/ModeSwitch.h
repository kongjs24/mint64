#ifndef MINT64_MODESWITCH_H_H
#define MINT64_MODESWITCH_H_H

#include "Types.h"

void kReadCPUID(DWORD dwEAX, DWORD* pdwEAX, DWORD* pdwEBX, DWORD* pdwECX, DWORD* pdwEDX);
void kSwitchAndExecute64bitKernel( void );

#endif //MINT64_MODESWITCH_H_H
