// LockFree-test.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "lib\Library.h"
#include "LockFreeMemoryPool.h"
#include "LockFreeStack.h"





int main()
{
	
	////////////////////////////////////////////////////////////
	//Ű�Է¿� ���� ������ MemoryPool, Stack, Queue�� �׽�Ʈ.
	//Q�� �Է½� ����.
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
			wprintf (L"\nError �߸��Է��ϼ̽��ϴ�.\n");
		}
	}



    return 0;
}

