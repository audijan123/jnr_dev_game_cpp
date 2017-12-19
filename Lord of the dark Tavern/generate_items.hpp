#pragma once

#include <iostream>
#include "main_os_manager.hpp"
#include "datenbank.hpp"
#include <string>
#include <boost/random.hpp>
#include <ctime>
#include "enumStructs.hpp"
#include "sfSpriteGen.hpp"

class gen_item
{
public:
	gen_item();
	~gen_item();

	std::vector<GAMESTRUCTS::item_data> gen_item::items(GAMESTRUCTS::item_class t);

	void gen_item::deleteItemList() { item_list.clear(); };

private:
	GAMESTRUCTS::item_rare gen_item::get_rare(const uint8_t&, const uint8_t&);
	sf::Texture gen_item::get_out_list(const uint8_t&, const uint8_t&, const uint8_t&,const GAMESTRUCTS::item_class&);
	int gen_item::get_rnd_number(const uint8_t&, const uint8_t&, const uint8_t&);
	sf::Color GetItemNameColorByRare(const GAMESTRUCTS::item_rare& r);


	std::vector<GAMESTRUCTS::item_data> item_list;

};
