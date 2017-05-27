#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"
#include "enumStructs.hpp"
#include "mainStateManager.hpp"

namespace GT
{
	class bank
	{
	public:
		bank();
		~bank();

		void update();
		void event();
		void event_get_key(sf::Event *pHauptEvent);
		void render(sf::RenderWindow *rw);
		void renderGUI(sf::RenderWindow *rw);


	private:

		// GUI SAFE
		sf::Sprite						*pSafeSprite[6];

		// GUI BANK
		sf::Texture						BankTexture[7];
		sf::Sprite						*pBankSprite[7];



		GAMESTRUCTS::gold_set status = GAMESTRUCTS::gold_set::init;


		sf::Text banking_text;
		sf::Text current_gold;

		const short activ_safe = 0;

		std::string bank_Set_gold;
		sf::Text set_gold;

		const sf::Vector2f scale = { 2.67f,2.85f };


	};

}