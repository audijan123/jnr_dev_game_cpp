#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"
#include "generate_items.hpp"
#include "mainStateManager.hpp"
#include "const.hpp"

namespace GT
{
	class verk�ufer
	{
	public:
		verk�ufer();
		~verk�ufer();

		void update();
		void event();
		void render(sf::RenderWindow *rw);
		void renderGUI(sf::RenderWindow *rw);

	private:

		void verk�ufer::f�lleSeitenMitItems();
		void verk�ufer::ItemShopSeiteNeuErstellen();

		gen_item					*item_gen;
		//Grundger�st
		sf::Texture					Verk�uferTexturen[3];
		sf::Sprite					*pVerk�uferSprite;

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

		std::vector<GAMESTRUCTS::item_site> vItemShopSeitenDatenR�stung;
		std::vector<GAMESTRUCTS::item_site> vItemShopSeitenDatenWeapon;
		std::vector<GAMESTRUCTS::item_site> vItemShopSeitenDatenSchild;
		std::vector<GAMESTRUCTS::item_site> vItemShopSeitenDatenSpezial;

		std::vector<GAMESTRUCTS::item_data> vItemShopDaten;

	};

}