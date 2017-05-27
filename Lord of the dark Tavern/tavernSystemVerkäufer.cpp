#include "tavernSystemVerkäufer.hpp"

extern sf::Vector2f vMain;
extern JGE::SpriteGen *pSpriteErsteller;
extern JGE::mainStateManager *pState;
extern sf::Font *pFont;
extern sf::Vector2f vMousePosition;

namespace GT
{
	verkäufer::verkäufer()
	{
		item_gen = new gen_item();

		item_list = item_gen->items(GAMESTRUCTS::item_class::WEAPON);
		std::cout << "TEST: " << item_list[2].i_texture << " SIZE OF VECTOR " << item_list.size() << std::endl;
		//Grundgerüst
		for (auto k = 0; k < 3; k++)
		{
			VerkäuferTexturen[k] = pSpriteErsteller->erstelle_texture("sale" + std::to_string(k + 2));
		}

		pVerkäuferSprite = pSpriteErsteller->erstelle_sprite("sale1", false, sf::Vector2f(650, 100), sf::Vector2f(2.67f, 2.85f));

		for (auto i = 0; i < 12; i++)
		{
			std::string buffer;
			if (i < 10)
			{
				buffer = "itsh" + std::to_string(i);
			}
			else
			{
				"its" + std::to_string(i);
			}
			pItemShopSprites[i] = pSpriteErsteller->erstelle_sprite(buffer, false, sf::Vector2f(0, 0), sf::Vector2f(1, 1));

			if (i >= 1 && i < 5)
			{
				pItemShopSprites[i]->setPosition((vMain.x / 2 - pItemShopSprites[1]->getTexture()->getSize().x*1.5f / 2),
												  vMain.y / 2 - pItemShopSprites[1]->getTexture()->getSize().y*1.5f / 2);
				pItemShopSprites[i]->setScale(1.5f, 1.5f);
			}
		}

		pItemShopSprites[0]->setPosition(pItemShopSprites[1]->getPosition().x + pItemShopSprites[1]->getTexture()->getSize().x*1.44f,
										 pItemShopSprites[1]->getPosition().y + 29);
		pItemShopSprites[11]->setPosition(pItemShopSprites[1]->getPosition().x + 650, pItemShopSprites[1]->getPosition().y + 190);
		pItemShopSprites[8]->setPosition(pItemShopSprites[1]->getPosition().x - 8, pItemShopSprites[1]->getPosition().y + 70);


		pItemShopSprites[0]->setScale(0.78f, 1.58f);

		for (auto i = 0; i < 3; i++)
		{
			ItemShopItemTexture[i] = pSpriteErsteller->erstelle_texture("item" + std::to_string(i));
		}

		for (auto i = 0; i < 30; i++)
		{
			pItemShopItemSprites[i] = new sf::Sprite;
			if (i < 15)
			{
				pItemShopItemSprites[i]->setTexture(ItemShopItemTexture[0]);
			}
			else
			{
				pItemShopItemSprites[i]->setTexture(ItemShopItemTexture[2]);
			}
		}

		pItemShopItemSprites[30] = new sf::Sprite;
		pItemShopItemSprites[30]->setTexture(ItemShopItemTexture[1]);
		pItemShopItemSprites[0]->setPosition(pItemShopSprites[1]->getPosition().x + 65,
											 pItemShopSprites[1]->getPosition().y + 110);
		pItemShopItemSprites[5]->setPosition(pItemShopSprites[1]->getPosition().x + 65,
											 pItemShopSprites[1]->getPosition().y + 182);
		pItemShopItemSprites[10]->setPosition(pItemShopSprites[1]->getPosition().x + 65,
											 pItemShopSprites[1]->getPosition().y + 254);

		pItemShopSprites[9]->setPosition(pItemShopSprites[8]->getPosition());

		for (auto i = 0; i < 3; i++)
		{
			if (i == 0)
			{
				for (auto p = 1; p < 5; p++)
				{
					pItemShopItemSprites[p]->setPosition(pItemShopItemSprites[p - 1]->getPosition().x + 60,
														 pItemShopItemSprites[0]->getPosition().y);
				}
			}
			else if (i == 1)
			{
				for (auto p = 6; p < 10; p++)
				{
					pItemShopItemSprites[p]->setPosition(pItemShopItemSprites[p - 1]->getPosition().x + 60,
														 pItemShopItemSprites[5]->getPosition().y);
				}
			}
			else if (i == 2)
			{
				for (auto p = 11; p < 15; p++)
				{
					pItemShopItemSprites[p]->setPosition(pItemShopItemSprites[p - 1]->getPosition().x + 60,
														 pItemShopItemSprites[10]->getPosition().y);
				}
			}
		}
		for (auto i = 0; i < 15; i++)
		{
			pItemShopItemSprites[i]->setScale(0.15f, 0.3f);

			pItemShopItemSprites[i]->setOrigin(ItemShopItemTexture[0].getSize().x / 2.f,
											   ItemShopItemTexture[0].getSize().y / 2.f);
			pItemShopItemSprites[i + 15]->setOrigin(ItemShopItemTexture[2].getSize().x / 2.f,
													ItemShopItemTexture[2].getSize().y / 2.f);
			pItemShopItemSprites[i + 15]->setPosition(pItemShopItemSprites[i]->getPosition());
		}

		pItemShopItemSprites[30]->setOrigin(ItemShopItemTexture[1].getSize().x / 2.f,
											ItemShopItemTexture[1].getSize().y / 2.f);
		pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[0]->getPosition());

		pItemShopItemSprites[30]->setScale(1.2f, 1.7f);

		pVorschauBildSprite = new sf::Sprite;
		pVorschauBildSprite->setTexture(ItemShopItemTexture[2]);
		pVorschauBildSprite->setPosition(645, 235);

		const GAMESTRUCTS::sRectangle sBuffercords{};

		rectangle[0].setPosition(sBuffercords.rüstung);
		rectangle[1].setPosition(sBuffercords.waffe);
		rectangle[2].setPosition(sBuffercords.schild);
		rectangle[3].setPosition(sBuffercords.special);

		for (auto i = 0; i < 4; i++)
		{
			rectangle[i].setSize(sBuffercords.size);
		}

		pItemShopSprites[5]->setPosition(315, 480);
		pItemShopSprites[6]->setPosition(578, pItemShopSprites[5]->getPosition().y);
		pItemShopSprites[5]->setScale(1.5f, 1.5f);
		pItemShopSprites[6]->setScale(pItemShopSprites[5]->getScale());


		site.setFont(*pFont);
		site.setPosition(pItemShopSprites[5]->getPosition().x + 50, pItemShopSprites[5]->getPosition().y + 3);
		site.setCharacterSize(25);
		site.setString("Seite 1 von " + std::to_string(max));
	}

	verkäufer::~verkäufer()
	{
	}

	void verkäufer::update()
	{

	}
	void verkäufer::event()
	{
		if (osm::sprite_pressed(pVerkäuferSprite, vMousePosition) && !pState->getTavernBankStatus() && !pState->getItemShopStatus())
		{
			// sellman to do
			pState->setItemShopStatus(true);
		}
		else if (pState->getItemShopStatus())
		{
			for (auto i = 0; i < 15; i++)
			{
				if (osm::sprite_pressed(pItemShopItemSprites[i], vMousePosition))
				{
					pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[i]->getPosition());
					pVorschauBildSprite->setTexture(*pItemShopItemSprites[i + 15]->getTexture());
				}
			}

			for (auto i = 0; i < 4; i++)
			{
				if (rectangle[i].getGlobalBounds().contains(vMousePosition) && iAktivItemShopHintergrund != i+1)
				{
					if (!pState->getItemShopCapMenuStatus())
					{
						iAktivItemShopHintergrund = i+1;
						pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[0]->getPosition());
					}
					else if (pState->getItemShopCapMenuStatus())
					{
						iAktivItemShopHintergrund = i+1;
						pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[0]->getPosition());
					}
				}
			}

			if (pItemShopSprites[8]->getGlobalBounds().contains(vMousePosition) && !pState->getItemShopCapMenuStatus())
			{
				iAktivItemShopHintergrund = 1;
				pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[0]->getPosition());
				pState->setItemShopCapMenuStatus(true);
			}
			else if (pItemShopSprites[8]->getGlobalBounds().contains(vMousePosition) && pState->getItemShopCapMenuStatus())
			{
				iAktivItemShopHintergrund = 1;
				pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[0]->getPosition());
				pState->setItemShopCapMenuStatus(false);
			}
			else if (pItemShopSprites[11]->getGlobalBounds().contains(vMousePosition))
			{
				if (pItemShopSprites[11]->getScale().x == -1.f)
				{
					pItemShopSprites[11]->setPosition(pItemShopSprites[11]->getPosition().x - 29,
													  pItemShopSprites[11]->getPosition().y);
					pItemShopSprites[11]->setScale(1.f, 1);
					pState->setItemShopBonusMenuStatus(true);
				}
				else if(pItemShopSprites[11]->getScale().x == 1.f)
				{
					pItemShopSprites[11]->setPosition(pItemShopSprites[11]->getPosition().x + 29,
													  pItemShopSprites[11]->getPosition().y);
					pItemShopSprites[11]->setScale(-1.f, 1);
					pState->setItemShopBonusMenuStatus(false);
				}
			}

		}
	}
	void verkäufer::render(sf::RenderWindow *rw)
	{
		rw->draw(*pVerkäuferSprite);
		
	}

	void verkäufer::renderGUI(sf::RenderWindow *rw)
	{
		if (pState->getItemShopStatus())
		{
			if (pState->getItemShopBonusMenuStatus())
			{
				rw->draw(*pItemShopSprites[0]);
			}
			rw->draw(*pItemShopSprites[iAktivItemShopHintergrund]);

			rw->draw(*pItemShopSprites[11]);
			if (pState->getItemShopCapMenuStatus())
			{
				rw->draw(*pItemShopSprites[9]);
			}
			else if (!pState->getItemShopCapMenuStatus())
			{
				rw->draw(*pItemShopSprites[8]);
			}

			rw->draw(*pItemShopSprites[5]);
			rw->draw(*pItemShopSprites[6]);
			rw->draw(site);

			rw->draw(*pVorschauBildSprite);

			for (auto i = 0; i < 31; i++)
			{
				rw->draw(*pItemShopItemSprites[i]);
			}
		}
	}
}