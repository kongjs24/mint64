#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Types.h"
#pragma pack(push, 1)
typedef struct kQueueManagerStruct {
	int iDataSize;//큐를 구성하는 데이터 하나의 크기
	int iMaxDataCount;//큐에 삽입할 수 있는 최대 개수

	void* pvQueueArray;//큐에서 데이터를 저장하는 용도로 사용할 버퍼
	int iPutIndex;//데이터를 삽입할 때 사용하는 인덱스
	int iGetIndex;//데이터를 제거할 때 사용하는 인덱스

	BOOL bLastOperationPut; //큐의 마지막 명령이 무엇인지 저장 삽입 동작시 TRUE
} QUEUE;
#pragma pack(pop)

void kInitializeQueue( QUEUE* pstQueue, void* pvQueueBuffer, int iMaxDataCount, int iDataSize);
BOOL kIsQueueFull( const QUEUE* pstQueue);
BOOL kIsQueueEmpty( const QUEUE* pstQueue);
BOOL kPutQueue(QUEUE* pstQueue, const void * pvData);
BOOL kGetQueue(QUEUE* pstQueue, void* pvData);
#endif
