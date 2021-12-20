#pragma once
#include <stdio.h>
#include <windows.h>

bool bIntercept = false;

int (WINAPI* precv)(SOCKET socket, char* buffer, int length, int flags) = NULL;


int WINAPI DetourRecv(SOCKET socket, char* buffer, int length, int flags)
{
	int ret = precv(socket, buffer, length, flags);
	if (bIntercept)
	{
		printf("\n[+ packet]");
		for (int i = 0; i < length; i++)
		{
			printf("%X ", buffer[i]);
		}
	}
	return ret;
}