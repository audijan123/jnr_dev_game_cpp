#include "enviroment_loader.hpp"

enviroment_loader::enviroment_loader(std::string path)
{
	enviroment[0] = new sf::Texture;
	enviroment[1] = new sf::Texture;
	enviroment[2] = new sf::Texture;
	enviroment[3] = new sf::Texture;
	enviroment[4] = new sf::Texture;
	enviroment[5] = new sf::Texture;
	enviroment[6] = new sf::Texture;
	enviroment[7] = new sf::Texture;
	enviroment[8] = new sf::Texture;
	enviroment[9] = new sf::Texture;
	enviroment[10] = new sf::Texture;
	enviroment[11] = new sf::Texture;
	enviroment[12] = new sf::Texture;
	enviroment[13] = new sf::Texture;

	pSprite = new sf::Sprite;
	pSprite->setScale(2.67f, 2.85f);
	pSky = new sf::Sprite;
	pSky->setScale(2.67f, 2.85f);
	pClouds = new sf::Sprite;
	pClouds->setScale(2.67f, 2.85f);

	enviroment[0]->loadFromFile(path + "DATA/dungeon/arena/back.png");
	enviroment[1]->loadFromFile(path + "DATA/dungeon/cave/back.png");
	enviroment[2]->loadFromFile(path + "DATA/dungeon/cave/back_c.png");
	enviroment[3]->loadFromFile(path + "DATA/dungeon/fire/back.png");
	enviroment[4]->loadFromFile(path + "DATA/dungeon/fire/back_c.png");
	enviroment[5]->loadFromFile(path + "DATA/dungeon/ice/back.png");
	enviroment[6]->loadFromFile(path + "DATA/dungeon/ice/back_c.png");
	enviroment[10]->loadFromFile(path + "DATA/dungeon/top/top.png");
	enviroment[11]->loadFromFile(path + "DATA/dungeon/top/top_c.png");
	enviroment[7]->loadFromFile(path + "DATA/dungeon/void/back.png");
	enviroment[8]->loadFromFile(path + "DATA/dungeon/void/back_c.png");
	enviroment[9]->loadFromFile(path + "DATA/dungeon/water/back.png");
	enviroment[12]->loadFromFile(path + "DATA/dungeon/top/mountain_clouds.png");
	enviroment[13]->loadFromFile(path + "DATA/dungeon/top/mountains.png");

	pSky->setTexture(*enviroment[13]);
	pClouds->setTexture(*enviroment[12]);


}
enviroment_loader::~enviroment_loader()
{

}

sf::Texture enviroment_loader::get_texture(int id)
{
	return *enviroment[id];
}

void enviroment_loader::render_enviro(int id, sf::RenderWindow *render)
{
	//std::cout << id << std::endl;

	if (id == 10)
	{
		render->draw(*pSky);
		render->draw(*pClouds);
	}
	pSprite->setTexture(*enviroment[id]);
	render->draw(*pSprite);
}