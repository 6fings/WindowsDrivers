/********************************************************************************
*																				*
* File Name:																	*
* 	6fings.h																	*
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
//	P R A G M A S.
/////////////////////////////////////////////////////////////////////
#pragma once


/////////////////////////////////////////////////////////////////////
//	T Y P E D E F S.
/////////////////////////////////////////////////////////////////////
typedef unsigned int UINT;
typedef char* PCHAR;


/////////////////////////////////////////////////////////////////////
//	M A C R O S.
/////////////////////////////////////////////////////////////////////
#define __USE_DIRECT__ 
//#define __USE_BUFFERED__

#ifdef __USE_DIRECT__
#define IO_TYPE DO_DIRECT_IO
#define USE_WRITE_FUNCTION  DispatchWriteDirectIO
#define USE_READ_FUNCTION   DispatchReadDirectIO
#endif

#ifdef __USE_BUFFERED__
#define IO_TYPE DO_BUFFERED_IO
#define USE_WRITE_FUNCTION  DispatchWriteBufferedIO
#define USE_READ_FUNCTION   DispatchReadBufferedIO
#endif

#ifndef IO_TYPE
#define IO_TYPE 0
#define USE_WRITE_FUNCTION  DispatchWriteNeither
#define USE_READ_FUNCTION   DispatchReadNeither
#endif


/////////////////////////////////////////////////////////////////////
//	F U N C T I O N  P R O T O T Y P E S.
/////////////////////////////////////////////////////////////////////


//***********************************************************************************
//	Function:
//		DispatchCreate
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Create dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS
DispatchCreate(
	IN  PDEVICE_OBJECT pDeviceObject, 
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchCleanup
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Cleanup dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS
DispatchCleanup(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchClose
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Close dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS
DispatchClose(
	IN  PDEVICE_OBJECT pDeviceObject, 
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchIoControl
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		IO Control dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		NTSTATUS
//		if function is successful then the return value is STATUS_SUCCESS.
//		if function fails then the return value is error code.
//
//***********************************************************************************
NTSTATUS
DispatchIoControl(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchWriteDirectIO
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Write Direct I/O dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS
DispatchWriteDirectIO(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchWriteBufferedIO
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Write buffered I/O dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS
DispatchWriteBufferedIO(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchWriteNeither
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Write neither direct nor buffered I/O dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS
DispatchWriteNeither(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchReadDirectIO
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Read Direct I/O dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS 
DispatchReadDirectIO(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchReadBufferedIO
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Read Buffered I/O dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS
DispatchReadBufferedIO(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchReadNeither
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Read Neither direct nor buffered I/O dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS 
DispatchReadNeither(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		DispatchUnSupportedFunction
//
//	Parameters:
//		[IN]  DEVICE_OBJECT* pDeviceObject
//		Our device object.
//	   
//		[IN/OUT]  IRP* pIrp
//		The IO request packet to process.
//
//	Routine Description:
//		Generic dispatch routine. All the requests are completed
//		successfuly.
//
//	Return Value:
//		STATUS_SUCCESS.
//
//***********************************************************************************
NTSTATUS 
DispatchUnSupportedFunction(
	IN  PDEVICE_OBJECT pDeviceObject,
	IN OUT  PIRP pIrp
);


//***********************************************************************************
//	Function:
//		IsStringTerminated
//
//	Parameters:
//		[IN]  PCHAR pString
//		String to analyse.
//	   
//		[IN]  UINT uiLength
//		Length of the string.
// 
//		[OUT]	UINT* pdwStringLength
//		Length of string read by this function including NULL character.
// 
//	Routine Description:
//		Routine to check whether a given string is NULL terminated or not.
//
//	Return Value:
//		BOOLEAN.
//		If the function succeeds, the return value is TRUE.
//		If the function fails, the return value is FALSE.
//
//***********************************************************************************
BOOLEAN 
IsStringTerminated(
	IN  PCHAR pString, 
	IN  UINT uiLength, 
	OUT  UINT* pdwStringLength
);


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
);


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
);