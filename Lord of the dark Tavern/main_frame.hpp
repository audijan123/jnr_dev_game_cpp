#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "datenbank_main.hpp"
#include "tavern_main.hpp"
#include "main_base.hpp"
#include "sfSpriteGen.hpp"
#include "riftBrowser.hpp"
#include "taverne.hpp"
#include "himmel.hpp"
#include "uiElemente.hpp"
#include "hintergrund.hpp"

class main_frame
{
public:
	sf::Vector2f main = { 1280.f,768.f };
	std::string sTitel = "Lord of the dark Tavern";

	main_frame(std::string const &pfad);
	~main_frame();
	void run();
	void enviroment();
	void datenbank();

private:
	// Funktion
	void quit();
	void render();
	void update();
	void handleEvents();
	void m_frametime();


	main_data			*pDatenbank;
	JGE::main_base		*pResourcenManager;
	//Hauptfenster
	sf::RenderWindow	*pHauptFenster;
	//Hintergrund
	GMS::hintergrund	*pHintergrund;

	sf::Event			*pHauptEvent; // Haupt event
	sf::Clock			*pHauptUhr; // Hauptuhr

	// Tavernen Systeme
	tavern_main			*pTaverne;

	//Pointer erschaffung für den Rift Manager
	//dungeon_manager		*pRiftManager;
	GMS::riftBrowser    *pRiftBrowser;

	// Erstellung der Taverne
	GMS::taverne		*pTavern;
	
	//Himmel erstellung
	GMS::himmel			*pHimmel;

	//Erschaffung des Sprite genartors
	JGE::SpriteGen		*pSpriteErsteller;

	//ui erstellung
	GMS::ui				*pUi;


	// Ende der Pointer Liste

	//Floats
	float fUpdateZeit			= 0;
	float fUpdateZeitWarte		= 0;
	float fUpdateZeitMax		= 1.0f/60.f;


	std::string	 mainPfad;
	sf::Vector2f vMousePosition;

	// Bools
	bool bRun					= true;
	bool bHauptFenster			= true;
	bool bPausenMenu			= false;
	bool bTaverne				= false;

	

};
