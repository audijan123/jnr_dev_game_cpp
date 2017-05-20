#include "main_frame.hpp"

main_frame::main_frame(const std::string &pfad) 
	: mainPfad(pfad.substr(0, pfad.length() - 27))
{
	pDatenbank					= new main_data(mainPfad); // Erstelle Datenbank Klasse //

	pResourcenManager			= new JGE::main_base(mainPfad); // Erstelle Resourchen Manager //
	pSpriteErsteller			= new JGE::SpriteGen(pResourcenManager);

	pRiftBrowser				= new GMS::riftBrowser(pResourcenManager, main, mainPfad);
	pTavern						= new GMS::taverne(pSpriteErsteller);
	pHimmel						= new GMS::himmel(pSpriteErsteller, main);
	pHintergrund				= new GMS::hintergrund(pSpriteErsteller, pRiftBrowser, pHimmel);


	pHauptEvent = new sf::Event; //Erstelle pHauptEvent
	pHauptUhr = new sf::Clock; // Erstelle Uhr

	//Laden der Taverne und dessen Funktionen
	pTaverne					= new tavern_main(mainPfad, pResourcenManager, main);


	pUi							= new GMS::ui(pSpriteErsteller, pRiftBrowser, pTaverne, main);

	//pHauptFenster erstellen
	pHauptFenster				= new sf::RenderWindow(sf::VideoMode(
														static_cast<unsigned int>(main.x),
														static_cast<unsigned int>(main.y), 
														64),
													   sTitel,
													   sf::Style::Default);

	pHauptFenster->setFramerateLimit(60);
	pHauptFenster->setVerticalSyncEnabled(true);


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
		if (!pRiftBrowser->getRiftBrowserStatus())
		{
			pTavern->update(vMousePosition);
		}

		handleEvents();
		render();
		quit();
	}
}

void main_frame::quit()
{
	if (!bRun || !pUi->getbRun())
	{
		pHauptFenster->close();
		exit(0x001996);
	}
}

void main_frame::update()
{

	if (!bPausenMenu)
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
		}
		if (pHauptEvent->type == sf::Event::MouseButtonPressed)
		{
			pRiftBrowser->eventRiftBrowser(vMousePosition);
			if (pHauptEvent->key.code == sf::Mouse::Button::Left)
			{
				pUi->update(vMousePosition, bHauptFenster, bTaverne);
				
				if (!pUi->getTavernStatus() && bTaverne)
				{
					bTaverne = false;
					bHauptFenster = true;
				}
				else if (pTavern->getTavernHover() && bHauptFenster)
				{
					bTaverne = true;
					bHauptFenster = false;
				}
				else if (bTaverne)
				{
					pTaverne->event();
				}

			}
		}
	}
}

void main_frame::render()
{
	pHauptFenster->clear();
	if (bHauptFenster)
	{
		pHintergrund->render(pHauptFenster);
		pTavern->render(pHauptFenster);
	}
	else if (bTaverne)
	{
		pTaverne->render(pHauptFenster);
	}
	pRiftBrowser->render(pHauptFenster);
	pUi->render(pHauptFenster);
	pHauptFenster->display();
}

void main_frame::m_frametime()
{
	fUpdateZeit = pHauptUhr->getElapsedTime().asSeconds();
	pHauptUhr->restart();
}

/////Enviroment SYSTEM Thread 1 //////////
void main_frame::enviroment()
{
	osm::t_s_ms(60);
	pHauptFenster->setTitle(sTitel + " FPS: " + std::to_string(static_cast<int>(1.f / fUpdateZeit)));
	pHintergrund->update(vMousePosition, bTaverne, pHauptEvent, fUpdateZeit);

}

/////DATENBANK SYSTEM Thread 2 //////////
void main_frame::datenbank()
{
	pDatenbank->run();
}