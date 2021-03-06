#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "datenbank.hpp"
#include "main_base.hpp"
#include "sfSpriteGen.hpp"
#include "riftBrowser.hpp"
#include "taverne.hpp"
#include "himmel.hpp"
#include "uiElemente.hpp"
#include "hintergrund.hpp"
#include "mainStateManager.hpp"

class main_frame
{
public:
	const std::string sTitel = "Lord of the dark Tavern";
	

	main_frame(std::string const &pfad);
	~main_frame();
	void run();
	void enviroment_t();
	void datenbank_t();

private:
	// Funktion
	void quit();
	void render();
	void update();
	void handleEvents();
	void m_frametime();


	JGE::main_base			*pResourcenManager;

	//Hintergrund
	GMS::hintergrund		*pHintergrund;

	sf::Clock				*pHauptUhr; // Hauptuhr


	//Pointer erschaffung f�r den Rift Manager
	//dungeon_manager		*pRiftManager;
	GMS::riftBrowser		*pRiftBrowser;

	// Erstellung der Taverne
	GMS::taverne			*pTavern;
	
	//Himmel erstellung
	GMS::himmel				*pHimmel;

	//ui erstellung
	GMS::ui					*pUi;


	// Ende der Pointer Liste

	//Floats
	float fUpdateZeit			= 0;
	float fUpdateZeitWarte		= 0;
	float fUpdateZeitMax		= 1.0f/60.f;


	

};
