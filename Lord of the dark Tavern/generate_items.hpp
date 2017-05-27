#pragma once

#include <iostream>
#include "main_os_manager.hpp"
#include "datenbank.hpp"
#include <string>
#include <boost/random.hpp>
#include <ctime>
#include "enumStructs.hpp"

class gen_item
{
public:
	gen_item();
	~gen_item();

	std::vector<GAMESTRUCTS::item_data> gen_item::items(GAMESTRUCTS::item_class t);

private:
	GAMESTRUCTS::item_rare gen_item::get_rare();
	std::string gen_item::get_out_list();
	int gen_item::get_rnd_number();


	std::vector<GAMESTRUCTS::item_data> item_list;

};
