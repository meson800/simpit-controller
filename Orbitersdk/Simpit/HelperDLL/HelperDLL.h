// HelperDLL.h

#pragma once

class CRgn;

namespace HelperDLL {

	class Helpers
	{
	public:
		static void SetWindowRegion(HWND window,CRgn region, bool redraw);
		static void SetWindowRegion(HWND window,int left, int top, int right, int bottom, bool redraw);
	};
}
