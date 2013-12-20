#ifndef STATE_SAVER
#define STATE_SAVER

#include <Windows.h>
#include <vector>
#include <map>
#include <string>

#include "resource.h"
#include "OrbiterAPI.h"
#include "IO.h"

typedef std::map<int, int>::iterator eventMapIterator;
typedef std::map<int, std::pair<int, int>>::iterator eventPairMapIterator;

class StateSaver : public IO
{
public:
	StateSaver(HINSTANCE _hDLL) {hDLL = _hDLL; }
	void load(const char * key, const char * value);
	void loadScenarioState(FILEHANDLE scenario);
	void saveScenarioState(FILEHANDLE scenario);
	bool handleEventBlocking(Event ev);

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

private:
	void createListbox();
	void updateDialog();
	bool inRange(Event ev);

	std::vector <std::pair<int, int>> ranges;
	std::map<int, std::pair<int, int>> recordedEvents;
	std::map<int, int> currentEvents;
	std::map<int, std::string> eventToNameMapping;

	HWND listbox;
	HWND hDlg;

	static HINSTANCE hDLL;

};

#endif