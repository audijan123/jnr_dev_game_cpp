#pragma once

#include <string>
#include <iostream>
#include <thread>

namespace osm
{
	void call(const std::string &text);
	int si(const std::string &text);
	uint8_t sB(const std::string &text);

	void t_s_ms(const short &ms);
}
