#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"
#include "generate_items.hpp"
#include "mainStateManager.hpp"
#include "const.hpp"

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

		void verkäufer::fülleSeitenMitItems();
		void verkäufer::ItemShopSeiteNeuErstellen();

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

		sf::Text					SeitenText;


		sf::Text					DamageText;
		sf::Text					LebensPunkteText;
		sf::Text					MagiePunkteText;
		sf::Text					ItemNameText;

		sf::Texture					KlarTexture;


		uint8_t iAktivItemShopHintergrund = 1;

		int iCheckSprite = 0;
		int seiten[4] = {};
		int aktiv_seite = 1;

		bool ItemShopHover = false;

		std::vector<GAMESTRUCTS::item_site> vItemShopSeitenDatenRüstung;
		std::vector<GAMESTRUCTS::item_site> vItemShopSeitenDatenWeapon;
		std::vector<GAMESTRUCTS::item_site> vItemShopSeitenDatenSchild;
		std::vector<GAMESTRUCTS::item_site> vItemShopSeitenDatenSpezial;

		std::vector<GAMESTRUCTS::item_data> vItemShopDaten;

	};

}