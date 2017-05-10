#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <sstream>
#include <vector>


class main_data
{
public:
	main_data(std::string m_path);
	~main_data();

	void run();

	enum item_class
	{
		WEAPON,
		USEABLE,
		CRAFTING,
		ARMOR,
		SCHILD,
		KOPF,
		FOOT,
		SPECIAL,
		NOTDEFINED
	};
	enum item_rare
	{
		NORMAL,
		BESONDERS,
		SELTEN,
		SEHRSELTEN,
		EPISCH,
		LEGENDAER,
		MYSTISCH
	};


	enum item_bouns_flags
	{
		B_NULL
	};

	enum item_cap_flags
	{
		C_NULL,
		NOUSEABLE
	};

	struct item_data
	{
		item_class  i_class = NOTDEFINED;
		std::string i_name = "Leer";
		std::string i_texture = "DATA\item\standart.png";
		int         i_dmg = 0;
		int			i_leben = 0;
		uint8_t		i_stufe = 0;
		item_rare	i_rare = NORMAL;
		int			i_buy_price = 1000;
		int			i_sell_price = 0;
		item_bouns_flags i_bonus_one = B_NULL;
		item_bouns_flags i_bonus_two = B_NULL;
		item_bouns_flags i_bonus_three = B_NULL;
		item_bouns_flags i_bonus_four = B_NULL;
		item_bouns_flags i_bonus_five = B_NULL;
		item_bouns_flags i_bonus_six = B_NULL;
		item_bouns_flags i_bonus_seven = B_NULL;
		item_cap_flags	 i_cap_one = C_NULL;
		item_cap_flags	 i_cap_two = C_NULL;
	};



private:
	void load_db_file();

	bool p_main_run = false;
	bool first_line = true;

	std::string path;

	short id = 0;

	std::vector<item_data> items;

	std::vector<std::string> buffer;
	std::string version = "VERSION<0.0.1>";

};

