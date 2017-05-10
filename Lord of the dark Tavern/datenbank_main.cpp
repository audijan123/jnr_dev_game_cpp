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
				//std::cout << d_data << std::endl;

				if (d_data == "#")
				{

					struct item_data item_data_single = {};
					if (buffer[0] == "WEAPON")
					{
						item_data_single.i_class = {WEAPON};
					}
					else if (buffer[0] == "USEABLE")
					{
						item_data_single.i_class = {USEABLE};
					}
					else if (buffer[0] == "CRAFTING")
					{
						item_data_single.i_class = { CRAFTING };
					}
					else if (buffer[0] == "ARMOR")
					{
						item_data_single.i_class = { ARMOR };
					}
					else if (buffer[0] == "SCHILD")
					{
						item_data_single.i_class = { SCHILD };
					}
					else if (buffer[0] == "KOPF")
					{
						item_data_single.i_class = { KOPF };
					}
					else if (buffer[0] == "FOOT")
					{
						item_data_single.i_class = { FOOT };
					}
					else if (buffer[0] == "SPECIAL")
					{
						item_data_single.i_class = { SPECIAL };
					}

					item_data_single.i_name = buffer[1];
					
					//item_data_single.i_class = { static_cast<item_class>(d_data[0]) };
					items.push_back(item_data_single);
					if (items[id].i_class == WEAPON)
					{
						std::cout << items[id].i_class << " : " << items[id].i_name << " Leben: " << items[id].i_leben << std::endl;
					}
					id++;
					buffer.clear();
				}
				else
				{
					buffer.push_back(d_data);
				}

			}
		}



	}
	f.close();
}