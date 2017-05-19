#include "riftBrowser.hpp"

namespace GMS
{
	riftBrowser::riftBrowser(JGE::main_base *s,const sf::Vector2f& main, const std::string& mainPfad)
		: pResourcenManager(s), mainPfad(mainPfad)
	{
		// Erstelle Schriftart
		pSchriftArt = new sf::Font;
		pSchriftArt->loadFromFile(mainPfad + "DATA/resource/dungeon.ttf");

		for (auto i_l = 0; i_l < 7; i_l++)
		{
			pRiftMenuTexture[i_l] = new sf::Texture;
			pRiftMenuSprite[i_l] = new sf::Sprite;

			pRiftMenuTexture[i_l]->loadFromMemory
			(
				&pResourcenManager->get_memory_data("dbtn" + std::to_string(i_l + 1))[0],
				pResourcenManager->get_memory_data("dbtn" + std::to_string(i_l + 1)).size()
			);
		}

		pRiftMenuTitel = new sf::Text;
		pRiftMenuSchwierigkeit = new sf::Text;
		pRiftMenuText = new sf::Text;
		pRiftMenuTextHoch = new sf::Text;


		// Texturen Setzen
		pRiftMenuSprite[0]->setTexture(*pRiftMenuTexture[0]); // Diffi Pfeil
		pRiftMenuSprite[1]->setTexture(*pRiftMenuTexture[0]); // Diffi Pfeil Andere Reichtung
		pRiftMenuSprite[2]->setTexture(*pRiftMenuTexture[1]); // close btn
		pRiftMenuSprite[3]->setTexture(*pRiftMenuTexture[2]); // start btn
		pRiftMenuSprite[4]->setTexture(*pRiftMenuTexture[4]); // check true
		pRiftMenuSprite[5]->setTexture(*pRiftMenuTexture[5]); //bg
		pRiftMenuSprite[6]->setTexture(*pRiftMenuTexture[6]); // bg text


		// Setze Schriftart
		pRiftMenuTitel->setFont(*pSchriftArt);
		pRiftMenuSchwierigkeit->setFont(*pSchriftArt);
		pRiftMenuText->setFont(*pSchriftArt);
		pRiftMenuTextHoch->setFont(*pSchriftArt);


		// Setze Positions
		pRiftMenuSprite[5]->setPosition(main.x / 2.f, main.y / 2.f);

		pRiftMenuSprite[5]->setOrigin(pRiftMenuTexture[5]->getSize().x / 2.f,
			pRiftMenuTexture[5]->getSize().y / 2.f);

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
	void riftBrowser::eventRiftBrowser(sf::Vector2f vMousePosition)
	{
		if (bRiftBrowser && !bRift)
		{
			if (osm::sprite_pressed(pRiftMenuSprite[4], vMousePosition))
			{
				if (bRfitBrowserHardcore)
				{
					bRfitBrowserHardcore = false;
					pRiftMenuSprite[4]->setTexture(*pRiftMenuTexture[4]);
				}
				else if (!bRfitBrowserHardcore)
				{
					bRfitBrowserHardcore = true;
					pRiftMenuSprite[4]->setTexture(*pRiftMenuTexture[3]);
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
				bRiftBrowser = false;
				pRiftManager = new dungeon_manager(difficulty, mainPfad, pResourcenManager);
				bRift = true;
			}
		}

	}
	void riftBrowser::render(sf::RenderWindow *rw)
	{
		if (bRiftBrowser)
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
		else if (bRift)
		{
			pRiftManager->render(rw);
		}
	}

	void  riftBrowser::deleteRift()
	{
		if (bRift)
		{
			bRift = false;
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
		bRiftBrowser = true;
	}
	void  riftBrowser::hide()
	{
		bRiftBrowser = false;
	}



}
