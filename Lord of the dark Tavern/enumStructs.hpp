#pragma once
#include <iostream>
#include "typedefs.hpp"


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
		item_class					i_class = NOTDEFINED;
		JGE::types::SpielString		i_name = "Leer";
		JGE::types::SpielString		i_texture = "stand";
		JGE::types::SpielTexture	ItemTexture;
		sf::Color					cItemColor = { 0,0,0,255 };
		JGE::types::uVierByte		i_dmg = 0;
		JGE::types::uVierByte		i_leben = 0;
		JGE::types::uVierByte		i_magie = 0;
		JGE::types::uEinByte		i_stufe = 0;
		item_rare					i_rare = NORMAL;
		JGE::types::SpielShopInt	i_buy_price = 1000;
		JGE::types::SpielShopInt	i_sell_price = 0;
		item_bouns_flags			i_bonus_one = B_NULL;
		item_bouns_flags			i_bonus_two = B_NULL;
		item_bouns_flags			i_bonus_three = B_NULL;
		item_bouns_flags			i_bonus_four = B_NULL;
		item_bouns_flags			i_bonus_five = B_NULL;
		item_bouns_flags			i_bonus_six = B_NULL;
		item_bouns_flags			i_bonus_seven = B_NULL;
		item_cap_flags				i_cap_one = C_NULL;
		item_cap_flags				i_cap_two = C_NULL;
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

	struct item_site
	{
		uint8_t items_per_site = 0;
		std::vector<GAMESTRUCTS::item_data> items;

	};
	struct ItemNameColor
	{
		sf::Color Weiß		= { 255,255,255,255 };
		sf::Color hBlau		= { 0,	255,255,255 };
		sf::Color dBlau		= { 0,	183,255,255 };
		sf::Color Rot		= { 214,  0,  0,255 };
		sf::Color Orange	= { 214,138,  0,255 };
		sf::Color Grün		= { 113,240, 87,255 };
		sf::Color hPink		= { 214,  0,190,255 };
	};


	const struct ItemTextureBereichsGroeße
	{
		const uint8_t iRüstungsGroeße	= 21;
		const uint8_t iWaffenGroeße		= 33;
		const uint8_t iSchildGroeße		= 23;
		const uint8_t iSpezialGroeße	= 41;
		const uint8_t iDefault			= 0;
	};
	
	struct memory_data
	{
		std::vector<char> t;
		std::string name;
	};

}