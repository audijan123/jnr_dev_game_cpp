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
					fill_struct_list();
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

void main_data::fill_struct_list()
{


	struct item_data item_data_single = {};
	if (buffer[0] == "WEAPON")
	{
		item_data_single.i_class = { WEAPON };
	}
	else if (buffer[0] == "USEABLE")
	{
		item_data_single.i_class = { USEABLE };
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
	item_data_single.i_texture = buffer[2];
	item_data_single.i_dmg = std::stoi(buffer[3]);
	item_data_single.i_leben = std::stoi(buffer[4]);
	item_data_single.i_stufe = static_cast<short>(std::stoi(buffer[5]));


	if (buffer[6] == "NORMAL")
	{
		item_data_single.i_rare = NORMAL;
	}
	else if (buffer[6] == "BESONDERS")
	{
		item_data_single.i_rare = BESONDERS;
	}
	else if (buffer[6] == "SELTEN")
	{
		item_data_single.i_rare = SELTEN;
	}
	else if (buffer[6] == "SEHRSELTEN")
	{
		item_data_single.i_rare = SEHRSELTEN;
	}
	else if (buffer[6] == "EPISCH")
	{
		item_data_single.i_rare = EPISCH;
	}
	else if (buffer[6] == "LEGENDAER")
	{
		item_data_single.i_rare = LEGENDAER;
	}
	else if (buffer[6] == "MYSTISCH")
	{
		item_data_single.i_rare = MYSTISCH;
	}

	item_data_single.i_buy_price = std::stoi(buffer[7]);
	item_data_single.i_sell_price = std::stoi(buffer[8]);





	items.push_back(item_data_single);
}