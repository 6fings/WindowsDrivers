/********************************************************************************
*																				*
* File Name:																	*
* 	Msg6Fings.c																	*
*																				*
* Abstract:																		*
* 	This file is the main file to communicate with driver						*
*																				*
* Revision History:																*
* 	Date:	13 December 2024													*
* 	Author: Arpit Mathur														*
* 	Desc:	Created																*
*																				*
********************************************************************************/


/////////////////////////////////////////////////////////////////////
//	H E A D E R S.
/////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>


/////////////////////////////////////////////////////////////////////
//	F U N C T I O N  D E F I N I T I O N S.
/////////////////////////////////////////////////////////////////////
int _cdecl main(void)
{
	HANDLE hFile;
	DWORD dwReturn;
	char szTemp[256] = { 0 };
	BOOL bRet;

	hFile = CreateFile(
				_T("\\\\.\\6FingsUsr"),
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				0,
				NULL
			);

	if (hFile)
	{
		WriteFile(
			hFile,
			"Hello from user mode!",
			sizeof("Hello from user mode!"),
			&dwReturn,
			NULL
		);

		bRet = ReadFile(
			hFile,
			&szTemp,
			256,
			&dwReturn,
			NULL
		);

		if (!bRet)
			printf("ReadFile Failed!");
		else
			printf(szTemp);

		CloseHandle(hFile);

		getchar();
	}

	return 0;
}