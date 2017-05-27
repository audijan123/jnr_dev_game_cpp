#include "datenbank.hpp"

extern std::string sPfad;

namespace GDB
{
	datenbank::datenbank()
	{
		std::string line;
		std::string d_data;
		std::ifstream f;
		f.open(sPfad + "DATA/local.db");
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

					if (d_data == "#")
					{
						sortiereListeinVector();
						vbuffer.clear();
					}
					else
					{
						vbuffer.push_back(d_data);
					}

				}
			}



		}
		f.close();
		p_main_run = true;
	}

	datenbank::~datenbank()
	{
	}

	void datenbank::run()
	{
		while (p_main_run)
		{

		}

	}

	void datenbank::sortiereListeinVector()
	{
		GAMESTRUCTS::item_data bufferStruct = {};
		if (vbuffer[0] == "WEAPON")
		{
			bufferStruct.i_class = { GAMESTRUCTS::WEAPON };
		}
		else if (vbuffer[0] == "USEABLE")
		{
			bufferStruct.i_class = { GAMESTRUCTS::USEABLE };
		}
		else if (vbuffer[0] == "CRAFTING")
		{
			bufferStruct.i_class = { GAMESTRUCTS::CRAFTING };
		}
		else if (vbuffer[0] == "ARMOR")
		{
			bufferStruct.i_class = { GAMESTRUCTS::ARMOR };
		}
		else if (vbuffer[0] == "SCHILD")
		{
			bufferStruct.i_class = { GAMESTRUCTS::SCHILD };
		}
		else if (vbuffer[0] == "KOPF")
		{
			bufferStruct.i_class = { GAMESTRUCTS::KOPF };
		}
		else if (vbuffer[0] == "FOOT")
		{
			bufferStruct.i_class = { GAMESTRUCTS::FOOT };
		}
		else if (vbuffer[0] == "SPECIAL")
		{
			bufferStruct.i_class = { GAMESTRUCTS::SPECIAL };
		}

		bufferStruct.i_name = vbuffer[1];
		bufferStruct.i_texture = vbuffer[2];
		bufferStruct.i_dmg = osm::si(vbuffer[3]);
		bufferStruct.i_leben = osm::si(vbuffer[4]);
		bufferStruct.i_stufe = osm::sB(vbuffer[5]);


		if (vbuffer[6] == "NORMAL")
		{
			bufferStruct.i_rare = GAMESTRUCTS::NORMAL;
		}
		else if (vbuffer[6] == "BESONDERS")
		{
			bufferStruct.i_rare = GAMESTRUCTS::BESONDERS;
		}
		else if (vbuffer[6] == "SELTEN")
		{
			bufferStruct.i_rare = GAMESTRUCTS::SELTEN;
		}
		else if (vbuffer[6] == "SEHRSELTEN")
		{
			bufferStruct.i_rare = GAMESTRUCTS::SEHRSELTEN;
		}
		else if (vbuffer[6] == "EPISCH")
		{
			bufferStruct.i_rare = GAMESTRUCTS::EPISCH;
		}
		else if (vbuffer[6] == "LEGENDAER")
		{
			bufferStruct.i_rare = GAMESTRUCTS::LEGENDAER;
		}
		else if (vbuffer[6] == "MYSTISCH")
		{
			bufferStruct.i_rare = GAMESTRUCTS::MYSTISCH;
		}

		bufferStruct.i_buy_price = osm::si(vbuffer[7]);
		bufferStruct.i_sell_price = osm::si(vbuffer[8]);

		vitems.push_back(bufferStruct);
	}

}