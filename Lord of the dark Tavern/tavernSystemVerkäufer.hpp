#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"
#include "generate_items.hpp"
#include "mainStateManager.hpp"

namespace GT
{
	class verkäufer
	{
	public:
		verkäufer();
		~verkäufer();

		void update();
		void event();
		void render(sf::RenderWindow *rw);
		void renderGUI(sf::RenderWindow *rw);

	private:

		gen_item					*item_gen;
		//Grundgerüst
		sf::Texture					VerkäuferTexturen[3];
		sf::Sprite					*pVerkäuferSprite;

		// ItemShop / Item Menu / GUI
		sf::Sprite					*pItemShopSprites[12];

		sf::Texture					ItemShopItemTexture[3];
		sf::Sprite					*pItemShopItemSprites[31];

		sf::Sprite					*pVorschauBildSprite;

		sf::RectangleShape			rectangle[4];

		sf::Text					site;


		 uint8_t iAktivItemShopHintergrund = 1;



		int max = 10;

		uint8_t items_per_site_max = 14;
		uint8_t site_max = 10;



		std::vector<GAMESTRUCTS::item_data> item_list;

		struct item_site
		{
			uint8_t items_per_site = 0;
			std::vector<GAMESTRUCTS::item_data> items;

		};

	};

}