#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "dungeon_manager.hpp"
#include "enviroment_loader.hpp"
#include "datenbank_main.hpp"
#include "tavern_main.hpp"
#include "main_base.hpp"

class main_frame
{
public:
	sf::Vector2f main = { 1280.f,768.f };

	main_frame(std::string const &pfad);
	~main_frame();
	void run();
	void enviroment();
	void datenbank();

	double get_main_scale() { return m_scale; };

private:
	// Funktion
	void quit();
	void render();
	void update();
	void handleEvents();
	void tavern_hover();
	void ui_render();
	void m_frametime();
	void life_clouds();
	void dungeon_rotate();
	void exit_dungeon();
	void exit_btn();
	void hardcore_btn();
	void diffi_btn();
	void update_diffi();
	void btn_exit_dungeon();
	void btn_go_dungeon();
	void create_dungeon_browser();


	main_data			*pDatenbank;
	JNR::main_base		*pResourcenManager;
	//Hauptfenster
	sf::RenderWindow	*pHauptFenster;
	sf::Texture			*pHintergrundTexture;
	sf::Sprite			*pHintergrundSprite;

	sf::Event			*pHauptEvent; // Haupt event
	sf::Clock			*pHauptUhr; // Hauptuhr

	sf::Font			*pSchriftArt; //schriftart

	// Tavern Object
	sf::Texture			*pTaverneTexture;
	sf::Sprite			*pTaverneSprite;
	// Tavern Hover
	sf::Texture			*pTaverneTextureHover;
	sf::Sprite			*pTaverneSpriteHover;

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


	// Rift Menu //
	sf::Texture			*pRiftMenuTexture[7];
	sf::Sprite			*pRiftMenuSprite[7];

	sf::Text			*pRiftMenuTitel;
	sf::Text			*pRiftMenuSchwierigkeit;
	sf::Text			*pRiftMenuText;
	sf::Text			*pRiftMenuTextHoch;


	//Hintergrund Lader
	enviroment_loader	*pHintergrundLader;

	// Tavernen Systeme
	tavern_main			*pTaverne;

	//Pointer erschaffung für den Rift Manager
	dungeon_manager		*pRiftManager;

	// Ende der Pointer Liste

	//Fps Anzeige
	sf::Text			textFps;

	//Floats
	float m_frame_time = 0;
	float m_scale = 1;
	float btn[10] = { main.x - 50.f,main.x - 100.f,main.x - 150.f,0.f,50.f };


	//ints
	uint16_t difficulty = 1;
	uint8_t  iRiftBrowserSchriftGröße = 21;


	std::string	 mainPfad;
	sf::Vector2f vMousePosition;

	// Bools
	bool bRun = true;
	bool bHauptFenster = true;
	bool bPausenMenu = false;
	bool bRift = false;
	bool bTaverne = false;
	bool bRiftBrowser = false;
	bool bRfitBrowserHardcore = false;
	bool bTavernHover = false;
	bool bPortalHover = false;

	

};
