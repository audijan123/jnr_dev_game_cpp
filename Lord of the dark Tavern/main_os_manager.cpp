#include "main_os_manager.hpp"
using namespace std;

namespace osm
{
	

	void call(const string &text)
	{
		cout << text << endl;
	}

	int si(const string &text)
	{
		return stoi(text);
	}

	uint8_t sB(const string &text)
	{
		return static_cast<uint8_t>(stoi(text));
	}

	void t_s_ms(const short &ms)
	{
		this_thread::sleep_for(chrono::milliseconds(ms));
	}


}