#include "datenbank_main.hpp"


main_data::main_data(std::string m_path) :
	path(m_path)
{
	p_main_run = true;
	load_db_file();

}

main_data::~main_data()
{
}

void main_data::run()
{
	std::cout << "update" << std::endl;
	while (p_main_run)
	{
	}

}


void main_data::load_db_file()
{
	std::string line;
	std::ifstream f;
	f.open(path + "DATA/local.db");
	if (f.is_open())
	{
		while (std::getline(f, line)) {
			std::cout << line << std::endl;
			
		}
	}
	f.close();
}