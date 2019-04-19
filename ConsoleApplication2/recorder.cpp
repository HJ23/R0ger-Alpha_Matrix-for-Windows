#include "ss.h"


desktop_recorder::desktop_recorder(point_packet a) {
	ccc = a.point1;
	desktop = GetDesktopWindow();
	height = abs(a.point2.y-a.point1.y);
	width = abs(a.point2.x-a.point1.x);

}

desktop_recorder::desktop_recorder() {}

void desktop_recorder::operator()(point_packet a) {
	ccc = a.point1;
	desktop = GetDesktopWindow();
	height = abs(a.point2.y - a.point1.y);
	width = abs(a.point2.x - a.point1.x);
}



void desktop_recorder::start() {

	hwindowDC = GetDC(desktop);
	hwindowDC = GetDC(desktop);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
	RECT size;
	GetClientRect(desktop, &size);
	record.create(height,width,CV_8UC4);

	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);   
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, ccc.x, ccc.y, width,height, SRCCOPY); 
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, record.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

	DeleteObject(hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(desktop, hwindowDC);
	cvtColor(record, record, COLOR_BGR2GRAY);
}


void desktop_recorder::save() {
	imwrite(".",record);  //specify path for screenshot
}


void desktop_recorder::get_record(Mat &a)  {
	record.copyTo(a);
	
}


desktop_recorder::~desktop_recorder() {

	record.release();
}