#include "dungeon_manager.hpp"


dungeon_manager::dungeon_manager(const int &m_power,std::string path,const std::vector<sf::Image*> &image)

{

	m_path = path;
	load_dungeon();

	/// Random Dungeon Generator
	std::time_t now = std::time(0);
	boost::random::mt19937 rng{ static_cast<std::uint32_t>(now) };;
	/// Dungeon Range Floor länge für LevelGrad
	if (m_power == 1)
	{
		floors = rng() % 20 + 10; ////  10 - 30
	}
	else if (m_power == 2)
	{
		floors = rng() % 50 + 30; //// 30 - 80
	}
	else if (m_power == 3)
	{
		floors = rng() % 120 + 60; //// 60 - 180
	}
	else if (m_power > 3)
	{
		floors = rng() % 120 + 60+ 30*(m_power-2); //// 60 - 180
	}
	

	diffculty = m_power;
	/// Enviroment Auswürfeln und setzen 

	enviro_id = rng() % 12;
	std::cout<< floors <<std::endl;
	for(int i = 0; i<image.capacity();i++)
		std::cout << image[i] << " : " << i<<std::endl;

	fill_dungeon(image);

	dungeon_atkiv = true;
}


dungeon_manager::~dungeon_manager()
{

	while (0 != mob_ebene_1.size())
	{
		delete mob_ebene_1[mob_ebene_1.size() - 1];
		mob_ebene_1[mob_ebene_1.size() - 1] = nullptr;
		mob_ebene_1.pop_back();
	}
	mob_ebene_1.clear();
	delete pfont;
	pfont = nullptr;
}

void dungeon_manager::load_dungeon()
{

}

void dungeon_manager::fill_dungeon(const std::vector<sf::Image*> &image)
{
	pfont = new sf::Font;
	pfont->loadFromFile(m_path + "DATA/resource/dungeon.ttf");



	int mobs_ebene = 0;
	for (int i = 0; i <= floors; i++)
	{
		std::time_t times = std::time(0);
		boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;
		mobs_ebene = dev()*(i+1) % 9 + 1;

		for (uint16_t u = mobs_ebene; u != 0; u--)
		{
			std::time_t fro = std::time(0);
			boost::random::mt19937 dev_test{ static_cast<std::uint32_t>(fro) };;
			//std::cout <<"Vector:" << image.capacity() << std::endl;
			uint16_t rnd = dev_test()*u % (image.capacity()-2);
			std::cout << rnd << std::endl;
			mob_ebene_1.push_back(new mob(u-1,*image[rnd], diffculty, 0, pfont, *image[image.capacity()-1]));
		}



		mob_per_floor.push_back(mobs_ebene);
		std::cout << mobs_ebene << " : " << i << " : "  << mob_per_floor[i] << std::endl;
		//49 173 168 163 84 79
		
			
			
	
			
			
			
	}

}




void dungeon_manager::render(sf::RenderWindow *rw)
{
	if (dungeon_atkiv)
	{
		for (int i_p = 0; i_p < mob_per_floor[floor_a]; i_p++)
		{
			//std::cout << i_p << std::endl;
			mob_ebene_1[i_p]->render(rw);
		}
	}
}
