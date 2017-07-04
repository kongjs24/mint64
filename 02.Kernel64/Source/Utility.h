//
// Created by devjin on 2017-07-04.
//

#ifndef MINT64_UTILITY_H
#define MINT64_UTILITY_H

#include "Types.h"

void kMemSet(void* pvDestination, BYTE bData, int iSize);
int kMemCpy(void* pvDestination, const void* pvSource, int iSize);
int kMemCmp(const void* pvDestination, const void* pvSource, int iSize);
#endif //MINT64_UTILITY_H
