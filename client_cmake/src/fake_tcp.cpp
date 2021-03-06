#if defined(WIN32) || defined(_WIN32)
#include "stdafx.h"
#endif

#include <iostream>
#include <string>
#include <vector>

#include "fake_tcp.h"
#include "util.h"

std::string FakeTCP::get_new_file_name()
{
	static int num = 0;
	++num;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
	std::string file_name("outputs\output");
#else
	std::string file_name("outputs/output");
#endif

	std::string suffix(".xml");

	file_name += std::to_string(num) + suffix;
	
	return file_name;
}

void FakeTCP::send()
{
	while(END != tcp_state->get_state())
		tcp_state->step(*this);
}

void FakeTCP::set_data(std::vector<int> &data_)
{
	data = data_;
}

std::vector<int> & FakeTCP::get_data()
{
	return data;
}
