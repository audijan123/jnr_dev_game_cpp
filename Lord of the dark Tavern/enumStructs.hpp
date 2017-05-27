#pragma once
#include <iostream>

namespace GAMESTRUCTS
{
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
		std::string i_texture = "stand";
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

	enum gold_set
	{
		positiv,
		negativ,
		init
	};

	struct mob
	{
		sf::Sprite *p_sprite = new sf::Sprite;
		sf::Vector2f scale;
		sf::Sprite *p_life = new sf::Sprite;

		sf::Text *text = new sf::Text;

		int life = 10;
		int dmg = 10;
	};

	const struct sRectangle
	{
		const sf::Vector2f rüstung = { 310, 200 };
		const sf::Vector2f waffe = { 378, 200 };
		const sf::Vector2f schild = { 446, 200 };
		const sf::Vector2f special = { 516, 200 };
		const sf::Vector2f size = { 50,45 };
	};
}