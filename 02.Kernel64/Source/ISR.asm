[BIT 64]

SECTION .text

extern kCommonExceptionHandler, kCommonInterruptHandler, kKeyboardHandler

;ISR = interrupt service routine
;예외처리
global kISRDivideError, kISRDebug, kISRNMI, kISRBreakPoint, KISROverflow
global kISRBoundRangeExceeded, kISRInvalidOpcode, kISRDeviceNotAvailable, kISRDoubleFault
global kISRCoprocessorSegmentOverrun, kISRInvalidTSS, kISRSegmentNotPresent
global kISRStackSegmentFault, kISRGeneralProtection, kISRPageFault, kISR15
global kIOSRFPUError, kISRAlignmentCheck, kISRMachineCheck, kISRSImDError, kISRETCException

;인터럽트 처리
global kISRTimer, kISRKeyboard, kISRSlavePIC, kISRSerial2,kISRSerial1, kISRParallel2
global kISRFloppy, kISRParallel1, kISRRTC, kISRReseved, kISRNotUsed1, kISRNotUsed2
global kISRMouse, kISRCoprocessor, kISRHDD1, kISRHDD2, kISRETCInterrupt

%macro KSAVECONTEXT 0
    push rbp
    mov rbp, rsp
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov ax, ds
    push rax
    mov ax, es
    push rax
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
%endmacro

%macro KLOADCONTEXT 0
    pop gs
    pop fs
    pop rax
    mov es, ax
    pop rax
    mov ds, ax

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop rbp
%endmacro

kISRDivideError:
    KSAVECONTEXT

    mov rdi, 0
    call kCommonExceptionHandler

    KLOADCONTEXT
    iretq

kISRDebug:
    mov rdi, 1
    call kCommonExceptionHandler

    KLOADCONTEXT
    iretq

kKISRNMI:
    KSAVECONTEXT

    mov rdi, 2
    call kCommonExceptionHandler

    
