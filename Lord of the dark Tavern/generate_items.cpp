#include "generate_items.hpp"

gen_item::gen_item()
{
}

gen_item::~gen_item()
{
}

std::vector<GAMESTRUCTS::item_data> gen_item::items(GAMESTRUCTS::item_class t)
{
	std::time_t times = std::time(0);
	boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;

	int t_rnd = dev() % 50 +5;
	for (auto i = 0; i < t_rnd; i++)
	{

		GAMESTRUCTS::item_data buff = {};

		buff.i_rare = get_rare();
		buff.i_class = t;
		buff.i_name = "TEST";
		buff.i_texture = get_out_list();
		buff.i_dmg = get_rnd_number();
		buff.i_leben = get_rnd_number();
		item_list.push_back(buff);
	}
	return item_list;

}

std::string gen_item::get_out_list()
{
	std::time_t times = std::time(0);
	boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;

	int rnd = dev() % 33;
	if (rnd < 10)
	{
		return "itw0" + std::to_string(rnd);
	}
	else if(rnd == 0)
	{
		return "itw00";
	}
	else
	{
		return "itw" + std::to_string(rnd);
	}
}

int gen_item::get_rnd_number()
{
	std::time_t times = std::time(0);
	boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;

	return dev() % 100;

}

GAMESTRUCTS::item_rare gen_item::get_rare()
{
	std::time_t times = std::time(0);
	boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;
	uint8_t int_buffer = dev() % 7;
	if (int_buffer == 0)
	{
		return GAMESTRUCTS::item_rare::NORMAL;
	}
	else if (int_buffer == 1)
	{
		return GAMESTRUCTS::item_rare::BESONDERS;
	}
	else if (int_buffer == 2)
	{
		return GAMESTRUCTS::item_rare::SELTEN;
	}
	else if (int_buffer == 3)
	{
		return GAMESTRUCTS::item_rare::SEHRSELTEN;
	}
	else if (int_buffer == 4)
	{
		return GAMESTRUCTS::item_rare::EPISCH;
	}
	else if (int_buffer == 5)
	{
		return GAMESTRUCTS::item_rare::LEGENDAER;
	}
	else if (int_buffer == 6)
	{
		return GAMESTRUCTS::item_rare::MYSTISCH;
	}
	return GAMESTRUCTS::item_rare::NORMAL;
}