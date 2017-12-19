#include "riftBrowser.hpp"

extern sf::Vector2f	vMain;
extern sf::Font	*pFont;
extern JGE::SpriteGen *pSpriteErsteller;
extern JGE::mainStateManager *pState;
extern sf::Vector2f vMousePosition;

namespace GMS
{
	riftBrowser::riftBrowser(const uint16_t& iMobS)
	{

		for (auto i_l = 0; i_l < 7; i_l++)
		{
			pRiftMenuSprite[i_l] = new sf::Sprite;
			pRiftMenuTexture[i_l] = pSpriteErsteller->erstelle_texture("dbtn" + std::to_string(i_l + 1));
		}

		pRiftMenuTitel = new sf::Text;
		pRiftMenuSchwierigkeit = new sf::Text;
		pRiftMenuText = new sf::Text;
		pRiftMenuTextHoch = new sf::Text;


		// Texturen Setzen
		pRiftMenuSprite[0]->setTexture(pRiftMenuTexture[0]); // Diffi Pfeil
		pRiftMenuSprite[1]->setTexture(pRiftMenuTexture[0]); // Diffi Pfeil Andere Reichtung
		pRiftMenuSprite[2]->setTexture(pRiftMenuTexture[1]); // close btn
		pRiftMenuSprite[3]->setTexture(pRiftMenuTexture[2]); // start btn
		pRiftMenuSprite[4]->setTexture(pRiftMenuTexture[4]); // check true
		pRiftMenuSprite[5]->setTexture(pRiftMenuTexture[5]); //bg
		pRiftMenuSprite[6]->setTexture(pRiftMenuTexture[6]); // bg text


		// Setze Schriftart
		pRiftMenuTitel->setFont(*pFont);
		pRiftMenuSchwierigkeit->setFont(*pFont);
		pRiftMenuText->setFont(*pFont);
		pRiftMenuTextHoch->setFont(*pFont);


		// Setze Positions
		pRiftMenuSprite[5]->setPosition(vMain.x / 2.f, vMain.y / 2.f);

		pRiftMenuSprite[5]->setOrigin(pRiftMenuTexture[5].getSize().x / 2.f,
			pRiftMenuTexture[5].getSize().y / 2.f);

		pRiftMenuSprite[1]->setPosition(pRiftMenuSprite[5]->getPosition().x - 167.f,
			pRiftMenuSprite[5]->getPosition().y - 50.f);

		pRiftMenuSprite[0]->setPosition(pRiftMenuSprite[1]->getPosition().x,
			pRiftMenuSprite[1]->getPosition().y + 30.f);

		pRiftMenuSprite[2]->setPosition(pRiftMenuSprite[5]->getPosition().x + 155.f,
			pRiftMenuSprite[5]->getPosition().y - 132.f);

		pRiftMenuSprite[3]->setPosition(pRiftMenuSprite[5]->getPosition().x - 75.f,
			pRiftMenuSprite[5]->getPosition().y + 70.f);

		pRiftMenuTextHoch->setPosition(pRiftMenuSprite[5]->getPosition().x + 15.f,
			pRiftMenuSprite[5]->getPosition().y - 90.f);

		pRiftMenuSprite[4]->setPosition(pRiftMenuTextHoch->getPosition().x + 50.f,
			pRiftMenuTextHoch->getPosition().y + 30.f);

		pRiftMenuTitel->setPosition(pRiftMenuSprite[5]->getPosition().x - 82.f,
			pRiftMenuSprite[5]->getPosition().y - 130.f);

		pRiftMenuSchwierigkeit->setPosition(pRiftMenuSprite[5]->getPosition().x - 127.f,
			pRiftMenuSprite[5]->getPosition().y - 50.f);


		//Setze Skalierungen
		pRiftMenuSprite[0]->setScale(1.3f, 1.f);
		pRiftMenuSprite[1]->setScale(1.3f, -1.f);
		pRiftMenuSprite[5]->setScale(1.5f, 1.5f);

		//Schriftgröße
		pRiftMenuTitel->setCharacterSize(iRiftBrowserSchriftGröße);
		pRiftMenuSchwierigkeit->setCharacterSize(iRiftBrowserSchriftGröße);
		pRiftMenuTextHoch->setCharacterSize(iRiftBrowserSchriftGröße);

		//Setze Text
		pRiftMenuTitel->setString("Dungeon Browser");
		pRiftMenuSchwierigkeit->setString("Leicht");
		pRiftMenuTextHoch->setString("Hardcore Mode");


		for (auto m = iMobS; m != 0; m--)
		{
			p_texture.push_back(pSpriteErsteller->erstelle_texture_mob(m));
		}
	}

	riftBrowser::~riftBrowser()
	{
	}


	void riftBrowser::update()
	{
		if (difficulty == 1)
		{
			pRiftMenuSchwierigkeit->setString("Leicht");
		}
		else if (difficulty == 2)
		{
			pRiftMenuSchwierigkeit->setString("Normal");
		}
		else if (difficulty == 3)
		{
			pRiftMenuSchwierigkeit->setString("Schwer");
		}
		else if (difficulty == 4)
		{
			pRiftMenuSchwierigkeit->setString("Mystisch");
		}
		else if (difficulty > 4)
		{
			pRiftMenuSchwierigkeit->setString("Mystisch " + std::to_string(difficulty - 4));
		}


	}
	void riftBrowser::eventRiftBrowser()
	{
		if (pState->getRiftBrowserStatus())
		{
			if (osm::sprite_pressed(pRiftMenuSprite[4], vMousePosition))
			{
				if (bRfitBrowserHardcore)
				{
					bRfitBrowserHardcore = false;
					pRiftMenuSprite[4]->setTexture(pRiftMenuTexture[4]);
				}
				else if (!bRfitBrowserHardcore)
				{
					bRfitBrowserHardcore = true;
					pRiftMenuSprite[4]->setTexture(pRiftMenuTexture[3]);
				}
			}
			else if (osm::sprite_pressed(pRiftMenuSprite[0], vMousePosition) && difficulty > 1)
			{
				difficulty--;
			}
			else if (osm::sprite_pressed(pRiftMenuSprite[1], vMousePosition))
			{
				difficulty++;
			}
			else if (osm::sprite_pressed(pRiftMenuSprite[2], vMousePosition))
			{
				hide();
			}
			else if (osm::sprite_pressed(pRiftMenuSprite[3], vMousePosition))
			{
				pState->setRiftBrowserStatus(false);
				pRiftManager = new dungeon_manager(difficulty, p_texture);
				pState->setRiftStatus(true);
				pState->setHauptFensterStatus(false);
			}
		}

	}
	void riftBrowser::render(sf::RenderWindow *rw)
	{
		if (pState->getRiftBrowserStatus())
		{
			rw->draw(*pRiftMenuSprite[5]);
			rw->draw(*pRiftMenuSprite[2]);
			rw->draw(*pRiftMenuTitel);
			rw->draw(*pRiftMenuSprite[0]);
			rw->draw(*pRiftMenuSprite[1]);
			rw->draw(*pRiftMenuSprite[3]);
			rw->draw(*pRiftMenuSprite[4]);
			rw->draw(*pRiftMenuSchwierigkeit);
			rw->draw(*pRiftMenuTextHoch);
		}
		else if (pState->getRiftStatus())
		{
			pRiftManager->render(rw);
		}
	}

	void  riftBrowser::deleteRift()
	{
		if (pState->getRiftStatus())
		{
			pState->setRiftStatus(false);
			pState->setHauptFensterStatus(true);
			delete pRiftManager;
			pRiftManager = nullptr;
		}
		else
		{
			osm::call("Kein Rift vorhanden");
		}
	}

	void  riftBrowser::show()
	{
		pState->setRiftBrowserStatus(true);
	}
	void  riftBrowser::hide()
	{
		pState->setRiftBrowserStatus(false);
	}



}
