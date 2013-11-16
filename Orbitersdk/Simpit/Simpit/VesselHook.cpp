// VesselHook.cpp: implementation of the VesselHook class.
//
//////////////////////////////////////////////////////////////////////
#pragma unmanaged
#include "orbitersdk.h"
#include "Queue.h"
#include "HookMethods.h"
#include "VesselHook.h"
#include <cstdio>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VesselHook::VesselHook ()
{
	pVtabl=0;
	Vtabl=0;
	VesselCount=0;
}

int VesselHook::Link (LPDWORD *lpVtabl)
{
	if (pVtabl==0)
	{		
		pVtabl=(LPDWORD)*lpVtabl;
		return hookVtable(true);
	}
	return -1;//Error linking
}

int VesselHook::Unlink ()
{
	if (pVtabl!=0)
	{		
		return hookVtable(false);
		pVtabl=0;		
	}
	return -1;//Error linking	
}

int VesselHook::hookVtable(bool on)
{	
	int i=0;
	LPDWORD *lpVtabl2= (LPDWORD*)HookMethodObject;
	LPDWORD pVtabl2=(LPDWORD)*lpVtabl2;
	//Get process information
	HANDLE hSelf = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ::GetCurrentProcessId());
	MEMORY_BASIC_INFORMATION mbi;

	//Open up vtable of linked object
	if(VirtualQueryEx(hSelf, (LPVOID)(pVtabl), &mbi, sizeof(mbi)) != sizeof(mbi)) return -1;
	PVOID pvRgnBaseAddress = mbi.BaseAddress;
	DWORD dwOldProtect1, dwOldProtect2,/*dwOldProtect3, dwOldProtect4,*/ dwFake;
	if(!::VirtualProtectEx(hSelf, pvRgnBaseAddress, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect1)) return -2;
	BOOL bStridePage = FALSE;
	LPBYTE lpByte = (LPBYTE)pvRgnBaseAddress;
	lpByte += 4096;
	if((DWORD)lpByte < (DWORD)pVtabl + 4) bStridePage = TRUE;
	PVOID pvRgnBaseAddress2 = (LPVOID)lpByte;
	if(bStridePage)
	   if(!::VirtualProtectEx(hSelf, pvRgnBaseAddress2, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect2))
	   {
		   ::VirtualProtectEx(hSelf, pvRgnBaseAddress, 4, dwOldProtect1, &dwFake);
			return -3;
	   }

	int retval=0;
	if (on)
	{
		//Store vtable entries
		int i=0;
		do
		{
			memcpy((LPVOID)&dwFake, (LPVOID)(pVtabl + i++), 4);
		}
		while(dwFake!=0);
		if (i>26)
		{
			Vtabl=new DWORD[i];
			for(i=12;i<18;i++)
			{
				memcpy((LPVOID)(Vtabl+i), (LPVOID)(pVtabl + i), 4);
				memcpy((LPVOID)(pVtabl + i), (LPVOID)(pVtabl2 + i), 4);
			}
			for(i=20;i<27;i+=3)
			{
				memcpy((LPVOID)(Vtabl+i), (LPVOID)(pVtabl + i), 4);
				memcpy((LPVOID)(pVtabl + i), (LPVOID)(pVtabl2 + i), 4);
			}
		}
		else retval=-4;//Error checking virtual table entries (NOT A VESSEL2)
	}
	else
	{
		if (Vtabl!=0)
		{
			for(i=12;i<18;i++)
			{
				memcpy((LPVOID)(pVtabl + i), (LPVOID)(Vtabl+i), 4);				
			}
			for(i=20;i<27;i+=3)
			{
				memcpy((LPVOID)(pVtabl + i), (LPVOID)(Vtabl+i), 4);
			}
			delete [] Vtabl;
			Vtabl=0;
		}
		else retval= -5;//Error restoring virtual table entries (NO VTABLE)
	}

	//Lock vtables again
	::VirtualProtectEx(hSelf, pvRgnBaseAddress, 4, dwOldProtect1, &dwFake);
	if(bStridePage) ::VirtualProtectEx(hSelf, pvRgnBaseAddress2, 4, dwOldProtect2, &dwFake);
	
	return retval;
}

int InstallVesselHook(VESSEL2 *link)
{
	int i;
	if (HookTableSize==0xFE)
	{		
		for(i=0;i<128;i++)
		{
			HookTable[i]=0;
			VesselTable[i]=0;
		}
		HookTableSize=255;
		for(i=0;i<16384;i++)
		{
			VesselInstanceTable[i]=0;
		}
		VesselTableSize=-1;
		HookQueue=new Queue();
		HookMethodObject=new HookMethods();
		if ((EventLogFile  = fopen (EVENTLOGFILE   , "w+")) == NULL) exit(0);
		fprintf(EventLogFile, "(Vessel hooking system initiated)\n");
		fflush(EventLogFile);
	}
	LPDWORD *dummy= (LPDWORD*)link;
	DWORD vTab= (DWORD)*dummy;
	DWORD k=0;
	if (HookTableSize>0x7F)
	{
		fprintf(EventLogFile, "(Class table was empty)\n");
		fflush(EventLogFile);
		if ((i=registerVesselInstance(link))!=0) return i;//Error registering instance		
		if (!hookVesselInternal(0, vTab, link))
		{
			unregisterVesselInstance(link);
			return -1; //Error hooking
		}
		HookTableSize=0;
		fprintf(EventLogFile, "Class hooked\n");
		fflush(EventLogFile);
		return 0;
	}	
	unsigned char a=0, b, c=HookTableSize;
	while(true)
	{
		b=(a+c)>>1;		
		k=HookTable[b];
		if (vTab==k)
		{
			fprintf(EventLogFile, "(Class already hooked)\n");
			fflush(EventLogFile);
			if ((i=registerVesselInstance(link))==0) VesselTable[b]->VesselCount++;
			return i;
		}
		if (vTab<k)
		{
			if (a!=b) c=b-1;
			else break;
		}
		else		
		{
			if (b!=c) a=b+1;
			else
			{
				b++;
				break;
			}
		}
	}
	fprintf(EventLogFile, "(New class to be hooked to set of %d)\n", HookTableSize+1);
	fflush(EventLogFile);
	if (HookTableSize==0x7F)
	{
		fprintf(EventLogFile, "ERROR: Too many classes (max. 128)\n");
		fflush(EventLogFile);
		return -2;//Error too many vessel classes
	}
	if ((i=registerVesselInstance(link))!=0) return i;//Error registering instance
	DWORD dwStore=HookTable[b];
	VesselHook *vhStore=VesselTable[b];
	if (!hookVesselInternal(b, vTab, link))
	{
		unregisterVesselInstance(link);
		return -1; //Error hooking
	}
	if (b<=HookTableSize)
	{
		//Insert
		for(i=HookTableSize;i>b;i--)
		{
			HookTable[i+1]=HookTable[i];
			VesselTable[i+1]=VesselTable[i];
		}
		HookTable[b+1]=dwStore;
		VesselTable[b+1]=vhStore;
	}
	HookTableSize++;
	fprintf(EventLogFile, "Class hooked\n");
	fflush(EventLogFile);
	return 0;
}

int registerVesselInstance(VESSEL2 *link)
{
	int i;
	DWORD vTab= (DWORD)link;
	DWORD k=0;
	if (VesselTableSize<0)
	{
		fprintf(EventLogFile, "(Vessel table was empty)\nVessel hooked\n");
		fflush(EventLogFile);
		VesselInstanceTable[0]=vTab;
		VesselTableSize=0;
		return 0;
	}	
	unsigned char a=0, b, c=VesselTableSize;
	while(true)
	{
		b=(a+c)>>1;		
		k=VesselInstanceTable[b];
		if (vTab==k)
		{
			fprintf(EventLogFile, "(Vessel already hooked)\n");
			fflush(EventLogFile);
			return 1; //Already linked
		}
		if (vTab<k)
		{
			if (a!=b) c=b-1;
			else break;
		}
		else		
		{
			if (b!=c) a=b+1;
			else
			{
				b++;
				break;
			}
		}
	}
	fprintf(EventLogFile, "(New vessel to be hooked to set of %d)\n", VesselTableSize+1);
	fflush(EventLogFile);
	if (VesselTableSize==16383)
	{
		fprintf(EventLogFile, "ERROR: Too many vessels (max. 16384)\n");
		fflush(EventLogFile);
		return -3;//Error too many vessels
	}
	if (b<=VesselTableSize)
	{
		//Insert
		for(i=VesselTableSize;i>=b;i--) VesselInstanceTable[i+1]=VesselInstanceTable[i];
	}
	VesselInstanceTable[b]=vTab;
	VesselTableSize++;
	fprintf(EventLogFile, "Vessel hooked\n");
	fflush(EventLogFile);
	return 0;
}

int RemoveVesselHook(VESSEL2 *link)
{
	int i,j=unregisterVesselInstance(link);
	if (j<0) return j;
	if (HookTableSize>0x7F)
	{
		fprintf(EventLogFile, "ERROR: Class not found in set of %d\n",HookTableSize+1);
		fflush(EventLogFile);
		return -2; //Error finding class
	}
	LPDWORD *dummy= (LPDWORD*)link;
	DWORD vTab= (DWORD)*dummy;
	DWORD k=0;	
	unsigned char a=0, b, c=HookTableSize;
	while(true)
	{
		b=(a+c)>>1;		
		k=HookTable[b];
		if (vTab==k)
		{
			if (--(VesselTable[b]->VesselCount)<0) break;
			return 0;
		}
		if (vTab<k)
		{
			if (a!=b) c=b-1;
			else
			{
				fprintf(EventLogFile, "ERROR: Class not found in set of %d\n",HookTableSize+1);
				fflush(EventLogFile);
				return -2; //Error finding class
			}
		}
		else		
		{
			if (b!=c) a=b+1;
			else
			{
				fprintf(EventLogFile, "ERROR: Class not found in set of %d\n",HookTableSize+1);
				fflush(EventLogFile);
				return -2; //Error finding class
			}
		}
	}
	if (!unhookVesselInternal(b)) return -1; //Error unhooking
	if (HookTableSize==0)
	{
		HookTableSize=0xFF;
		fprintf(EventLogFile, "Class unhooked (table is empty)\n");
		fflush(EventLogFile);
		return 2;//no more hooking active
	}	
	if (b<HookTableSize)
	{
		//Remove
		for(i=b;i<HookTableSize;i++)
		{
			HookTable[i]=HookTable[i+1];
			VesselTable[i]=VesselTable[i+1];
		}
	}	
	HookTableSize--;
	fprintf(EventLogFile, "Class unhooked (no more vessels for this class)\n");
	fflush(EventLogFile);
	return 1;//no more vessels of this class
}

int unregisterVesselInstance(VESSEL2 *link)
{
	int i;
	if (VesselTableSize<0)
	{
		fprintf(EventLogFile, "ERROR: Vessel not found (table is empty)\n");
		fflush(EventLogFile);
		return -3; //Error finding vessel
	}
	DWORD vTab= (DWORD)link;
	DWORD k=0;	
	unsigned char a=0, b, c=VesselTableSize;
	while(true)
	{
		b=(a+c)>>1;		
		k=VesselInstanceTable[b];
		if (vTab==k) break;
		if (vTab<k)
		{
			if (a!=b) c=b-1;
			else
			{
				fprintf(EventLogFile, "ERROR: Vessel not found in set of %d\n",VesselTableSize+1);
				fflush(EventLogFile);
				return -3; //Error finding vessel
			}
		}
		else		
		{
			if (b!=c) a=b+1;
			else
			{
				fprintf(EventLogFile, "ERROR: Vessel not found in set of %d\n",VesselTableSize+1);
				fflush(EventLogFile);
				return -3; //Error finding vessel
			}
		}
	}
	VesselInstanceTable[b]=0;
	if (VesselTableSize==0)
	{
		VesselTableSize=-1;
		fprintf(EventLogFile, "Vessel unhooked (table is empty)\n");
		fflush(EventLogFile);
		return 1;//no more vessel active
	}	
	if (b<VesselTableSize)
	{
		//Remove
		for(i=b;i<VesselTableSize;i++)
		{
			VesselInstanceTable[i]=VesselInstanceTable[i+1];			
		}
	}	
	VesselTableSize--;
	fprintf(EventLogFile, "Vessel unhooked\n");
	fflush(EventLogFile);
	return 0;
}

LPDWORD *GetOriginalVtable(LPDWORD *me, bool &hooked)
{
	if (HookTableSize>0x7F) return 0;
	DWORD vTab= (DWORD)me, k=0;
	int ia=0, ib, ic=VesselTableSize;
	//binary searching instances [16384] => 15 iterations
	hooked=false;
	while(HookEnabled && EventsEnabled)
	{
		ib=(ia+ic)>>1;		
		k=VesselInstanceTable[ib];
		if (vTab==k)
		{
			hooked=true;
			break;
		}
		if (vTab<k)
		{
			if (ia!=ib) ic=ib-1;
			else break;
		}
		else		
		{
			if (ib!=ic) ia=ib+1;
			else break;
		}
	}
	vTab= (DWORD)*me;	
	unsigned char a=0, b, c=HookTableSize;
	//binary searching classes [128] => 8 iterations
	while(true)
	{
		b=(a+c)>>1;		
		k=HookTable[b];
		if (vTab==k) return (LPDWORD *)(VesselTable[b]->Vtabl);
		if (vTab<k)
		{
			if (a!=b) c=b-1;
			else return 0;
		}
		else		
		{
			if (b!=c) a=b+1;
			else return 0;
		}
	}
}

bool hookVesselInternal(unsigned char pos, DWORD vTab, VESSEL2 *link)
{
	VesselHook *hook=new VesselHook();
	int i=hook->Link((LPDWORD*)link);
	if (i!=0)
	{
		fprintf(EventLogFile, "ERROR: Unable to hook the class (ErrNo: %d)!\n",i);
		fflush(EventLogFile);
		delete hook;
		return false;
	}
	HookTable[pos]=vTab;
	VesselTable[pos]=hook;	
	return true;
}

bool unhookVesselInternal(unsigned char pos)
{
	VesselHook *hook=VesselTable[pos];
	int i=hook->Unlink();
	if (i!=0)
	{
		fprintf(EventLogFile, "ERROR: Unable to unhook the class (ErrNo: %d)!\n",i);
		fflush(EventLogFile);
		return false;
	}
	delete hook;	
	return true;
}

void CleanUpHooking()
{
	int i=0;
	if (HookMethodObject==0) return;
	if (HookTableSize<0x80)	for(;i<=HookTableSize;i++) unhookVesselInternal(i);
	HookTableSize=0xFE;
	delete HookMethodObject;
	union Hook_Event *entry;
	while (!HookQueue->is_empty())
	{
		fprintf(EventLogFile, "Clearing queue entry #%d\n", HookQueue->get_count());
		fflush(EventLogFile);
		entry=(union Hook_Event *)HookQueue->Dequeue();
		delete entry;
	}
	delete HookQueue;
}

FILE *GetEventLogFile()
{
	return EventLogFile;
}

Queue *GetEventQueue()
{
	return HookQueue;
}

void SetHookEnabled(bool enabled)
{
	HookEnabled=enabled;
}

void SetEventsEnabled(bool enabled)
{
	EventsEnabled=enabled;
}

bool GetEventsEnabled()
{
	return EventsEnabled;
}