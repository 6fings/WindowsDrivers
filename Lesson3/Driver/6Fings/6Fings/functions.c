/********************************************************************************
*																				*
* File Name:																	*
* 	functions.c																	*
*																				*
* Abstract:																		*
* 	This file contains definitions of all the dispatch routines.				*
* 	It also contains definitions of generic functions.							*
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
//	These are compiler directive which specifies 
//  whether the code of the function can be paged out of memory or not.
// 
#pragma alloc_text(PAGE, DispatchCreate)
#pragma alloc_text(PAGE, DispatchCleanup) 
#pragma alloc_text(PAGE, DispatchClose) 
#pragma alloc_text(PAGE, DispatchIoControl)
#pragma alloc_text(PAGE, DispatchWriteDirectIO)
#pragma alloc_text(PAGE, DispatchWriteBufferedIO)
#pragma alloc_text(PAGE, DispatchWriteNeither)
#pragma alloc_text(PAGE, DispatchReadDirectIO)
#pragma alloc_text(PAGE, DispatchReadBufferedIO)
#pragma alloc_text(PAGE, DispatchReadNeither)
#pragma alloc_text(PAGE, DispatchUnSupportedFunction)
#pragma alloc_text(PAGE, IsStringTerminated)


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
    )
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    UNREFERENCED_PARAMETER(pIrp);
    NTSTATUS NtStatus = STATUS_SUCCESS;
    DbgPrint("DispatchCreate Called \r\n");

    return NtStatus;
}


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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    UNREFERENCED_PARAMETER(pIrp);
    NTSTATUS NtStatus = STATUS_SUCCESS;
    DbgPrint("DispatchCleanup Called \r\n");

    return NtStatus;
}


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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    UNREFERENCED_PARAMETER(pIrp);
    NTSTATUS NtStatus = STATUS_SUCCESS;
    DbgPrint("DispatchClose Called \r\n");

    return NtStatus;
}


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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    UNREFERENCED_PARAMETER(pIrp);
    NTSTATUS NtStatus = STATUS_SUCCESS;
    DbgPrint("DispatchIoControl Called \r\n");

    return NtStatus;
}


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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    NTSTATUS NtStatus = STATUS_UNSUCCESSFUL;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pWriteDataBuffer;
    UINT dwDataWritten = 0;

    DbgPrint("DispatchWriteDirectIO Called \r\n");

    pIoStackIrp = IoGetCurrentIrpStackLocation(pIrp);

    if (pIoStackIrp && pIrp->MdlAddress)
    {
        pWriteDataBuffer = MmGetSystemAddressForMdlSafe(pIrp->MdlAddress, NormalPagePriority);

        if (pWriteDataBuffer)
        {
            if (IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length, &dwDataWritten))
            {
                DbgPrint(pWriteDataBuffer);
                NtStatus = STATUS_SUCCESS;
            }
        }
    }

    pIrp->IoStatus.Status = NtStatus;
    pIrp->IoStatus.Information = dwDataWritten;

    IoCompleteRequest(pIrp, IO_NO_INCREMENT);

    return NtStatus;
}


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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    NTSTATUS NtStatus = STATUS_UNSUCCESSFUL;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pWriteDataBuffer;
    UINT dwDataWritten = 0;

    DbgPrint("DispatchWriteBufferedIO Called \r\n");

    pIoStackIrp = IoGetCurrentIrpStackLocation(pIrp);

    if (pIoStackIrp)
    {
        pWriteDataBuffer = (PCHAR)pIrp->AssociatedIrp.SystemBuffer;

        if (pWriteDataBuffer)
        {
            if (IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length, &dwDataWritten))
            {
                DbgPrint(pWriteDataBuffer);
                NtStatus = STATUS_SUCCESS;
            }
        }
    }

    pIrp->IoStatus.Status = NtStatus;
    pIrp->IoStatus.Information = dwDataWritten;

    IoCompleteRequest(pIrp, IO_NO_INCREMENT);

    return NtStatus;
}


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
//		Write neither buffered nor direct I/O dispatch routine. All the requests are completed
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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    NTSTATUS NtStatus = STATUS_UNSUCCESSFUL;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pWriteDataBuffer;
    UINT dwDataWritten = 0;

    DbgPrint("DispatchWriteNeither Called \r\n");

    pIoStackIrp = IoGetCurrentIrpStackLocation(pIrp);

    if (pIoStackIrp)
    {
        __try 
        {
            #pragma warning(push)
            #pragma warning(disable : 4116)

            ProbeForRead(pIrp->UserBuffer, pIoStackIrp->Parameters.Write.Length, TYPE_ALIGNMENT(char));
            
            #pragma warning(pop)
            
            pWriteDataBuffer = pIrp->UserBuffer;

            if (pWriteDataBuffer)
            {
                if (IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length, &dwDataWritten))
                {
                    DbgPrint(pWriteDataBuffer);
                    NtStatus = STATUS_SUCCESS;
                }
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) 
        {
            NtStatus = GetExceptionCode();
        }
    }

    pIrp->IoStatus.Status = NtStatus;
    pIrp->IoStatus.Information = dwDataWritten;

    IoCompleteRequest(pIrp, IO_NO_INCREMENT);

    return NtStatus;
}


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
//		Read direct I/O dispatch routine. All the requests are completed
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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    NTSTATUS NtStatus = STATUS_BUFFER_TOO_SMALL;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pReturnData = "DispatchReadBufferedIO - Hello from the Kernel!";
    UINT dwDataSize = sizeof("DispatchReadBufferedIO - Hello from the Kernel!");
    UINT dwDataRead = 0;
    PCHAR pReadDataBuffer;

    DbgPrint("DispatchReadBufferedIO Called \r\n");

    pIoStackIrp = IoGetCurrentIrpStackLocation(pIrp);

    if (pIoStackIrp)
    {
        pReadDataBuffer = (PCHAR)pIrp->AssociatedIrp.SystemBuffer;

        if (pReadDataBuffer && pIoStackIrp->Parameters.Read.Length >= dwDataSize)
        {
            RtlCopyMemory(pReadDataBuffer, pReturnData, dwDataSize);
            dwDataRead = dwDataSize;
            NtStatus = STATUS_SUCCESS;
        }
    }

    pIrp->IoStatus.Status = NtStatus;
    pIrp->IoStatus.Information = dwDataRead;

    IoCompleteRequest(pIrp, IO_NO_INCREMENT);

    return NtStatus;
}


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
//		Read buffered I/O dispatch routine. All the requests are completed
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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    NTSTATUS NtStatus = STATUS_BUFFER_TOO_SMALL;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pReturnData = "DispatchReadDirectIO - Hello from the Kernel!";
    UINT dwDataSize = sizeof("DispatchReadDirectIO - Hello from the Kernel!");
    UINT dwDataRead = 0;
    PCHAR pReadDataBuffer;

    DbgPrint("DispatchReadDirectIO Called \r\n");

    pIoStackIrp = IoGetCurrentIrpStackLocation(pIrp);

    if (pIoStackIrp && pIrp->MdlAddress)
    {
        pReadDataBuffer = MmGetSystemAddressForMdlSafe(pIrp->MdlAddress, NormalPagePriority);

        if (pReadDataBuffer && pIoStackIrp->Parameters.Read.Length >= dwDataSize)
        {
            RtlCopyMemory(pReadDataBuffer, pReturnData, dwDataSize);
            dwDataRead = dwDataSize;
            NtStatus = STATUS_SUCCESS;
        }
    }

    pIrp->IoStatus.Status = NtStatus;
    pIrp->IoStatus.Information = dwDataRead;

    IoCompleteRequest(pIrp, IO_NO_INCREMENT);

    return NtStatus;
}


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
//		Read neither direct nor buffered dispatch routine. All the requests are completed
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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    NTSTATUS NtStatus = STATUS_BUFFER_TOO_SMALL;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pReturnData = "DispatchReadNeither - Hello from the Kernel!";
    UINT dwDataSize = sizeof("DispatchReadNeither - Hello from the Kernel!");
    UINT dwDataRead = 0;
    PCHAR pReadDataBuffer;

    DbgPrint("DispatchReadNeither Called \r\n");

    pIoStackIrp = IoGetCurrentIrpStackLocation(pIrp);

    if (pIoStackIrp)
    {
        __try {

            if (pIoStackIrp->Parameters.Read.Length >= dwDataSize && pIrp->UserBuffer)
            {

                ProbeForWrite(pIrp->UserBuffer, pIoStackIrp->Parameters.Read.Length, sizeof(char));
                pReadDataBuffer = pIrp->UserBuffer;

                RtlCopyMemory(pReadDataBuffer, pReturnData, dwDataSize);
                dwDataRead = dwDataSize;
                NtStatus = STATUS_SUCCESS;
            }

        }
        __except (EXCEPTION_EXECUTE_HANDLER) {

            NtStatus = GetExceptionCode();
        }

    }

    pIrp->IoStatus.Status = NtStatus;
    pIrp->IoStatus.Information = dwDataRead;

    IoCompleteRequest(pIrp, IO_NO_INCREMENT);

    return NtStatus;
}


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
)
{
    UNREFERENCED_PARAMETER(pDeviceObject);
    UNREFERENCED_PARAMETER(pIrp);
    NTSTATUS NtStatus = STATUS_NOT_SUPPORTED;
    DbgPrint("DispatchUnSupportedFunction Called \r\n");

    return NtStatus;
}


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
)
{
    BOOLEAN bStringIsTerminated = FALSE;
    UINT uiIndex = 0;

    *pdwStringLength = 0;

    while (uiIndex < uiLength && bStringIsTerminated == FALSE)
    {
        if (pString[uiIndex] == '\0')
        {
            *pdwStringLength = uiIndex + 1; /* Include the total count we read, includes the NULL */
            bStringIsTerminated = TRUE;
        }
        else
        {
            uiIndex++;
        }
    }

    return bStringIsTerminated;
}