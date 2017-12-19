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

		sf::Texture ItemShopSpriteTexture;
		ItemShopSpriteTexture.create(33, 35);

		for (auto i = 0; i < 30; i++)
		{
			pItemShopItemSprites[i] = new sf::Sprite;
			if (i < 15)
			{
				pItemShopItemSprites[i]->setTexture(ItemShopItemTexture[0]);
			}
			else
			{
				pItemShopItemSprites[i]->setTexture(ItemShopSpriteTexture);
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
			pItemShopItemSprites[i + 15]->setOrigin(ItemShopSpriteTexture.getSize().x / 2.f,
													ItemShopSpriteTexture.getSize().y / 2.f);
			pItemShopItemSprites[i + 15]->setPosition(pItemShopItemSprites[i]->getPosition());
		}

		pItemShopItemSprites[30]->setOrigin(ItemShopItemTexture[1].getSize().x / 2.f,
											ItemShopItemTexture[1].getSize().y / 2.f);
		pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[0]->getPosition());

		pItemShopItemSprites[30]->setScale(1.2f, 1.7f);

		pVorschauBildSprite = new sf::Sprite;
		pVorschauBildSprite->setTexture(ItemShopSpriteTexture);
		pVorschauBildSprite->setPosition(640, 235);

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


		SeitenText.setFont(*pFont);
		SeitenText.setPosition(pItemShopSprites[5]->getPosition().x + 50, pItemShopSprites[5]->getPosition().y + 3);
		SeitenText.setCharacterSize(25);
		SeitenText.setString("Seite 1 von 1");


		DamageText.setFont(*pFont);
		LebensPunkteText.setFont(*pFont);
		MagiePunkteText.setFont(*pFont);
		ItemNameText.setFont(*pFont);

		DamageText.setString("");
		LebensPunkteText.setString("");
		MagiePunkteText.setString("");
		ItemNameText.setString("");

		DamageText.setCharacterSize(iItemShopSchriftGröße);
		LebensPunkteText.setCharacterSize(iItemShopSchriftGröße);
		MagiePunkteText.setCharacterSize(iItemShopSchriftGröße);
		ItemNameText.setCharacterSize(iItemShopSchriftGröße);


		DamageText.setPosition(pItemShopSprites[1]->getPosition().x + 450, pItemShopSprites[1]->getPosition().y +77);
		LebensPunkteText.setPosition(DamageText.getPosition().x + 90, DamageText.getPosition().y);
		MagiePunkteText.setPosition(DamageText.getPosition().x + 180, DamageText.getPosition().y);
		ItemNameText.setPosition(pItemShopSprites[1]->getPosition().x + 415, pItemShopSprites[1]->getPosition().y+45);

		KlarTexture.create(40,40);
		pVorschauBildSprite->setTexture(KlarTexture);


		fülleSeitenMitItems();
		aktiv_seite = 1;
		ItemShopSeiteNeuErstellen();


	}

	verkäufer::~verkäufer()
	{
	}

	void verkäufer::update()
	{
		if (iAktivItemShopHintergrund == 1 && aktiv_seite-1 <= vItemShopSeitenDatenRüstung.size())
		{
			iCheckSprite = vItemShopSeitenDatenRüstung[aktiv_seite - 1].items_per_site;
			for (auto i = 0; i < vItemShopSeitenDatenRüstung[aktiv_seite-1].items_per_site; i++)
			{
				pItemShopItemSprites[i + 15]->setTexture(vItemShopSeitenDatenRüstung[aktiv_seite-1].items[i].ItemTexture);
			}
		}
		else if (iAktivItemShopHintergrund == 2 && aktiv_seite - 1 <= vItemShopSeitenDatenWeapon.size())
		{

			iCheckSprite = vItemShopSeitenDatenWeapon[aktiv_seite - 1].items_per_site;
			for (auto i = 0; i < vItemShopSeitenDatenWeapon[aktiv_seite - 1].items_per_site; i++)
			{
				pItemShopItemSprites[i + 15]->setTexture(vItemShopSeitenDatenWeapon[aktiv_seite - 1].items[i].ItemTexture);
			}
		}
		else if (iAktivItemShopHintergrund == 3 && aktiv_seite - 1 <= vItemShopSeitenDatenSchild.size())
		{

			iCheckSprite = vItemShopSeitenDatenSchild[aktiv_seite - 1].items_per_site;
			for (auto i = 0; i < vItemShopSeitenDatenSchild[aktiv_seite - 1].items_per_site; i++)
			{
				pItemShopItemSprites[i + 15]->setTexture(vItemShopSeitenDatenSchild[aktiv_seite - 1].items[i].ItemTexture);
			}
		}
		else if (iAktivItemShopHintergrund == 4 && aktiv_seite - 1 <= vItemShopSeitenDatenSpezial.size())
		{

			iCheckSprite = vItemShopSeitenDatenSpezial[aktiv_seite - 1].items_per_site;
			for (auto i = 0; i < vItemShopSeitenDatenSpezial[aktiv_seite - 1].items_per_site; i++)
			{
				pItemShopItemSprites[i + 15]->setTexture(vItemShopSeitenDatenSpezial[aktiv_seite - 1].items[i].ItemTexture);
			}
		}

	}
	void verkäufer::event()
	{
		if (osm::sprite_pressed(pVerkäuferSprite, vMousePosition) && !pState->getTavernBankStatus() 
			&& !pState->getItemShopStatus())
		{
			// sellman to do
			pState->setItemShopStatus(true);
		}
		else if (pState->getItemShopStatus())
		{
			for (auto i = 0; i < iCheckSprite; i++)
			{
				if (osm::sprite_pressed(pItemShopItemSprites[i], vMousePosition))
				{
					pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[i]->getPosition());
					pVorschauBildSprite->setTexture(*pItemShopItemSprites[i + 15]->getTexture());
					switch (iAktivItemShopHintergrund)
					{
					case 1:
						ItemNameText.setColor(vItemShopSeitenDatenRüstung[aktiv_seite - 1].items[i].cItemColor);
						ItemNameText.setString(osm::convertEnumToString(vItemShopSeitenDatenRüstung[aktiv_seite - 1].items[i].i_rare) +
							vItemShopSeitenDatenRüstung[aktiv_seite - 1].items[i].i_name);

						DamageText.setString(std::to_string(vItemShopSeitenDatenRüstung[aktiv_seite - 1].items[i].i_dmg));
						LebensPunkteText.setString(std::to_string(vItemShopSeitenDatenRüstung[aktiv_seite - 1].items[i].i_leben));
						MagiePunkteText.setString(std::to_string(vItemShopSeitenDatenRüstung[aktiv_seite - 1].items[i].i_magie));
						break;
					case 2:
						ItemNameText.setColor(vItemShopSeitenDatenWeapon[aktiv_seite - 1].items[i].cItemColor);
						ItemNameText.setString(osm::convertEnumToString(vItemShopSeitenDatenWeapon[aktiv_seite - 1].items[i].i_rare) +
												vItemShopSeitenDatenWeapon[aktiv_seite - 1].items[i].i_name);
						
						DamageText.setString(std::to_string(vItemShopSeitenDatenWeapon[aktiv_seite - 1].items[i].i_dmg));
						LebensPunkteText.setString(std::to_string(vItemShopSeitenDatenWeapon[aktiv_seite - 1].items[i].i_leben));
						MagiePunkteText.setString(std::to_string(vItemShopSeitenDatenWeapon[aktiv_seite - 1].items[i].i_magie));
						break;
					case 3:
						ItemNameText.setColor(vItemShopSeitenDatenSchild[aktiv_seite - 1].items[i].cItemColor);
						ItemNameText.setString(osm::convertEnumToString(vItemShopSeitenDatenSchild[aktiv_seite - 1].items[i].i_rare) +
							vItemShopSeitenDatenSchild[aktiv_seite - 1].items[i].i_name);

						DamageText.setString(std::to_string(vItemShopSeitenDatenSchild[aktiv_seite - 1].items[i].i_dmg));
						LebensPunkteText.setString(std::to_string(vItemShopSeitenDatenSchild[aktiv_seite - 1].items[i].i_leben));
						MagiePunkteText.setString(std::to_string(vItemShopSeitenDatenSchild[aktiv_seite - 1].items[i].i_magie));
						break;
					case 4:
						ItemNameText.setColor(vItemShopSeitenDatenSpezial[aktiv_seite - 1].items[i].cItemColor);
						ItemNameText.setString(osm::convertEnumToString(vItemShopSeitenDatenSpezial[aktiv_seite - 1].items[i].i_rare) +
							vItemShopSeitenDatenSpezial[aktiv_seite - 1].items[i].i_name);

						DamageText.setString(std::to_string(vItemShopSeitenDatenSpezial[aktiv_seite - 1].items[i].i_dmg));
						LebensPunkteText.setString(std::to_string(vItemShopSeitenDatenSpezial[aktiv_seite - 1].items[i].i_leben));
						MagiePunkteText.setString(std::to_string(vItemShopSeitenDatenSpezial[aktiv_seite - 1].items[i].i_magie));
						break;
					default:
						ItemNameText.setString("Error");
						break;
					}
					ItemShopHover = true;

				}
			}

			for (auto i = 0; i < 4; i++)
			{
				if (rectangle[i].getGlobalBounds().contains(vMousePosition) && iAktivItemShopHintergrund != i+1)
				{
					if (!pState->getItemShopCapMenuStatus())
					{
						iAktivItemShopHintergrund = i+1;
						aktiv_seite = 1;
						ItemShopSeiteNeuErstellen();
					}
					else if (pState->getItemShopCapMenuStatus())
					{
						iAktivItemShopHintergrund = i+1;
						aktiv_seite = 1;
						ItemShopSeiteNeuErstellen();
					}
				}
			}

			if (pItemShopSprites[8]->getGlobalBounds().contains(vMousePosition) && !pState->getItemShopCapMenuStatus())
			{
				iAktivItemShopHintergrund = 1;
				aktiv_seite = 1;
				ItemShopSeiteNeuErstellen();
				pState->setItemShopCapMenuStatus(true);
			}
			else if (pItemShopSprites[8]->getGlobalBounds().contains(vMousePosition) && pState->getItemShopCapMenuStatus())
			{
				iAktivItemShopHintergrund = 1;
				aktiv_seite = 1;
				ItemShopSeiteNeuErstellen();
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

			if (osm::sprite_pressed(pItemShopSprites[5], vMousePosition) && aktiv_seite >= 2)
			{
				aktiv_seite--;
				pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[0]->getPosition());
				ItemShopSeiteNeuErstellen();
			}
			else if (osm::sprite_pressed(pItemShopSprites[6], vMousePosition) && seiten[iAktivItemShopHintergrund] > aktiv_seite)
			{
				aktiv_seite++;
				pItemShopItemSprites[30]->setPosition(pItemShopItemSprites[0]->getPosition());
				ItemShopSeiteNeuErstellen();
			}
		}
	}
	
	void verkäufer::fülleSeitenMitItems()
	{
		int iSchleifenBuffer = 1;
		while (iSchleifenBuffer < 5)
		{
			switch (iSchleifenBuffer)
			{
			case 1:
				vItemShopDaten = item_gen->items(GAMESTRUCTS::item_class::ARMOR);
				break;
			case 2:
				vItemShopDaten = item_gen->items(GAMESTRUCTS::item_class::WEAPON);
				break;
			case 3:
				vItemShopDaten = item_gen->items(GAMESTRUCTS::item_class::SCHILD);
				break;
			case 4:
				vItemShopDaten = item_gen->items(GAMESTRUCTS::item_class::SPECIAL);
				break;
			default:
				vItemShopDaten = item_gen->items(GAMESTRUCTS::item_class::ARMOR);
				break;
			}

			std::cout << "TEST:  SIZE OF VECTOR " << vItemShopDaten.size() << std::endl;
			int size = vItemShopDaten.size() - 1;
			seiten[iSchleifenBuffer] = size / iItemShopMaxItemProSeite + 1;

			if (vItemShopDaten[0].i_texture == vItemShopDaten[1].i_texture && vItemShopDaten[0].i_texture == vItemShopDaten[2].i_texture && vItemShopDaten[0].i_texture == vItemShopDaten[3].i_texture)
			{
				osm::call("Error");
			}
#ifdef TEST_MODUS
			for (int n = 0; n<vItemShopDaten.size()-1; n++) {
				for (int m = n + 1; m<vItemShopDaten.size(); m++) {
					if (vItemShopDaten[n].i_texture == vItemShopDaten[m].i_texture) {
						std::swap(vItemShopDaten[n].i_texture, vItemShopDaten[m].i_texture);
					}
				}
			}
#endif // TEST_MODUS

			for (auto i = 0; i < seiten[iSchleifenBuffer]; i++)
			{
				GAMESTRUCTS::item_site buffer = {};
				if (size >= iItemShopMaxItemProSeite)
				{
					buffer.items_per_site = iItemShopMaxItemProSeite;
					for (auto i = 0; i < iItemShopMaxItemProSeite; i++)
					{
						buffer.items.push_back(vItemShopDaten[vItemShopDaten.size() - 1]);
						vItemShopDaten.pop_back();
					}
					size -= iItemShopMaxItemProSeite;
				}
				else
				{
					buffer.items_per_site = size;
					for (auto i = 0; i < size; i++)
					{
						buffer.items.push_back(vItemShopDaten[vItemShopDaten.size() - 1]);
						vItemShopDaten.pop_back();
					}
				}
				switch (iSchleifenBuffer)
				{
				case 1:
					vItemShopSeitenDatenRüstung.push_back(buffer);
					break;
				case 2:
					vItemShopSeitenDatenWeapon.push_back(buffer);
					break;
				case 3:
					vItemShopSeitenDatenSchild.push_back(buffer);
					break;
				case 4:
					vItemShopSeitenDatenSpezial.push_back(buffer);
					break;
				default:
					vItemShopSeitenDatenRüstung.push_back(buffer);
					break;
				}
			}
			size = 0;
			vItemShopDaten.clear();
			item_gen->deleteItemList();
			iSchleifenBuffer++;
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
			rw->draw(SeitenText);
			rw->draw(DamageText);
			rw->draw(LebensPunkteText);
			rw->draw(MagiePunkteText);
			rw->draw(ItemNameText);

			rw->draw(*pVorschauBildSprite);


			switch (iAktivItemShopHintergrund)
			{
			case 1:
				for (auto i = 0; i < vItemShopSeitenDatenRüstung[aktiv_seite-1].items_per_site; i++)
				{
					rw->draw(*pItemShopItemSprites[i]);
					rw->draw(*pItemShopItemSprites[i + 15]);
				}
				break;
			case 2:
				for (auto i = 0; i < vItemShopSeitenDatenWeapon[aktiv_seite - 1].items_per_site; i++)
				{
					rw->draw(*pItemShopItemSprites[i]);
					rw->draw(*pItemShopItemSprites[i + 15]);
				}
				break;
			case 3:
				for (auto i = 0; i < vItemShopSeitenDatenSchild[aktiv_seite - 1].items_per_site; i++)
				{
					rw->draw(*pItemShopItemSprites[i]);
					rw->draw(*pItemShopItemSprites[i + 15]);
				}
				break;
			case 4:
				for (auto i = 0; i < vItemShopSeitenDatenSpezial[aktiv_seite - 1].items_per_site; i++)
				{
					rw->draw(*pItemShopItemSprites[i]);
					rw->draw(*pItemShopItemSprites[i + 15]);
				}
				break;
			default:
				break;
			}
			if (ItemShopHover)
			{
				rw->draw(*pItemShopItemSprites[30]);
			}
		}
	}

	void verkäufer::ItemShopSeiteNeuErstellen()
	{
		SeitenText.setString("Seite " + std::to_string(aktiv_seite) + " von " + std::to_string(seiten[iAktivItemShopHintergrund]));
		pVorschauBildSprite->setTexture(KlarTexture);
		DamageText.setString("");
		LebensPunkteText.setString("");
		MagiePunkteText.setString("");
		ItemNameText.setString("");
		ItemShopHover = false;
	}
}