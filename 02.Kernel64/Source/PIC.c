#include "PIC.h"

void kInitializePIC(void) {
	//마스터 인터럽트 컨트롤러에 ICW1,2,3,4 전송
	kOutPortByte(PIC_MASTER_PORT1, 0x11);
	kOutPortByte(PIC_MASTER_PORT2, PIC_IRQSTARTVECTOR); //인터럽트 벡터 설정
	kOutPortByte(PIC_MASTER_PORT2, 0x04);
	kOutPortByte(PIC_MASTER_PORT2, 0x01);

	//슬레이브 인터럽트 컨트롤러에 ICW1,2,3,4전송
	kOutPortByte(PIC_SLAVE_PORT1, 0x11);
	kOutPortByte(PIC_SLAVE_PORT2, PIC_IRQSTARTVECTOR + 8); //인터럽트 벡터
	kOutPortByte(PIC_SLAVE_PORT2, 0x02);
	kOutPortByte(PIC_SLAVE_PORT2, 0x01);
}

void kMaskPICInterrupt(WORD wIRQBitmask) {
	kOutPortByte(PIC_MASTER_PORT2, (BYTE)wIRQBitmask);
	kOutPortByte(PIC_SLAVE_PORT2, (BYTE)wIRQBitmask >> 8);
}

void kSendEOIToPIC(int iIRQNumber) {
	kOutPortByte(PIC_MASTER_PORT1, 0x20);

	if(iIRQNumber >= 8)
		kOutPortByte(PIC_SLAVE_PORT1, 0x20);
}
