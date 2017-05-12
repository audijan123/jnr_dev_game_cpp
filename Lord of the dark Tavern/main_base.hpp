#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>

namespace JNR
{
	class main_base
	{
	public:
		main_base(std::string path);
		~main_base();



		std::vector<char> get_memory_data(std::string name) const;

	private:

		std::string main_path;

		struct memory_data
		{
			std::vector<char> t;
			std::string name;
		};

		std::vector<struct memory_data> d_data;

	};


}