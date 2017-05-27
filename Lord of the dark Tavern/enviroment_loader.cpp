#include "enviroment_loader.hpp"

extern JGE::SpriteGen *pSpriteErsteller;

enviroment_loader::enviroment_loader()
{
	//Lade Texturen
	for (auto i = 0; i < 14; i++)
	{
		HintergrundTexturen[i] = pSpriteErsteller->erstelle_texture("dgb" + std::to_string(i + 10));
	}

	// Erstelle Sprites
	pHintergrund					= new sf::Sprite;
	pHimmel							= new sf::Sprite;
	pWolken							= new sf::Sprite;

	pHintergrund->setScale(scale);
	pHimmel->setScale(scale);	
	pWolken->setScale(scale);

	pHimmel->setTexture(HintergrundTexturen[13]);
	pWolken->setTexture(HintergrundTexturen[12]);



}
enviroment_loader::~enviroment_loader()
{
	delete pHimmel;
	pHimmel = nullptr;

	delete pWolken;
	pWolken = nullptr;

	delete pHintergrund;
	pHintergrund = nullptr;

}


void enviroment_loader::render_enviro(int id, sf::RenderWindow *rw)
{
	if (id >= 10)
	{
		// Wenn eine Area die Wolken benötigt gerendert wird
		rw->draw(*pHimmel);
		rw->draw(*pWolken);
	}

	pHintergrund->setTexture(HintergrundTexturen[id]);
	rw->draw(*pHintergrund);
}