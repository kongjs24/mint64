#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"

void kPrintString(int iX, int iY, const char *pcString);

void kPrintStringWithPass(int iX, int iY, const char *pcString);

void kPrintStringWithDot(int iX, int iY, const char *pcString);

void Main(void) {
    char vcTemp[2] = {0,};
    BYTE bFlags;
    BYTE bTemp;
    int i = 0;
    kPrintString(0, 10, "Switch To IA-32e Mode Success~!!");
    kPrintStringWithPass(0, 11, "IA-32e C Language Kernel Start.");
    kPrintStringWithDot(0, 12, "GDT Initialize And Switch For IA-32e Mode.");
    kInitializeGDTTableAndTSS();
    kLoadGDTR(GDTR_STARTADDRESS);
    kPrintString(75, 12, "PASS");

    kPrintStringWithDot(0, 13, "TSS Segment Load.");
    kLoadTR(GDT_TSSSEGMENT);
    kPrintString(75,13, "PASS");

    kPrintStringWithDot(0, 14, "IDT Initialize.");
    kInitializeIDTTables();
    kLoadIDTR(IDTR_STARTADDRESS);
    kPrintString(75, 14, "PASS");

    kPrintStringWithDot(0, 15, "Keyboard Activate.");
    if (kActivateKeyboard() == TRUE) {
        kPrintString(75, 15, "PASS");
        kChangeKeyboardLED(TRUE, FALSE, FALSE);
    } else {
        kPrintString(75, 15, "FAIL");
        while (1);
    }

    while (1) {
        if (kIsOutputBufferFull() == TRUE) {
            bTemp = kGetKeyboardScanCode();

            if (kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags) == TRUE) {
                if (bFlags & KEY_FLAGS_DOWN) {
                    kPrintString(i++, 16, vcTemp);
                }
            }
        }
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

void kPrintStringWithDot(int iX, int iY, const char *pcString) {
    DWORD maxWidth = 80;
    int i;
    int stringLength;
    char dots[80] = {0,};

    for (i = 0; pcString[i] != 0; i++) {
        stringLength = i;
    }
    kPrintString(iX, iY, pcString);
    for (i = 0; i < maxWidth - stringLength - 7 ; i++) {
        dots[i] = '.';
    }
    kPrintString(stringLength + 1, iY, dots);
    kPrintString(maxWidth - 6, iY, "[    ]");
}

void kPrintStringWithPass(int iX, int iY, const char *pcString) {
    DWORD maxWidth = 80;
    int i;
    int stringLength;
    char dots[80] = {0,};

    for (i = 0; pcString[i] != 0; i++) {
        stringLength = i;
    }
    kPrintString(iX, iY, pcString);
    for (i = 0; i < maxWidth - stringLength - 7; i++) {
        dots[i] = '.';
    }
    kPrintString(stringLength + 1, iY, dots);
    kPrintString(maxWidth - 6, iY, "[PASS]");
}
