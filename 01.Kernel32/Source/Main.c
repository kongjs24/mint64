#include "Types.h"

void kPrintMessageAndStatus(int ix, int iy, const char *success, const char *failure, BOOL status);

void kPrintString(int iX, int iY, const char *pcString);

BOOL kInitializeKernel64Area(void);

BOOL kIsMemoryEnough(void);

void Main(void) {
    DWORD i;

    kPrintMessageAndStatus(0, 3,
                           "C Language Kernel Start",
                           "",
                           TRUE
    );
    kPrintMessageAndStatus(0, 4,
                           "Minimum Memory Size Check.",
                           "Not Enough Memory. MINT64 OS Requires Over 64MB Memory.",
                           kIsMemoryEnough()
    );
    kPrintMessageAndStatus(0, 5,
                           "IA-32e Kernel Area Initialize",
                           "Kernel Area Initialization Fail~!!",
                           kInitializeKernel64Area()
    );

    while (1);
}

void kPrintMessageAndStatus(int iX, int iY, const char *success, const char *failure, BOOL status) {
    DWORD maxWidth = 80;
    int i;
    int successSize;
    char *dots;

    for (i = 0; success[i] != 0; i++) {
        successSize = i;
    }

    kPrintString(iX, iY, success);
    for (i = 0; i < maxWidth - successSize - 6; i++) {
        dots[i] = '.';
    }
    dots[i + 1] = '\0';
    kPrintString(successSize +1, iY, dots);
    if (status == TRUE) {
        kPrintString(maxWidth - 6, iY, "[PASS]");
    } else {
        kPrintString(maxWidth - 6, iY, "[FAIL]");
        kPrintString(0, iY+1, failure);
        while (1);
    }

}

void kPrintString(int iX, int iY, const char *pcString) {
    CHARACTER *pstScreen = (CHARACTER *) 0xB8000;
    int i;

    pstScreen += (iY * 80) + iX;
    for (i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharactor = pcString[i];
    }

}

BOOL kIsMemoryEnough(void) {
    DWORD* pdwCurrentAddress;

    pdwCurrentAddress = (DWORD*) 0x100000;

    while((DWORD) pdwCurrentAddress < 0x4000000) {
        *pdwCurrentAddress = 0x12345678;
        if (*pdwCurrentAddress != 0x12345678) {
            return FALSE;
        }
        pdwCurrentAddress +=(0x100000 / 4);
    }
    return TRUE;
}

BOOL kInitializeKernel64Area(void) {
    DWORD *pdwCurrentAddress;

    pdwCurrentAddress = (DWORD *) 0x100000;

    while ((DWORD) pdwCurrentAddress < 0x600000) {
        *pdwCurrentAddress = 0x00;

        if (*pdwCurrentAddress != 0) {
            return FALSE;
        }

        pdwCurrentAddress++;
    }

    return TRUE;
}

