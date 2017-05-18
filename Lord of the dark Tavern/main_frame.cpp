#include "main_frame.hpp"

main_frame::main_frame(const std::string &pfad) 
	: mainPfad(pfad.substr(0, pfad.length() - 27))
{
	pDatenbank					= new main_data(mainPfad); // Erstelle Datenbank Klasse //
	pResourcenManager			= new JNR::main_base(mainPfad); // Erstelle Resourchen Manager //


	//pHauptFenster erstellen
	pHauptFenster				= new sf::RenderWindow(sf::VideoMode(main.x,main.y, 64), 
													   "Lord of the dark Travern",
													   sf::Style::Default);

	pHauptFenster->setFramerateLimit(60);
	pHauptFenster->setVerticalSyncEnabled(true);


	//Hintergrund für das pHauptFenster erstellen und einen sf::Sprite zuordnen
	pHintergrundTexture			= new sf::Texture;
	pHintergrundSprite			= new sf::Sprite;

	pHintergrundTexture->loadFromMemory(&pResourcenManager->get_memory_data("backg")[0],
										pResourcenManager->get_memory_data("backg").size());
	pHintergrundSprite->setTexture(*pHintergrundTexture);

	pHintergrundSprite->setScale(2.67f, 2.85f);


	pHauptEvent					= new sf::Event; //Erstelle pHauptEvent
	pHauptUhr					= new sf::Clock; // Erstelle Uhr


	// Erstelle Schriftart
	pSchriftArt					= new sf::Font;
	pSchriftArt->loadFromFile(mainPfad + "DATA/resource/dungeon.ttf");


	//Erstellen des "Tavernen" Objectes + zugehöriges Hover effekt
	//Object
	pTaverneTexture				= new sf::Texture;
	pTaverneSprite				= new sf::Sprite;

	pTaverneTexture->loadFromMemory(&pResourcenManager->get_memory_data("taver")[0], 
									pResourcenManager->get_memory_data("taver").size());
	pTaverneSprite->setTexture(*pTaverneTexture);

	pTaverneSprite->setPosition(0, 230);
	pTaverneSprite->setScale(2.67f, 2.85f);

	//Hover
	pTaverneTextureHover		= new sf::Texture;
	pTaverneSpriteHover			= new sf::Sprite;

	pTaverneTextureHover->loadFromMemory(&pResourcenManager->get_memory_data("taveh")[0], 
										 pResourcenManager->get_memory_data("taveh").size());
	pTaverneSpriteHover->setTexture(*pTaverneTextureHover);

	pTaverneSpriteHover->setPosition(95.f, 335.f);
	pTaverneSpriteHover->setScale(2.67f, 2.85f);



	// Himmel Object
	pHimmelTexture				= new sf::Texture;
	pHimmelSprite				= new sf::Sprite;

	pHimmelTexture->loadFromMemory(&pResourcenManager->get_memory_data("skybb")[0], 
									pResourcenManager->get_memory_data("skybb").size());
	pHimmelSprite->setTexture(*pHimmelTexture);

	pHimmelSprite->setScale(2.67f, 2.85f);


	// Wolken Objecte
	pWolkenTexture				= new sf::Texture;
	pWolkeSprite				= new sf::Sprite;
	pWolkeZweiSprite			= new sf::Sprite;

	pWolkenTexture->loadFromFile(mainPfad + "DATA/resource/clouds.png");
	pWolkeSprite->setTexture(*pWolkenTexture);
	pWolkeZweiSprite->setTexture(*pWolkenTexture);

	pWolkeSprite->setScale(1.5f, 1.2f);
	pWolkeZweiSprite->setScale(1.5f, 1.2f);
	pWolkeZweiSprite->setPosition(0 - 1200, 0);


	// Hintergrundbilder Laden ///
	pHintergrundLader			= new enviroment_loader(mainPfad);


	// Rift Portal und Rift Portal Hover//
	//Object
	pRiftPortalTexture			= new sf::Texture;
	pRiftPortalSprite			= new sf::Sprite;

	pRiftPortalTexture->loadFromFile(mainPfad + "DATA/resource/portal.png");
	pRiftPortalSprite->setTexture(*pRiftPortalTexture);

	pRiftPortalSprite->setOrigin(pRiftPortalTexture->getSize().x / 2.f, pRiftPortalTexture->getSize().y / 2.f);
	pRiftPortalSprite->setPosition(1100, 390);
	pRiftPortalSprite->setScale(0.5, 0.5);

	//Hover
	pRiftPortalTextureHover		= new sf::Texture;
	pRiftSkyTextureHover		= new sf::Texture;

	pRiftPortalTextureHover->loadFromFile(mainPfad + "DATA/resource/portal_hover.png");
	pRiftSkyTextureHover->loadFromFile(mainPfad + "DATA/resource/sky_hover.png");


	// Menu Button Objecte
	for (auto i = 0; i < 3; i++)
	{
		pMenuButtonTexture[i]	= new sf::Texture;
		pMenuButtonSprite[i]	= new sf::Sprite;

		pMenuButtonTexture[i]->loadFromMemory(&pResourcenManager->get_memory_data("btn", i + 100)[0],
											 pResourcenManager->get_memory_data("btn", i + 100).size());
		pMenuButtonSprite[i]->setTexture(*pMenuButtonTexture[i]);

		pMenuButtonSprite[i]->setPosition(btn[i], btn[3]);
		pMenuButtonSprite[i]->setScale(1.7f, 1.7f);
	}

	// Rift Menu //
	create_dungeon_browser();

	//Laden der Taverne und dessen Funktionen
	pTaverne = new tavern_main(mainPfad, pResourcenManager, main);


	//Fps Anzeige
	textFps.setFont(*pSchriftArt);
	textFps.setString("");

	textFps.setPosition(0, 0);

	// Ende Konstruktor
}

main_frame::~main_frame()
{
}


void main_frame::run()
{
	while (bRun)
	{
		update();
		tavern_hover();
		update_diffi();

		handleEvents();
		render();
		m_frametime();
		quit();
	}
}

void main_frame::quit()
{
	if (!bRun)
	{
		pHauptFenster->close();
		exit(0x001996);
	}
}

void main_frame::update()
{
	if (bPausenMenu == false)
	{
		textFps.setString(std::to_string(static_cast<int>(1.f / m_frame_time)));

		vMousePosition = { sf::Mouse::getPosition().x - 8.f - pHauptFenster->getPosition().x ,
			sf::Mouse::getPosition().y - 32.f - pHauptFenster->getPosition().y };

		pTaverne->update(vMousePosition);
	}


}
void main_frame::handleEvents()
{
	while (pHauptFenster->pollEvent(*pHauptEvent))
	{
		if (pHauptEvent->type == sf::Event::Closed)
		{
			bRun = false;
		}
		if (pHauptEvent->type == sf::Event::KeyPressed && pHauptFenster->hasFocus())
		{
			pTaverne->event_get_key(pHauptEvent);
			if (pHauptEvent->key.code == sf::Keyboard::A)
			{
				std::cout << "event " << std::endl;
			}
			else if (pHauptEvent->key.code == sf::Keyboard::F1)
			{
				pTaverne->test_func();
			}
			else if (pHauptEvent->key.code == sf::Keyboard::F5)
			{
				exit_dungeon();
			}

			
		}
		if (pHauptEvent->type == sf::Event::MouseButtonPressed)
		{
			if (pHauptEvent->key.code == sf::Mouse::Button::Left)
			{
				if (bTavernHover && !bRift && !bTaverne)
				{
					bTaverne = true;
					bRift = false;
					bHauptFenster = false;
				}			
				else if (bRiftBrowser && !bRift && !bTaverne)
				{
					hardcore_btn();
					diffi_btn();
					btn_exit_dungeon();
					btn_go_dungeon();
				}
				else if (bTaverne)
				{
					pTaverne->event();
				}
				exit_btn();
			}
		}
	}
}

void main_frame::render()
{
	pHauptFenster->clear();
	if (bRift)
	{
		if (!pRiftManager->check_dungeon()) {
			pHauptFenster->draw(*pHimmelSprite);
			if (!bPortalHover) {
				pHauptFenster->draw(*pWolkeSprite);
				pHauptFenster->draw(*pWolkeZweiSprite);
			}
			pHauptFenster->draw(*pHintergrundSprite);
			pHauptFenster->draw(*pTaverneSprite);
			pHauptFenster->draw(*pRiftPortalSprite);
			if (bTavernHover)
			{
				pHauptFenster->draw(*pTaverneSpriteHover);
			}
		}
		else if (pRiftManager->check_dungeon())
		{
			pHintergrundLader->render_enviro(pRiftManager->enviroment_id(), pHauptFenster);
			if(!bHauptFenster)
				pRiftManager->render(pHauptFenster);
		}
	}
	else if (bHauptFenster)
	{
		pHauptFenster->draw(*pHimmelSprite);
		if (!bPortalHover) {
			pHauptFenster->draw(*pWolkeSprite);
			pHauptFenster->draw(*pWolkeZweiSprite);
		}
		pHauptFenster->draw(*pHintergrundSprite);
		pHauptFenster->draw(*pTaverneSprite);
		pHauptFenster->draw(*pRiftPortalSprite);
		if (bTavernHover)
		{
			pHauptFenster->draw(*pTaverneSpriteHover);
		}
	}
	else if (bTaverne)
	{
		pTaverne->render(pHauptFenster);
	}
	ui_render();
	pHauptFenster->draw(textFps);
	pHauptFenster->display();
}

void main_frame::ui_render()
{
	for (auto i = 0; i < 3; i++)
	{
		pHauptFenster->draw(*pMenuButtonSprite[i]);
	}


	if (bRiftBrowser && !bRift && !bTaverne)
	{
		pHauptFenster->draw(*pRiftMenuSprite[5]);
		pHauptFenster->draw(*pRiftMenuSprite[2]);
		pHauptFenster->draw(*pRiftMenuTitel);
		pHauptFenster->draw(*pRiftMenuSprite[0]);
		pHauptFenster->draw(*pRiftMenuSprite[1]);
		pHauptFenster->draw(*pRiftMenuSprite[3]);
		pHauptFenster->draw(*pRiftMenuSprite[4]);
		pHauptFenster->draw(*pRiftMenuSchwierigkeit);
		pHauptFenster->draw(*pRiftMenuTextHoch);
	}


}

void main_frame::m_frametime()
{
	m_frame_time = pHauptUhr->getElapsedTime().asSeconds();
	pHauptUhr->restart();
}

void main_frame::tavern_hover()
{
	if (pTaverneSprite->getGlobalBounds().contains(vMousePosition) && !bRiftBrowser && !bTaverne && !bRift)
	{
		bTavernHover = true;
	}
	else
	{
		bTavernHover = false;
	}
}

void main_frame::life_clouds()
{
	if (pWolkeSprite->getPosition().x >= main.x)
	{
		pWolkeSprite->setPosition(0- main.x, pWolkeSprite->getPosition().y);
	}
	else if (pWolkeSprite->getPosition().x <  main.x)
	{
		pWolkeSprite->setPosition(pWolkeSprite->getPosition().x + 30 * m_frame_time, pWolkeSprite->getPosition().y);
	}
	if (pWolkeZweiSprite->getPosition().x >= main.x)
	{
		pWolkeZweiSprite->setPosition(0 - main.x, pWolkeZweiSprite->getPosition().y);
	}
	else if (pWolkeZweiSprite->getPosition().x < main.x)
	{
		pWolkeZweiSprite->setPosition(pWolkeZweiSprite->getPosition().x + 30 * m_frame_time, pWolkeZweiSprite->getPosition().y);
	}
}

void main_frame::dungeon_rotate()
{
	pRiftPortalSprite->rotate(0.5);

	if (pRiftPortalSprite->getGlobalBounds().contains(vMousePosition) && !bTaverne &&
		pHauptEvent->key.code == sf::Mouse::Button::Left || bRiftBrowser)
	{
		pHintergrundSprite->setTexture(*pRiftPortalTextureHover);
		pHimmelSprite->setTexture(*pRiftSkyTextureHover);


		bPortalHover = true;
		bRiftBrowser = true;
	}
	else
	{
		pHintergrundSprite->setTexture(*pHintergrundTexture);
		pHimmelSprite->setTexture(*pHimmelTexture);

		bPortalHover = false;
	}
	

}

void main_frame::exit_dungeon()
{
	bRift = false;
	delete pRiftManager;
	pRiftManager = nullptr;
	bHauptFenster = true;
}

void main_frame::exit_btn()
{
	if (osm::sprite_pressed(pMenuButtonSprite[0], vMousePosition))
	{
		if (bRift)
		{
			exit_dungeon();
		}
		else if (bHauptFenster)
		{
			bRun = false;
		}
		else if (bTaverne && !pTaverne->o_menu())
		{
			bTaverne = false;
			bHauptFenster = true;
		}
	}
}

void main_frame::hardcore_btn()
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
}

void main_frame::diffi_btn()
{
	//p_Dungeon_Browser[1]
	if (osm::sprite_pressed(pRiftMenuSprite[0], vMousePosition) && difficulty > 1)
	{
		difficulty--;
	}
	else if (osm::sprite_pressed(pRiftMenuSprite[1], vMousePosition))
	{
		difficulty++;
	}
}

void main_frame::update_diffi()
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
		pRiftMenuSchwierigkeit->setString("Mystisch " + std::to_string(difficulty-4));
	}
}

void main_frame::btn_exit_dungeon()
{
	if (osm::sprite_pressed(pRiftMenuSprite[2], vMousePosition))
	{
		bRiftBrowser = false;
	}
}

void main_frame::btn_go_dungeon()
{
	if (osm::sprite_pressed(pRiftMenuSprite[3], vMousePosition))
	{
		bRiftBrowser = false;
		pRiftManager = new dungeon_manager(difficulty, mainPfad, pResourcenManager);
		bRift = true;
		bHauptFenster = false;
	}
}

void main_frame::create_dungeon_browser()
{
	for (auto i_l = 0; i_l < 7; i_l++)
	{
		pRiftMenuTexture[i_l]		 = new sf::Texture;
		pRiftMenuSprite[i_l]		 = new sf::Sprite;

		pRiftMenuTexture[i_l]->loadFromMemory
		(
			&pResourcenManager->get_memory_data("dbtn" + std::to_string(i_l + 1))[0],
			pResourcenManager->get_memory_data("dbtn" + std::to_string(i_l + 1)).size()
		);
	}

	pRiftMenuTitel					 = new sf::Text;
	pRiftMenuSchwierigkeit			 = new sf::Text;
	pRiftMenuText					 = new sf::Text;
	pRiftMenuTextHoch				 = new sf::Text;




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
	pRiftMenuSprite[5]->setOrigin(pRiftMenuTexture[5]->getSize().x / 2.f,
								  pRiftMenuTexture[5]->getSize().y / 2.f);

	pRiftMenuSprite[5]->setPosition(main.x / 2.f, main.y / 2.f);

	pRiftMenuTitel->setPosition(pRiftMenuSprite[5]->getPosition().x - 82.f,
								pRiftMenuSprite[5]->getPosition().y - 130.f);

	pRiftMenuSchwierigkeit->setPosition(pRiftMenuSprite[5]->getPosition().x - 127.f,
										pRiftMenuSprite[5]->getPosition().y - 50.f);

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





/////Enviroment SYSTEM Thread 1 //////////

void main_frame::enviroment()
{
	osm::t_s_ms(20);
	life_clouds();
	dungeon_rotate();
}



/////DATENBANK SYSTEM Thread 2 //////////


void main_frame::datenbank()
{
	pDatenbank->run();
}