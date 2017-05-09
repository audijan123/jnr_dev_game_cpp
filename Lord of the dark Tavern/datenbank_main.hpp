#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <sstream>


class main_data
{
public:
	main_data(std::string m_path);
	~main_data();

	void run();

private:
	void load_db_file();

	bool p_main_run = false;
	bool first_line = true;

	std::string path;


	std::string version = "VERSION<0.0.1>";

};

