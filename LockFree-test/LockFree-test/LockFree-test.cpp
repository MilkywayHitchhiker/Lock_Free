// LockFree-test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "lib\Library.h"
#include "LockFreeMemoryPool.h"
#include "LockFreeStack.h"





int main()
{
	
	////////////////////////////////////////////////////////////
	//키입력에 따라서 락프리 MemoryPool, Stack, Queue를 테스트.
	//Q를 입력시 종료.
	////////////////////////////////////////////////////////////
	int Key = 0;
	
	
	while ( 1 )
	{
		Key = getwchar ();
		switch ( Key )
		{
		case 1:
			break;
		case 'q':
			break;
		default :
			wprintf (L"\nError 잘못입력하셨습니다.\n");
		}
	}



    return 0;
}

