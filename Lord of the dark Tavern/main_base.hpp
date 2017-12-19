#pragma once

#include <iostream>
#include "enumStructs.hpp"
#include <stdio.h>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "main_os_manager.hpp"
#include "typedefs.hpp"
#include "const.hpp"
#include <boost\filesystem\path.hpp>

namespace JGE
{
	class main_base
	{
	public:
		main_base();
		~main_base();

		std::vector<char> get_memory_data(const std::string& name) const;
		std::vector<char> get_memory_data(std::string name,const int& rnd) const;

		JGE::types::uEinByte get_mob_size_short() { return iSizeOfMobData; };

	private:

		inline void vSetSizeOfMobData();

		HANDLE fHandle;
		WIN32_FIND_DATA wfd;


		JGE::types::uEinByte iSizeOfMobData = 0;
		JGE::types::EinBit found = false;

		std::vector<GAMESTRUCTS::memory_data> d_data;

	};


}