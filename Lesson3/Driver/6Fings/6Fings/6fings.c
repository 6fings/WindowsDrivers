/********************************************************************************
*																				* 
* File Name:																	*
* 	6fings.c																	*
*																				*
* Abstract:																		*
* 	This file is the main file for the driver.									*
* 	It implements the driver load/unload routines.								*
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
#include <wdm.h>
#include "6fings.h"


/////////////////////////////////////////////////////////////////////
//	P R A G M A S.
/////////////////////////////////////////////////////////////////////


//
//	These compiler directives tell the Operating System how to load the
//	driver into memory. The "INIT" section is discardable as we only
//	need the DriverEntry upon initialization, then it can be discarded.
//	"PAGE" directive tells that the code can be paged out to disk when not in use, saving non-paged memory.
//  This directive places the Unload function in the PAGE section of the driver's memory.
// 
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, DriverUnload)


/////////////////////////////////////////////////////////////////////
//	F U N C T I O N  D E F I N I T I O N S.
/////////////////////////////////////////////////////////////////////


//*******************************************************************
//
//	Function:
//		DriverEntry.
//
//	Parameters:
//		[IN] PDRIVER_OBJECT pDriverObject.
//		Driver object.
//
//		[IN] PUNICODE_STRING pusRegistryPath.
//		Registry path which stores the driver configurations.
//
//	Description:
//		This function is the initialization routine of the driver.
//
//	Returns:
//		NTSTATUS.
//		If the function succeeds the return value is STATUS_SUCCESS.
//		Else the return value is some error status.
//
//*******************************************************************
NTSTATUS
DriverEntry(
	IN  PDRIVER_OBJECT pDriverObject,
	IN  PUNICODE_STRING pusRegistryPath
)
{
	UNREFERENCED_PARAMETER(pusRegistryPath);

	NTSTATUS NtStatus = STATUS_SUCCESS;
	UINT uiIndex = 0;
	PDEVICE_OBJECT pDeviceObject;
	UNICODE_STRING usDriverName, usDosDeviceName;

	DbgPrint("DriverEntry Called! \r\n");

	RtlInitUnicodeString(
		&usDriverName,
		L"\\Device\\6Fings"
	);

	RtlInitUnicodeString(
		&usDosDeviceName,
		L"\\DosDevices\\6FingsUsr"
	);

	NtStatus = IoCreateDevice(
		pDriverObject,
		0,
		&usDriverName,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		FALSE,
		&pDeviceObject
	);

	if (STATUS_SUCCESS == NtStatus)
	{
		//
		//	The "MajorFunction" is a list of function pointers for entry points into the driver.
		// 
		for (uiIndex = 0; uiIndex < IRP_MJ_MAXIMUM_FUNCTION; uiIndex++)
			pDriverObject->MajorFunction[uiIndex] = DispatchUnSupportedFunction;

		pDriverObject->MajorFunction[IRP_MJ_CLEANUP] = DispatchCleanup;
		pDriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
		pDriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
		pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchIoControl;
		pDriverObject->MajorFunction[IRP_MJ_READ] = USE_READ_FUNCTION;
		pDriverObject->MajorFunction[IRP_MJ_WRITE] = USE_WRITE_FUNCTION;

		//
		//	Required to unload the driver dynamically. 
		//	If this function is missing the driver cannot be dynamically unloaded.
		// 
		pDriverObject->DriverUnload = DriverUnload;


		//
		//	Setting the flags on the device driver object determine what type of I/O
		//	we wish to use.
		// 
		// 
		//	Direct I/O - MdlAddress describes the Virtual Address list. This is then
		//				 used to lock the pages in memory.
		// 
		//				 PROS: Fast, Pages are not copied.
		//				 CONS: Uses resources, needs to lock pages into memory.
		// 
		// 
		//	Buffered I/O - SystemBuffer is then used by the driver to access the data. The I/O
		//				   manager will copy the data given by the user mode into this buffer
		//				   on behalf of the driver.
		// 
		//				   CONS: Slower operation (Use on smaller data sets)
		//						 Uses resources, allocates Non-paged memory
		//						 Large allocations may not work since it would
		//						 require allocating large sequential non-paged memory.
		//				   PROS: Easier to use, driver simply accesses the buffer
		//						 Usermode buffer is not locked in memory
		// 
		// 
		//	Neither Buffered 
		//	nor Direct - This is when you simply read the buffer directly using the user-mode address.
		//				 Simply omit DO_DIRECT_IO and DO_BUFFERED_IO to perform this action.
		// 
		//				 PROS: No copying or locking pages occurs.
		//				 CONS: You *MUST* be in the context of the user-mode thread that made the request.
		//					   being in another process space, the page tables would not point to
		//					   the same location.
		//					   You have to perform some checking and probeing in order to verify
		//					   when you can read/write from the pages.
		//					   You cannot access a user mode address unless it's locked into memory
		//					   at >= DPC level.
		//					   The usermode process could also change the access rights of the
		//					   buffer while the driver is trying to read it!
		// 
		// 
		//	If your driver services lower level drivers you will need to set this field to the same type of
		//	I/O.
		// 
		//	The flags for Read/Write is:
		//	DO_BUFFERED_IO, DO_DIRECT_IO, Specify neither flag for "Neither".
		// 
		pDeviceObject->Flags |= IO_TYPE;

		//
		//	We are not required to clear this flag in the DriverEntry as the I/O Manager will
		//	clear it for us, but we will anyway. Creating a device in any other location we
		//	would need to clear it.
		//
		pDeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);

		//		
		//	Create a Symbolic Link to the device. 6FingsUsr -> \Device\6Fings
		//
		IoCreateSymbolicLink(
			&usDosDeviceName,
			&usDriverName
		);
	}

	return NtStatus;
}


//*******************************************************************
//
//	Function:
//		DriverUnload.
//
//	Parameters:
//		[IN] PDRIVER_OBJECT pDriverObject.
//		pDriverObject for unload operation.
//
//	Description:
//		This function is the unload routine of the driver.
//
//	Returns:
//		NTSTATUS.
//		If the function succeeds the return value is STATUS_SUCCESS.
//		Else the return value is some error status.
//
//*******************************************************************
VOID
DriverUnload(
	IN  PDRIVER_OBJECT pDriverObject
)
{
	UNICODE_STRING usDosDeviceName;

	DbgPrint("DriverUnload Called! \r\n");

	RtlInitUnicodeString(
		&usDosDeviceName,
		L"\\DosDevices\\6FingsUsr"
	);

	IoDeleteSymbolicLink(&usDosDeviceName);
	IoDeleteDevice(pDriverObject->DeviceObject);
}