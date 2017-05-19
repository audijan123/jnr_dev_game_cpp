#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "datenbank_main.hpp"
#include "tavern_main.hpp"
#include "main_base.hpp"
#include "sfSpriteGen.hpp"
#include "riftBrowser.hpp"
#include "taverne.hpp"

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
	void ui_render();
	void m_frametime();
	void life_clouds();
	void dungeon_rotate();
	void exit_btn();


	main_data			*pDatenbank;
	JGE::main_base		*pResourcenManager;
	//Hauptfenster
	sf::RenderWindow	*pHauptFenster;
	sf::Texture			*pHintergrundTexture;
	sf::Sprite			*pHintergrundSprite;

	sf::Event			*pHauptEvent; // Haupt event
	sf::Clock			*pHauptUhr; // Hauptuhr

	//Umwelt
	// Himmel Objecte
	sf::Texture			*pHimmelTexture;
	sf::Sprite			*pHimmelSprite;

	// Wolken Objecte
	sf::Texture			*pWolkenTexture;
	sf::Sprite			*pWolkeSprite;
	sf::Sprite			*pWolkeZweiSprite;

	//Rift Portal und Hover
	sf::Texture			*pRiftPortalTexture;
	sf::Sprite			*pRiftPortalSprite;
	//Hover
	sf::Texture			*pRiftPortalTextureHover;
	sf::Texture			*pRiftSkyTextureHover;

	// Menu Button Objecte
	sf::Texture			*pMenuButtonTexture[10];
	sf::Sprite			*pMenuButtonSprite[10];

	// Tavernen Systeme
	tavern_main			*pTaverne;

	//Pointer erschaffung für den Rift Manager
	//dungeon_manager		*pRiftManager;
	GMS::riftBrowser    *pRiftBrowser;

	// Erstellung der Taverne
	GMS::taverne		*pTavern;
	

	//Erschaffung des Sprite genartors
	JGE::SpriteGen		*pSpriteErsteller;

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
	bool bPortalHover			= false;

	

};
