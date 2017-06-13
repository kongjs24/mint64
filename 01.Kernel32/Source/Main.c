#include "Types.h"
#include "Page.h"
#include "ModeSwitch.h"

void kPrintMessageAndStatus(int ix, int iy, const char *success, const char *failure, BOOL status);

void kPrintString(int iX, int iY, const char *pcString);

BOOL kInitializeKernel64Area(void);

BOOL kIsMemoryEnough(void);

void kCopyKernel64ImageTo2Mbyte(void);

void Main(void) {
    DWORD i;
    DWORD dwEAX, dwEBX, dwECX, dwEDX;
    char vcVendorString[13] = {0,};

    kPrintMessageAndStatus(0, 3,
                           "Protected Mode C Language Kernel Start",
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
    kPrintMessageAndStatus(0, 6,
                           "IA-32e Page Tables Initialize.",
                           "",
                           kInitializePageTables()
    );
    kReadCPUID(0x00, &dwEAX, &dwEBX, &dwECX, &dwEDX);
    *(DWORD *) vcVendorString = dwEBX;
    *((DWORD *) vcVendorString + 1) = dwEDX;
    *((DWORD *) vcVendorString + 2) = dwECX;
    kPrintMessageAndStatus(0, 7,
                           "Processor Vendor String.",
                           "",
                           TRUE
    );
    kPrintString(68,7,vcVendorString);

    kReadCPUID( 0x80000001, &dwEAX, &dwEBX, &dwECX, &dwEDX );
    kPrintMessageAndStatus(0, 8,
                           "64bit Mode Support Check.",
                           "This processor does not support 64bit mode~!!",
                           (dwEDX & ( 1 << 29 )) >> 29
    );
    kCopyKernel64ImageTo2Mbyte();
    kPrintMessageAndStatus(0,9,
                           "Copy IA-32e Kernel To 2M Address",
                           "",
                           TRUE
    );
    kPrintString( 0, 9, "Switch To IA-32e Mode" );
    kSwitchAndExecute64bitKernel();

    while (1);
}

void kPrintMessageAndStatus(int iX,
                            int iY,
                            const char *success,
                            const char *failure,
                            BOOL status) {
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
    kPrintString(successSize + 1, iY, dots);
    if (status) {
        kPrintString(maxWidth - 6, iY, "[PASS]");
    } else {
        kPrintString(maxWidth - 6, iY, "[FAIL]");
        kPrintString(0, iY + 1, failure);
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
    DWORD *pdwCurrentAddress;

    pdwCurrentAddress = (DWORD *) 0x100000;

    while ((DWORD) pdwCurrentAddress < 0x4000000) {
        *pdwCurrentAddress = 0x12345678;
        if (*pdwCurrentAddress != 0x12345678) {
            return FALSE;
        }
        pdwCurrentAddress += (0x100000 / 4);
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

void kCopyKernel64ImageTo2Mbyte(void) {
    WORD wKernel32SectorCount, wTotalKernelSectorCount;
    DWORD* pdwSourceAddress,* pdwDestinationAddress;
    int i;

    wTotalKernelSectorCount = *((WORD*) 0x7C05);
    wKernel32SectorCount = *((WORD*) 0x7C07);

    pdwSourceAddress = (DWORD*) (0x10000 + (wKernel32SectorCount * 512));
    pdwDestinationAddress = (DWORD*) 0x200000;

    for (i = 0; i < 512 * (wTotalKernelSectorCount - wKernel32SectorCount) / 4; i++) {
        *pdwDestinationAddress = *pdwSourceAddress;
        pdwDestinationAddress++;
        pdwSourceAddress++;
    }
}
