#pragma once

NTSTATUS
DriverEntry(
	PDRIVER_OBJECT	pDriverObject,
	PUNICODE_STRING	pRegistryPath
);

VOID
DriverUnload(
	PDRIVER_OBJECT	pDriverObject
);