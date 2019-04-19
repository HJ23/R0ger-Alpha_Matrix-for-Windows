#pragma once
#include <Windows.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include "point_packet.h"

using namespace std;
using namespace cv;

class desktop_recorder{
private:
	    POINT ccc;
		Mat record;   //image_file
		HWND desktop;
		HDC hwindowDC, hwindowCompatibleDC;
		BITMAPINFOHEADER  bi;
		HBITMAP hbwindow;
		int height, width;
public: desktop_recorder(point_packet);
		desktop_recorder();
		void start();
		void save();
		void get_record(Mat &);
		void operator()(point_packet);

		~desktop_recorder();
};








