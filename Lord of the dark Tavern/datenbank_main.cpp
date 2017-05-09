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
	std::string d_data;
	std::ifstream f;
	f.open(path + "DATA/local.db");
	if (f.is_open())
	{
		std::getline(f, line);
		if (first_line)
		{
			if (line != version)
			{
				std::cout << "Error DB Version not Match" << std::endl;

			}
			else
			{
				first_line = false;
			}
		}

		if (!first_line)
		{
			while (getline(f, line, ';'))
			{
				std::stringstream ss(line);
				ss >> d_data;
				d_data = d_data.substr(1, d_data.length() - 2);
			}
		}



	}
	f.close();
}