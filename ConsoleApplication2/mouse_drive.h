#pragma once

#ifndef MOUSE_DRIVE
#define MOUSE_DRIVE

#include <Windows.h>
#include "point_packet.h"

class mouse_driver {


private: POINT first, second;

public:
		 point_packet get_points() const;
		 void execute(point_packet);
		 bool catch_points();

};

#endif
