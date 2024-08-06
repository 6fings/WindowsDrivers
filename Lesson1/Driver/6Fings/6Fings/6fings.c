#include <wdm.h>

#include "6fings.h"

#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, DriverUnload)

NTSTATUS
DriverEntry(
	PDRIVER_OBJECT	pDriverObject,
	PUNICODE_STRING	pRegistryPath
)
{
	UNREFERENCED_PARAMETER(pRegistryPath);

	NTSTATUS			NtStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT		pDeviceObject;
	UNICODE_STRING		usDriverName, usDosDeviceName;

	DbgPrint("DriverEntry Called! \r\n");

	RtlInitUnicodeString(
		&usDriverName,
		L"\\Device\\6Fings"
	);

	RtlInitUnicodeString(
		&usDosDeviceName,
		L"\\DosDevices\\6Fings"
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
		IoCreateSymbolicLink(
			&usDosDeviceName,
			&usDriverName
		);
	}

	return NtStatus;
}


VOID
DriverUnload(
	PDRIVER_OBJECT pDriverObject
)
{
	UNICODE_STRING usDosDeviceName;

	DbgPrint("DriverUnload Called! \r\n");

	RtlInitUnicodeString(
		&usDosDeviceName,
		L"\\DosDevices\\6Fings"
	);

	IoDeleteSymbolicLink(&usDosDeviceName);
	IoDeleteDevice(pDriverObject->DeviceObject);
}