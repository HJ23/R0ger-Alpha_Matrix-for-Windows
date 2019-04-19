
#include "mouse_drive.h"
#include <Windows.h>
#include <iostream>

void move_left_down_and_up(POINT x1) {
	SetCursorPos(x1.x, x1.y);
	Sleep(50);
	INPUT a = {0};
	a.type = INPUT_MOUSE;
	a.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &a, sizeof(a));
	Sleep(50);
	ZeroMemory(&a, sizeof(a));
	a.type = INPUT_MOUSE;
	a.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &a, sizeof(a));
	Sleep(50);
}




bool mouse_driver::catch_points() {
	int option;
	std::cout << "To recognize chess board correctly software needs 2 points " << std::endl;
	std::cout << "( just move mouse indicated location and click left mouse button )" << std::endl;


A:

	std::cout << std::endl;
	std::cout << " - Specify first (LEFT_TOP) point " << std::endl;
	while (1) {

		if (GetKeyState(VK_LBUTTON) & 0x100) {
			GetCursorPos(&first);
			std::cout << "Mouse Position captured !   (" << first.x << "," << first.y << ")" << std::endl;
			break;
		}
	}

	C:
	std::cout << "The mouse position for first (LEFT_TOP) point is correct ?  (y/n) >>>";
		option = std::getchar();
		if (option == 'y' || option == 'Y') {
			std::getchar();
			goto B;
		}
		else if (option == 'N' || option == 'n')
		{
			std::getchar();
			goto A;
		}
		else {
			std::getchar();
			std::cout << "Please just use y/n or Y/N  letters !"<<std::endl;
			goto C;
		}
	B:
		std::cout << std::endl;
		std::cout << " - Specify second (RIGHT_BOTTOM) point " << std::endl;
		while (1) {

			if (GetKeyState(VK_LBUTTON) & 0x100) {
				GetCursorPos(&second);
				std::cout << "Mouse Position captured !   (" << second.x << "," << second.y << ")" << std::endl;
				break;
			}

		}
	D:
		std::cout << "The mouse position for second (RIGHT_BOTTOM) point is correct ?  (y/n) >>>";
		option = std::getc(stdin);
		if (option == 'y' || option == 'Y') {
			std::getchar();
		}
		else if (option == 'N' || option == 'n')
		{
			std::getchar();
			goto B;
		}
		else {
			std::getchar();
			std::cout << "Please just use y/n or Y/N  letters !" << std::endl;
			goto D;
		}
		


		std::cout << "Operation succesfull " << std::endl;
		return true;

	}


point_packet mouse_driver::get_points() const{
	point_packet a;
	a.point1 = first;
	a.point2 = second;
	return a;
}

void mouse_driver::execute(point_packet a) {
	
	move_left_down_and_up(a.point1);
	Sleep(300);
	move_left_down_and_up(a.point2);
	Sleep(300);
	SetCursorPos(0,0);
	Sleep(50);
}


