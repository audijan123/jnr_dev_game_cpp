#pragma once

#include <iostream>
#include "main_os_manager.hpp"
#include "datenbank_main.hpp"
#include <string>
#include <boost/random.hpp>
#include <ctime>

class gen_item
{
public:
	gen_item();
	~gen_item();

	std::vector<main_data::item_data> gen_item::items(main_data::item_class t);

private:
	main_data::item_rare gen_item::get_rare();
	std::string gen_item::get_out_list();
	int gen_item::get_rnd_number();


	std::vector<main_data::item_data> item_list;

};
