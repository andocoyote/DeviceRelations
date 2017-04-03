#include <windows.h>
#include <iostream>
#include <Cfgmgr32.h>
#include <string.h>

using namespace std;

DWORD wmain(DWORD argc, PCWSTR argv[])
{
	DWORD returnCode = 0;
	ULONG bufferSize = 0;
	PCWSTR deviceID = nullptr;
	PWSTR relatedDevicesBuffer = nullptr;
	
	if(argc != 2)
	{
		wcout << "Call this tool with the device ID supplied on the command line.\n";
		goto Cleanup;
	}
	
	deviceID = argv[1];
	
	wcout << "DeviceID: " << deviceID << endl;
	
	// Get the size for the buffer of device IDs
	returnCode = CM_Get_Device_ID_List_SizeW(
		  &bufferSize,
		  deviceID,
		  CM_GETIDLIST_FILTER_NONE
		);
		
	if(returnCode != CR_SUCCESS)
	{
		wcout << "Error: CM_Get_Device_ID_List_Size returned 0x" << returnCode << endl;
		goto Cleanup;
	}
	
	if(bufferSize == 0)
	{
		wcout << "Error: Required buffer size returned by CM_Get_Device_ID_List_Size is 0\n";
		goto Cleanup;
	}
	
	wcout << "Required buffer size returned by CM_Get_Device_ID_List_Size is " << bufferSize << endl;
	
	relatedDevicesBuffer = new WCHAR[bufferSize];
	
	// Query for the list of related devices
	returnCode = CM_Get_Device_ID_ListW(
		  deviceID,
		  relatedDevicesBuffer,
		  bufferSize,
		  CM_GETIDLIST_FILTER_NONE
		);
		
	if(returnCode != CR_SUCCESS)
	{
		wcout << "Error: CM_Get_Device_ID_List returned 0x" << returnCode << endl;
		goto Cleanup;
	}
	
	// Iterate through the collection of related devices.
	// The extra null terminator at the end of the collection allows us to stop the loop at *curDevice
	for(LPWSTR curDevice = relatedDevicesBuffer; *curDevice; curDevice += wcslen(curDevice) + 1)
    {
		wcout << "Related devices: " << curDevice << endl;
	}
	
Cleanup:

	if(relatedDevicesBuffer)
	{
		delete [] relatedDevicesBuffer;
	}

	return 0;
}
