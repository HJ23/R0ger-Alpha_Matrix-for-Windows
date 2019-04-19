#pragma once
#include <string>
#include <cstdio>
#include <Windows.h>

class connector {
private:std::string result;
		STARTUPINFO sti = { 0 };
		SECURITY_ATTRIBUTES sa = { 0 };
		PROCESS_INFORMATION pi = { 0 };
		BYTE by[2048];
		DWORD write, excode, read, available;
		HANDLE pipe_in_w, pipe_in_r, pipe_out_r, pipe_out_w;

public:void connect();
	   std::string get_result(std::string );
	   void close();
	   
};