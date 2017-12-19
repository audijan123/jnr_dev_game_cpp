#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "main_os_manager.hpp"
#include "enumStructs.hpp"
#include "mainStateManager.hpp"
#include "const.hpp"

namespace GDB
{
	class datenbank
	{
	public:
		datenbank();
		~datenbank();
	
		void run();
	
	private:

		void sortiereListeinVector();
	
		bool first_line = true;

		std::vector<GAMESTRUCTS::item_data>	 vitems;
		std::vector<std::string>			 vbuffer;
	};
}
