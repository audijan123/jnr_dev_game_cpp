#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <Windows.h>
#include "main_os_manager.hpp"

namespace JNR
{
	class main_base
	{
	public:
		main_base(std::string path);
		~main_base();



		std::vector<char> get_memory_data(const std::string &name) const;
		std::vector<char> get_memory_data(std::string name,int rnd) const;

		short get_mob_size_short() { return size_of_mob; };

	private:

		short sec_integer = 10;

		std::wstring main_base::s2ws(const std::string& s);
		void get_mob_size();

		std::string main_path;

		HANDLE fHandle;
		WIN32_FIND_DATA wfd;

		struct memory_data
		{
			std::vector<char> t;
			std::string name;
		};

		short size_of_mob = 0;

		std::vector<struct memory_data> d_data;

	};


}