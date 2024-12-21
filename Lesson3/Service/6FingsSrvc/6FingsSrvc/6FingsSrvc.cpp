/********************************************************************************
*																				*
* File Name:																	*
* 	6FingsSrvc.c																*
*																				*
* Abstract:																		*
* 	This file is the main file to create, start and stop service.				*
* 	Service loads/unloads the driver.											*
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
#include <windows.h>
#include <tchar.h>
#include <stdio.h>


/////////////////////////////////////////////////////////////////////
//	F U N C T I O N  D E F I N I T I O N S.
/////////////////////////////////////////////////////////////////////
int main()
{
	SC_HANDLE hSCManager;
	SC_HANDLE hService;
	SERVICE_STATUS ss;

	hSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_CREATE_SERVICE
	);

	printf("Load Driver\n");

	if (hSCManager)
	{
		printf("Create Service\n");

		hService = CreateService(
			hSCManager,
			_T("6Fings"),
			_T("6Fings Service"),
			SERVICE_START | DELETE | SERVICE_STOP,
			SERVICE_KERNEL_DRIVER,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_IGNORE,
			_T("C:\\Windows\\System32\\drivers\\6Fings.sys"),
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		);

		if (!hService)
		{
			hService = OpenService(
				hSCManager,
				_T("6Fings"),
				SERVICE_START | DELETE | SERVICE_STOP
			);
		}

		if (hService)
		{
			printf("Start Service\n");

			StartService(
				hService,
				0,
				NULL
			);

			printf("Press Enter to Stop Service/Driver");

			getchar();

			ControlService(
				hService,
				SERVICE_CONTROL_STOP,
				&ss
			);

			CloseServiceHandle(hService);

			DeleteService(hService);
		}
		CloseServiceHandle(hSCManager);
	}
	return 0;
}