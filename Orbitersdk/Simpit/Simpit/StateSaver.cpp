//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

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
				, "listbox", "status_listbox"
				, WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL
				, 0, 0, width, height
				, hWnd, NULL, hDLL, NULL);
			*((HWND*)lParam) = hListBox;
		}
		return true;
	case WM_CLOSE:
		EndDialog(hWnd, wParam);
		return true;
	default:
		return false;
	}
}

void StateSaver::updateDialog()
{
	if (recordedEvents.size() == 0)
	{
		//we're done with the dialog!!!
		oapiCloseDialog(hDlg);
		int result;
		EndDialog(hDlg, (WPARAM)(&result));
	}
}

bool StateSaver::handleEventBlocking(Event ev)
{
	for (unsigned int i = 0; i < ranges.size(); i++)
	{
		if (ev.id > ranges[i].first && ev.id < ranges[i].second)
		{
			//record that sucker!
			currentEvents[ev.id] = ev.state;
			//see if it matches one of our recorded events
			//iterate over map

			eventPairMapIterator itr = recordedEvents.begin();
			while (itr != recordedEvents.end())
			{
				
				//check if the id and state are the same
				if (itr->second.first == ev.id && itr->second.second == ev.state)
				{
					fprintf(Log::returnLogHandle(), "[StateSaver]-Handled and Blocked event, id=%i\tstate=%i\n",
						(ev.id), (ev.state));
					//delete from listbox
					int item_id = SendMessage(listbox, LB_FINDSTRINGEXACT, -1, (LPARAM)(itr->first.c_str()));

					if (item_id != LB_ERR)
						SendMessage(listbox, LB_DELETESTRING, item_id, NULL);
					else
						Log::println("[StateSaver]-Couldn't delete string out of listbox!");
					//delete from map
					itr = recordedEvents.erase(itr);
					updateDialog();
					//return true, we handled it
					return true;
				}
				else
				{	
					//to make sure "bad" events are blocked, return true if the id is the same
					if (itr->second.first == ev.id)
						return true;
					itr++;
				}

			}
			updateDialog();
		}
	}
	return false;
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
	createListbox();
	//listbox = (HWND)oapiGetDialogContext(hDlg);

	char * line;
	while (oapiReadScenario_nextline(scenario, line))
	{
		//load the recorded event and add to listbox
		int ev_id, ev_state;
		if (sscanf(line, "%i %i", &ev_id, &ev_state) == 2)
		{
			std::string item_name;
			//see if there is an easy name for the event
			if (eventToNameMapping.count(ev_id) != 0)
			{
				//just add the easy name to the listbox
				SendMessage(listbox, LB_ADDSTRING, NULL,
					(LPARAM)eventToNameMapping[ev_id].c_str());
				item_name = eventToNameMapping[ev_id];
			}
			else
			{
				//no easy name :(
				char idToString[100];
				sprintf(idToString, "%d", ev_id);

				SendMessage(listbox, LB_ADDSTRING, NULL,
					(LPARAM)idToString);
				
				item_name = idToString;
			}
			//add to recorded events
			recordedEvents[item_name] = std::make_pair(ev_id, ev_state);

			updateDialog();
		}
	}
	updateDialog();
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
	hDlg = oapiOpenDialog(hDLL, IDD_STATE, &(StateSaver::DlgProc), (void *)(&listbox));

}