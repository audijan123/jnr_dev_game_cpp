#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>



class re_loader
{
public:
	re_loader(std::string m_path);
	~re_loader();

	
	std::vector<sf::Image*> get_mob_data() { return mob_data; };

private:

	std::vector<sf::Image*> mob_data;


	std::string work_dir;

	std::wstring s2ws(const std::string& s);

	HANDLE fHandle;
	WIN32_FIND_DATA wfd;


	int c_ord = 0;
	int p = 0;
};
