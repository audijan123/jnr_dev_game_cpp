#include "main_frame.hpp"

main_frame::main_frame(const std::string &pfad) 
	: mainPfad(pfad.substr(0, pfad.length() - 27))
{
	pDatenbank					= new main_data(mainPfad); // Erstelle Datenbank Klasse //
	pResourcenManager			= new JGE::main_base(mainPfad); // Erstelle Resourchen Manager //
	pSpriteErsteller			= new JGE::SpriteGen(pResourcenManager);
	pRiftBrowser = new GMS::riftBrowser(pResourcenManager, main, mainPfad);


	//pHauptFenster erstellen
	pHauptFenster				= new sf::RenderWindow(sf::VideoMode(
														static_cast<unsigned int>(main.x),
														static_cast<unsigned int>(main.y), 
														64),
													   sTitel,
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


	// Rift Portal und Rift Portal Hover//
	//Object
	pRiftPortalSprite = pSpriteErsteller->erstelle_sprite("porta", true, sf::Vector2f(1100.f, 390.f), sf::Vector2f(0.5f, 0.5f));

	//Hover
	pRiftPortalTextureHover		= new sf::Texture;
	pRiftSkyTextureHover		= new sf::Texture;

	pRiftPortalTextureHover->loadFromFile(mainPfad + "DATA/resource/portal_hover.png");
	pRiftSkyTextureHover->loadFromFile(mainPfad + "DATA/resource/sky_hover.png");


	// Menu Button Objecte
	for (uint16_t i = 0; i < 3; i++)
	{
		pMenuButtonSprite[i] = pSpriteErsteller->erstelle_sprite("btn", false, sf::Vector2f(main.x - (50 * (i + 1)), 0.f),
																sf::Vector2f(1.7f, 1.7f), i + 100);
	}


	//Laden der Taverne und dessen Funktionen
	pTaverne = new tavern_main(mainPfad, pResourcenManager, main);

	// Ende Konstruktor
}

main_frame::~main_frame()
{
}


void main_frame::run()
{
	while (bRun)
	{
		m_frametime();
		fUpdateZeitWarte += fUpdateZeit;
		if (fUpdateZeitWarte >= fUpdateZeitMax)
		{
			update();
			fUpdateZeitWarte = 0.f;
		}

		pRiftBrowser->update();
		tavern_hover();



		handleEvents();
		render();
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
		}
		if (pHauptEvent->type == sf::Event::MouseButtonPressed)
		{
			pRiftBrowser->eventRiftBrowser(vMousePosition);
			if (pHauptEvent->key.code == sf::Mouse::Button::Left)
			{
				if (bTavernHover)
				{
					bTaverne = true;
					bHauptFenster = false;
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
	if (bHauptFenster)
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
	pHauptFenster->display();
}

void main_frame::ui_render()
{

	pRiftBrowser->render(pHauptFenster);
	for (auto i = 0; i < 3; i++)
	{
		pHauptFenster->draw(*pMenuButtonSprite[i]);
	}


}

void main_frame::m_frametime()
{
	fUpdateZeit = pHauptUhr->getElapsedTime().asSeconds();
	pHauptUhr->restart();
}

void main_frame::tavern_hover()
{
	if (pTaverneSprite->getGlobalBounds().contains(vMousePosition) &&
		!pRiftBrowser->getRiftBrowserStatus() && !bTaverne &&
		!pRiftBrowser->getRiftStatus())
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
		pWolkeSprite->setPosition(pWolkeSprite->getPosition().x + 60 * fUpdateZeit, pWolkeSprite->getPosition().y);
	}
	if (pWolkeZweiSprite->getPosition().x >= main.x)
	{
		pWolkeZweiSprite->setPosition(0 - main.x, pWolkeZweiSprite->getPosition().y);
	}
	else if (pWolkeZweiSprite->getPosition().x < main.x)
	{
		pWolkeZweiSprite->setPosition(pWolkeZweiSprite->getPosition().x + 60 * fUpdateZeit, pWolkeZweiSprite->getPosition().y);
	}
}

void main_frame::dungeon_rotate()
{
	pRiftPortalSprite->rotate(1.3f);

	if (pRiftPortalSprite->getGlobalBounds().contains(vMousePosition) && !bTaverne &&
		pHauptEvent->key.code == sf::Mouse::Button::Left && !pRiftBrowser->getRiftBrowserStatus() &&
		!pRiftBrowser->getRiftStatus())
	{
		pHintergrundSprite->setTexture(*pRiftPortalTextureHover);
		pHimmelSprite->setTexture(*pRiftSkyTextureHover);

		bPortalHover = true;
		pRiftBrowser->show();
	}
	else if(!pRiftBrowser->getRiftBrowserStatus())
	{
		pHintergrundSprite->setTexture(*pHintergrundTexture);
		pHimmelSprite->setTexture(*pHimmelTexture);

		bPortalHover = false;
	}
	

}

void main_frame::exit_btn()
{
	if (osm::sprite_pressed(pMenuButtonSprite[0], vMousePosition))
	{
		if (pRiftBrowser->getRiftStatus())
		{
			pRiftBrowser->deleteRift();
		}
		else if (bHauptFenster)
		{
			bRun = false;
		}
		else if (pRiftBrowser->getRiftBrowserStatus())
		{
			pRiftBrowser->hide();
		}
		else if (bTaverne && !pTaverne->o_menu())
		{
			bTaverne = false;
			bHauptFenster = true;
		}
	}
}

/////Enviroment SYSTEM Thread 1 //////////
void main_frame::enviroment()
{
	osm::t_s_ms(60);
	pHauptFenster->setTitle(sTitel + " FPS: " + std::to_string(static_cast<int>(1.f / fUpdateZeit)));
	life_clouds();
	dungeon_rotate();
}

/////DATENBANK SYSTEM Thread 2 //////////
void main_frame::datenbank()
{
	pDatenbank->run();
}