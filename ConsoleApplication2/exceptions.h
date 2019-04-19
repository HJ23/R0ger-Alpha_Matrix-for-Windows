#pragma once

#include <string>
class base {
public:  std::string error_message;
        virtual std::string get_error_message()=0;
		virtual void set_error_message()=0;

};


class engine_error_exception : public base {
private: void set_error_message() { error_message = "Engine return Null value something went wrong !"; };
public:std::string get_error_message() { return error_message; };
};

class chess_board_detection_error :public base {
private:void set_error_message() { error_message = "Please specify coordinates properly chessboard detection finished unproperly !"; };
public:std::string get_error_message() { return error_message; }
};