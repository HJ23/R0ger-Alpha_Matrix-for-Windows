#include "process.h"
#include "mouse_drive.h"
#include "exceptions.h"

void data_processor::opponent_finder() {
	try {
		contours.clear();
		threshold(data, temp, 241, 255, THRESH_BINARY);
		erode(temp, temp, kernel1);
		dilate(temp, temp, kernel2);
		medianBlur(temp, temp, 5);
		findContours(temp, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		if (contours.size() == 0)
			throw chess_board_detection_error();
		moment_ss.resize(1);
		moment_ss[0] = moments(contours[0]);
	}
	catch (chess_board_detection_error exception) {
		cout << exception.get_error_message();
		getc(stdin);
		exit(0);
	}


	if ((data.size().height/2)<float(moment_ss[0].m01 / moment_ss[0].m00)) {
		color_of_opponent = black;
		cout << "Opponent is black !"<<endl;
	}
	else {
		color_of_opponent = white;
		cout << "Opponent is white !" << endl;
	}




}

inline void data_processor::calculate_square(point_packet pp) {
	square_xy = abs(pp.point2.y-pp.point1.y)/8;
}

data_processor::data_processor(){
    
	if (a.catch_points()) {
		win_size = a.get_points();
	}

	desktop_recorder b(win_size);
	b.start();
	b.get_record(data);
	
    
}


void data_processor::init() {
	opponent_finder();
	b(win_size);
	calculate_square(win_size);
	ccc.connect();
}


void data_processor::start() {


	if (color_of_opponent==black) {
		string ax=ccc.get_result("");
		move += ax + " ";
		cout << "The best move : " << ax << endl;
		change_player_position(ax);
		a.execute(make_move_user(ax));

	}
	while(!GetAsyncKeyState(VK_ESCAPE)) {
		b.start();
		b.get_record(data);
		any_change();
		if (change) {
			string aaa = ccc.get_result(move);
			cout << "The best move : "<<aaa<<endl;
			move += aaa+" ";
			change_player_position(aaa);
			a.execute(make_move_user(aaa));
		}
		Sleep(3000);
		change = false;
	}
	cout << "Interrupt detected !"<<endl;
	exit(0);


}





void data_processor::image_processor() {

	if (color_of_opponent == black) {
		threshold(data, data, 0, 255, THRESH_BINARY_INV);
	}
	else {
		threshold(data, data, 241, 255, THRESH_BINARY);
	}


	for (int x = 0; x<8; x++) {
		for (int y = 0; y<8; y++) {
			if (prv_chessboard[x][y] == 2) {
				new_chessboard[x][y] = 2;
			}
		}
	}
    

	contours.clear();
	moment_ss.clear();
	erode(data, data, kernel1);
	dilate(data, data, kernel2);
	medianBlur(data, data, 5);
	findContours(data, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	moment_ss.resize(contours.size());
	for (int x = 0; x < contours.size(); x++) {
		moment_ss[x] = moments(contours[x]);
		int a = floor(float(moment_ss[x].m01 / moment_ss[x].m00) / square_xy);
		int b = floor(float(moment_ss[x].m10 / moment_ss[x].m00) / square_xy);
		new_chessboard[a][b] = 1;

	}

}


void data_processor::any_change() {
	
	image_processor();  ///*****************************************


	for (int x = 0; x<8; x++) {
		for (int y = 0; y<8; y++) {
			if (new_chessboard[x][y] != prv_chessboard[x][y]) {
				if ((prv_chessboard[x][y] == 1 && new_chessboard[x][y] == 0)) {
					mouse_move.point1.x = x;
					mouse_move.point1.y = y;
					change = true;
				}

				else if ((prv_chessboard[x][y] == 2 && new_chessboard[x][y] == 1)) {
					mouse_move.point2.x = x;
					mouse_move.point2.y = y;
					change = true;
				}

				else if ((prv_chessboard[x][y] == 0 && new_chessboard[x][y] == 1)) {
					mouse_move.point2.x = x;
					mouse_move.point2.y = y;
					change = true;
					
				}


				
			}
		}
	}


		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				prv_chessboard[x][y] = new_chessboard[x][y];
				if (new_chessboard[x][y] != 2 || new_chessboard[x][y] != 1) {
					new_chessboard[x][y] = 0;
				}
			}
		}

		if (change) {
		

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					cout << prv_chessboard[x][y]<<" ";
				}
				cout << endl;
			}
			
			cout << endl;
			prepare_move();  
				
		}
	

}


int data_processor::find_column(const char x) {
	for (int z = 0; z < 8; z++) {
		if (array_x[z] == x) {
			if (color_of_opponent == black) {
				return z;
			}
			else {
				return (7 - z);
			}
		}
	}
	return 0;
}






void data_processor::change_player_position(std::string move) {
	char str_char[4]; 
	strncpy(str_char,move.c_str(),4);
	
	if (color_of_opponent == white) {
		prv_chessboard[(str_char[1] - '0' - 1)][find_column(str_char[0])] = 0;
		prv_chessboard[(str_char[3] - '0' - 1)][find_column(str_char[2])] = 2;
	}
	else {
		prv_chessboard[8 - int(str_char[1] - '0')][find_column(str_char[0])] = 0;
		prv_chessboard[8 - int(str_char[3] - '0')][find_column(str_char[2])] = 2;

	}

}




void data_processor::prepare_move() {
	
	if (color_of_opponent == white) {
		move += (array_x[7 - mouse_move.point1.y] + to_string(mouse_move.point1.x + 1));
		move += (array_x[7 - mouse_move.point2.y] + to_string(mouse_move.point2.x + 1) + " ");
	}
	else {
		move += (array_x[ mouse_move.point1.y] + to_string(8-mouse_move.point1.x ));
		move += (array_x[mouse_move.point2.y] + to_string(8-mouse_move.point2.x) + " ");	
	}

	cout <<move <<endl;

}



data_processor::~data_processor() {
	data.release();
	temp.release();
	
}



point_packet data_processor::make_move_user(string s) {
	point_packet ret;
	char arr[4];
	strncpy(arr, s.c_str(), 4);


	if (color_of_opponent == white) {
		ret.point1.x = win_size.point1.x+square_xy*(find_column(arr[0]))+square_xy/2;
		ret.point1.y = win_size.point1.y + square_xy*(arr[1] - '0' - 1) + square_xy / 2;
		ret.point2.x= win_size.point1.x + square_xy*(find_column(arr[2])) + square_xy / 2;
		ret.point2.y = win_size.point1.y + square_xy*(arr[3] - '0' - 1) + square_xy / 2;

	}
	else {

		ret.point1.x = win_size.point1.x + square_xy*(find_column(arr[0])) + square_xy;
		ret.point1.y = win_size.point1.y+square_xy*(8-(arr[1]-'0'))+square_xy/2;
		ret.point2.x = win_size.point1.x + square_xy*(find_column(arr[2])) + square_xy;
		ret.point2.y = win_size.point1.y + square_xy*(8 - (arr[3] - '0')) + square_xy / 2;
	
	}

	return ret;
}