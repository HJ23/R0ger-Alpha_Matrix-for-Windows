#pragma once
#include <Windows.h>
#include "point_packet.h"
#include "mouse_drive.h"
#include "ss.h"
#include <vector>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include "connector.h"
#include <string>
#include <cstdlib>

using namespace cv;
using namespace std;



class data_processor {

private: 
	     Mat data;   //gray image always
		 Mat temp;
		 vector<Moments> moment_ss;
		 vector<vector<Point> > contours;
		 enum color_set { black, white };
		 color_set color_of_opponent;
		 int square_xy;
		 Mat filtered_pure_image;

		 point_packet win_size;
		 point_packet mouse_move;

		 bool change = false;
		 bool first = false;

		 char array_x[8] = { 'a','b','c','d','e','f','g','h' };

		 int prv_chessboard[8][8] = {
	     { 1,1,1,1,1,1,1,1 },
		 { 1,1,1,1,1,1,1,1 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 2,2,2,2,2,2,2,2 },
		 { 2,2,2,2,2,2,2,2 } 
		 };
		 int new_chessboard[8][8] = {
	     { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 },
		 { 0,0,0,0,0,0,0,0 }
		 };

		 Mat kernel1 = Mat::ones(Size(5, 5), CV_8U);
		 Mat kernel2 = Mat::ones(Size(15, 15), CV_8U);
		 Mat kernel3 = Mat::ones(Size(51, 1), CV_8U);
		 Mat kernel4 = Mat::ones(Size(1, 51), CV_8U);
		 string move="";
		 mouse_driver a;
		 connector ccc;
		 desktop_recorder b;

private:
	void image_processor();
	void opponent_finder();   //initialize  2
	inline void calculate_square(point_packet); //initialize  1
	//point_packet find_best_position();
	void any_change();
	void prepare_move();
	void change_player_position(string);
	point_packet make_move_user(string);
	int find_column(const char );


public:
	   
	   void init();
	   data_processor();   //initialize pass window location 0
	   void start();  //while loop here and check interrupt !  3
	   ~data_processor();
};



