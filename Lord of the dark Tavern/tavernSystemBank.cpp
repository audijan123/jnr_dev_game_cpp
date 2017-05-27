#include "tavernSystemBank.hpp"

extern sf::Vector2f vMain;
extern JGE::SpriteGen *pSpriteErsteller;
extern JGE::mainStateManager *pState;
extern sf::Font *pFont;
extern sf::Vector2f vMousePosition;

namespace GT
{
	bank::bank()
	{
		for (auto i = 0; i < 7; i++)
		{
			pBankSprite[i]			= new sf::Sprite;

			BankTexture[i] = pSpriteErsteller->erstelle_texture("bank" + std::to_string(i + 1));
			pBankSprite[i]->setTexture(BankTexture[i]);

			if (i != 6)
			{
				pSafeSprite[i] = pSpriteErsteller->erstelle_sprite("safe" + std::to_string(i + 1), false,
																	sf::Vector2f(120, 325), scale);
				if (i > 0)
				{
					float y_buffer = (pSafeSprite[i]->getTexture()->getSize().y*scale.y)
									- (pSafeSprite[0]->getTexture()->getSize().y*scale.y);

					pSafeSprite[i]->setPosition(120, 325 - y_buffer);
				}
			}

		}

		// BANKING POSI
		pBankSprite[0]->setScale(0.85f, 1.5f);
		pBankSprite[1]->setScale(1.2f, 1.f);
		pBankSprite[3]->setScale(1.f, 0.8f);

		pBankSprite[0]->setOrigin(BankTexture[0].getSize().x / 2.f, BankTexture[0].getSize().y / 2.f);

		pBankSprite[0]->setPosition(vMain.x / 2.f, vMain.y / 2.f);
		pBankSprite[1]->setPosition(pBankSprite[0]->getPosition().x - 200.f*0.8f, pBankSprite[0]->getPosition().y);
		pBankSprite[2]->setPosition(pBankSprite[1]->getPosition());
		pBankSprite[3]->setPosition(pBankSprite[0]->getPosition().x - 1.f + (BankTexture[0].getSize().x / 2)*0.85f - BankTexture[3].getSize().x, pBankSprite[0]->getPosition().y - 92.f);
		pBankSprite[4]->setPosition(pBankSprite[1]->getPosition().x + BankTexture[1].getSize().x*0.9f, pBankSprite[1]->getPosition().y + 40);
		pBankSprite[6]->setPosition(pBankSprite[1]->getPosition().x + BankTexture[1].getSize().x*1.08f, pBankSprite[4]->getPosition().y);
		pBankSprite[5]->setPosition(pBankSprite[1]->getPosition().x + BankTexture[1].getSize().x*1.08f, pBankSprite[4]->getPosition().y);


		banking_text.setFont(*pFont);
		current_gold.setFont(*pFont);
		set_gold.setFont(*pFont);

		banking_text.setPosition(pBankSprite[1]->getPosition().x, pBankSprite[1]->getPosition().y - 25);
		current_gold.setPosition(pBankSprite[1]->getPosition().x + 35, pBankSprite[1]->getPosition().y - 11);
		set_gold.setPosition(pBankSprite[1]->getPosition().x + 35, pBankSprite[1]->getPosition().y - 11);

		current_gold.setCharacterSize(44);
		banking_text.setCharacterSize(20);
		set_gold.setCharacterSize(44);

		current_gold.setFillColor(sf::Color::Black);
		set_gold.setFillColor(sf::Color::Black);

		banking_text.setString("Current Gold");
		set_gold.setString("");
		banking_text.setString("Current Gold");
		current_gold.setString("1000000M");
	}

	bank::~bank()
	{

	}

	void bank::update()
	{
		set_gold.setString(bank_Set_gold);
	}

	void bank::event_get_key(sf::Event *pHauptEvent)
	{
		if (pHauptEvent->key.code >= 26 && pHauptEvent->key.code <= 35 && pState->getbGoldVerändernStatus())
		{
			if (bank_Set_gold.length() == 0 && pHauptEvent->key.code == 26)
			{
				osm::call("Die erstezahl kann keine Null sein!");
			}
			else if (bank_Set_gold.length() == 12)
			{
				osm::call("Max Erreicht");
			}
			else
			{
				bank_Set_gold.push_back(static_cast<char>(pHauptEvent->key.code + 22));
			}
		}
		else if (pHauptEvent->key.code == 59 && bank_Set_gold.length() > 0)
		{
			bank_Set_gold.pop_back();
		}
	}

	void bank::event()
	{
		if (osm::sprite_pressed(pSafeSprite[activ_safe], vMousePosition))
		{
			pState->setTavernBankStatus(true);
		}
		else if (pState->getTavernBankStatus())
		{
			if (osm::sprite_pressed(pBankSprite[3], vMousePosition))
			{
				if (pState->getbGoldVerändernStatus())
				{
					pState->setbGoldVerändernStatus(false);
					set_gold.setString("");
					bank_Set_gold.clear();
					banking_text.setString("Current Gold");
					status = GAMESTRUCTS::gold_set::init;
				}
				else
				{
					pState->setTavernBankStatus(false);
				}
			}
			else if (osm::sprite_pressed(pBankSprite[4], vMousePosition) && !pState->getbGoldVerändernStatus())
			{
				status = GAMESTRUCTS::gold_set::negativ;
				banking_text.setString("Wieviel willst du haben?");
				pState->setbGoldVerändernStatus(true);
			}
			else if (osm::sprite_pressed(pBankSprite[6], vMousePosition) && !pState->getbGoldVerändernStatus())
			{
				status = GAMESTRUCTS::gold_set::positiv;
				banking_text.setString("Wieviel willst du einzahlen?");
				pState->setbGoldVerändernStatus(true);
			}
			else if (osm::sprite_pressed(pBankSprite[5], vMousePosition) && pState->getbGoldVerändernStatus())
			{
				if (status == GAMESTRUCTS::gold_set::positiv)
				{
					// player money - and bank money +
					// saverange
				}
				else if (status == GAMESTRUCTS::gold_set::negativ)
				{
					// player money + and bank money -
					// player cant get money out of range
				}
				else
				{
					osm::call("Error: Banking System Status");
				}
				pState->setbGoldVerändernStatus(false);
				bank_Set_gold.clear();
				status = GAMESTRUCTS::gold_set::init;
				banking_text.setString("Current Gold");
			}
		}
	}

	void bank::render(sf::RenderWindow *rw)
	{
		rw->draw(*pSafeSprite[activ_safe]);

	}
	void bank::renderGUI(sf::RenderWindow *rw)
	{
		if (pState->getTavernBankStatus())
		{
			rw->draw(*pBankSprite[0]);
			rw->draw(*pBankSprite[1]);
			rw->draw(*pBankSprite[2]);
			rw->draw(*pBankSprite[3]);
			if (!pState->getbGoldVerändernStatus())
			{
				rw->draw(*pBankSprite[4]);
				rw->draw(*pBankSprite[6]);
				rw->draw(current_gold);
			}
			else
			{
				rw->draw(*pBankSprite[5]);
				rw->draw(set_gold);
			}
			rw->draw(banking_text);
		}
	}
}