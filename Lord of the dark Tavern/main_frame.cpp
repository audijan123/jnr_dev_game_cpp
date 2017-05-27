#include "main_frame.hpp"

////GLOBAL DEFINIERT

sf::Event				*pHauptEvent; // Haupt event
sf::Vector2f			vMain = { 1280.f,768.f };
std::string				sPfad;
sf::Vector2f			vMousePosition;
sf::Font				*pFont;
GDB::datenbank			*pDatenbank;
JGE::mainStateManager	*pState;

//Hauptfenster
sf::RenderWindow		*pHauptFenster;

//Erschaffung des Sprite genartors
JGE::SpriteGen			*pSpriteErsteller;

////ENDE GLOBAL

main_frame::main_frame(const std::string &pfad) 
{
	sPfad = pfad.substr(0, pfad.length() - 27);
	pFont = new sf::Font;
	pFont->loadFromFile(sPfad + "DATA/resource/dungeon.ttf");

	pHauptEvent = new sf::Event; //Erstelle pHauptEvent

	 //pHauptFenster erstellen
	pHauptFenster = new sf::RenderWindow(sf::VideoMode(
											static_cast<unsigned int>(vMain.x),
											static_cast<unsigned int>(vMain.y),
											64),
											sTitel,
											sf::Style::Default);


	pState						= new JGE::mainStateManager(); // Erstelle State Manager
	pDatenbank					= new GDB::datenbank(); // Erstelle Datenbank Klasse //
	pResourcenManager			= new JGE::main_base(); // Erstelle Resourchen Manager //
	pSpriteErsteller			= new JGE::SpriteGen(pResourcenManager);
	pRiftBrowser				= new GMS::riftBrowser(pResourcenManager->get_mob_size_short()-1);
	pTavern						= new GMS::taverne();
	pHimmel						= new GMS::himmel();
	pHintergrund				= new GMS::hintergrund(pHimmel, pRiftBrowser);

	pHauptUhr					= new sf::Clock; // Erstelle Uhr

	pUi							= new GMS::ui(pRiftBrowser);

	pHauptFenster->setFramerateLimit(60);
	pHauptFenster->setVerticalSyncEnabled(true);


	// Ende Konstruktor
}

main_frame::~main_frame()
{
}


void main_frame::run()
{
	while (pState->getProgrammStatus())
	{
		m_frametime();
		fUpdateZeitWarte += fUpdateZeit;
		if (fUpdateZeitWarte >= fUpdateZeitMax)
		{
			update();
			fUpdateZeitWarte = 0.f;
		}

		handleEvents();
		render();
		quit();
	}
}

void main_frame::quit()
{
	if (!pState->getProgrammStatus())
	{
		pHauptFenster->close();
		exit(0x001996);
	}
}

void main_frame::update()
{
	if (!pState->getPauseStatus())
	{
		vMousePosition = { sf::Mouse::getPosition().x - 8.f - pHauptFenster->getPosition().x ,
			sf::Mouse::getPosition().y - 32.f - pHauptFenster->getPosition().y };
	}

	if (!pState->getRiftBrowserStatus())
	{
		pTavern->update();
	}
	
	pRiftBrowser->update();


}
void main_frame::handleEvents()
{
	while (pHauptFenster->pollEvent(*pHauptEvent))
	{
		if (pHauptEvent->type == sf::Event::Closed)
		{
			pState->setProgrammStatus(false);
		}
		else if (pHauptEvent->type == sf::Event::MouseButtonPressed && pHauptFenster->hasFocus() 
			&& pHauptEvent->key.code == sf::Mouse::Button::Left)
		{
			pRiftBrowser->eventRiftBrowser(vMousePosition);
			pUi->update();
			pTavern->eventTaverne();
			pHintergrund->event();
		}
		else if (pHauptEvent->type == sf::Event::KeyPressed && pHauptFenster->hasFocus())
		{
			pTavern->keyEvent(pHauptEvent);
		}
	}
}

void main_frame::render()
{
	pHauptFenster->clear();
	if (pState->getHauptFensterStatus())
	{
		pHintergrund->render(pHauptFenster);
	}
	pTavern->render(pHauptFenster);
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
void main_frame::enviroment_t()
{
	osm::t_s_ms(60);
	pHauptFenster->setTitle(sTitel + " FPS: " + std::to_string(static_cast<int>(1.f / fUpdateZeit)));
	pHintergrund->update(fUpdateZeit);

}

/////DATENBANK SYSTEM Thread 2 //////////
void main_frame::datenbank_t()
{
	pDatenbank->run();
}