#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <Windows.h>

namespace JNR
{
	class main_base
	{
	public:
		main_base(std::string path);
		~main_base();



		std::vector<char> get_memory_data(std::string name) const;

	private:

		short sec_integer = 10;

		std::wstring main_base::s2ws(const std::string& s);

		std::string main_path;

		HANDLE fHandle;
		WIN32_FIND_DATA wfd;

		struct memory_data
		{
			std::vector<char> t;
			std::string name;
		};

		std::vector<struct memory_data> d_data;

	};


}