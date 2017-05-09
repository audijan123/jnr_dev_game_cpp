#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>


class main_data
{
public:
	main_data(std::string m_path);
	~main_data();

	void run();

private:
	void load_db_file();

	bool p_main_run = false;

	std::string path;

};

