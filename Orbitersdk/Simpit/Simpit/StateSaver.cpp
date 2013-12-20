#include "StateSaver.h"

HINSTANCE StateSaver::hDLL = 0;

INT_PTR CALLBACK StateSaver::DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) 
{
	switch (Msg)
	{
	case WM_INITDIALOG:

		//get size of window, and create list box to fill it
		RECT rect;
		if (GetWindowRect(hWnd, &rect))
		{
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			HWND hListBox = CreateWindowEx(WS_EX_CLIENTEDGE
				, "LISTBOX", NULL
				, WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL
				, 7, 35, width - 7, height - 35
				, hWnd, NULL, hDLL, NULL);
			lParam = (LPARAM)hListBox;
		}
		return true;
	default:
		return DefDlgProc(hWnd, Msg, wParam, lParam);
	}
}

void StateSaver::load(const char * key, const char * value)
{
	//load ranges
	if (strcmp(key, "range") == 0)
	{
		int first, second;
		if (sscanf(value, " %i %i", &first, &second) == 2)
			ranges.push_back(std::make_pair(first, second));
	}
	//load mapping
	if (strcmp(key, "mapping") == 0)
	{
		int map_key;
		char map_value [256];
		if (sscanf(value, " %i %s", &map_key, map_value) == 2)
			eventToNameMapping[map_key] = std::string(map_value);
	}
}

void StateSaver::loadScenarioState(FILEHANDLE scenario)
{
	char * line;
	while (oapiReadScenario_nextline(scenario, line))
	{
		//load the recorded event
		int ev_id, ev_state;
		if (sscanf(line, "%i %i", &ev_id, &ev_state) == 2)
			recordedEvents[ev_id] = ev_state;
	}


	createListbox();
	listbox = (HWND)oapiGetDialogContext(hDlg);
	//add items to listbox

}

void StateSaver::saveScenarioState(FILEHANDLE scenario)
{
	for (eventMapIterator it = currentEvents.begin(); it != currentEvents.end(); it++)
	{
		char lineToWrite[100];
		sprintf(lineToWrite, "%i %i", it->first, it->second);
		oapiWriteLine(scenario, lineToWrite);
	}
}

void StateSaver::createListbox()
{
	hDlg = oapiOpenDialog(hDLL, 0, &(StateSaver::DlgProc), (void *)this);

}