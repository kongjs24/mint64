#include "Types.h"
#include "Keyboard.h"

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
    kPrintStringWithDot(0, 12, "Keyboard Activate.");

    if (kActivateKeyboard() == TRUE) {
        kPrintString(75, 12, "PASS");
        kChangeKeyboardLED(TRUE, FALSE, FALSE);
    } else {
        kPrintString(75, 12, "FAIL");
        while (1);
    }

    while (1) {
        if (kIsOutputBufferFull() == TRUE) {
            bTemp = kGetKeyboardScanCode();

            if (kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags) == TRUE) {
                if (bFlags & KEY_FLAGS_DOWN) {
                    kPrintString(i++, 13, vcTemp);
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
    char *dots;

    for (i = 0; pcString[i] != 0; i++) {
        stringLength = i;
    }
    kPrintString(iX, iY, pcString);
    for (i = 0; i < maxWidth - stringLength - 6; i++) {
        dots[i] = '.';
    }
    dots[i + 1] = '\0';
    kPrintString(stringLength + 1, iY, dots);
    kPrintString(maxWidth - 6, iY, "[    ]");
}

void kPrintStringWithPass(int iX, int iY, const char *pcString) {
    DWORD maxWidth = 80;
    int i;
    int stringLength;
    char *dots;

    for (i = 0; pcString[i] != 0; i++) {
        stringLength = i;
    }
    kPrintString(iX, iY, pcString);
    for (i = 0; i < maxWidth - stringLength - 6; i++) {
        dots[i] = '.';
    }
    dots[i + 1] = '\0';
    kPrintString(stringLength + 1, iY, dots);
    kPrintString(maxWidth - 6, iY, "[PASS]");
}
