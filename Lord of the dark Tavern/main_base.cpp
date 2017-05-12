#include "main_base.hpp"

namespace JNR
{
	main_base::main_base(std::string path)
		: main_path(path)
	{
		std::ifstream texture_file{ main_path + "DATA/63287zruihgfiuz7zfuiwh27482zuhdbjfg783u2hg.jnr", std::ifstream::binary };
		std::vector<char> buffer;

		if (texture_file) {
			// get length of file:
			texture_file.seekg(0, texture_file.end);
			const auto length = texture_file.tellg();
			if (!length) {
				std::cerr << "Cannot load zero byte texture file" << std::endl;
			}
			buffer.resize(length); // reserve space

			texture_file.seekg(0, texture_file.beg);

			auto start = &*buffer.begin();
			texture_file.read(start, length);
			texture_file.close();
		}
		else {
			std::cerr << "Could not open texture file" << std::endl;
		}

		struct memory_data d_memory_data;
		buffer.erase(buffer.begin());
		buffer[1] += -1;
		buffer[2] += -1;
		buffer[3] += -1;
		d_memory_data.t = buffer;
		char buffer_char[5];
		for (int u = 0; u < 5; u++)
		{
			buffer_char[u] = (buffer[buffer.size() - (7 - u)]-1);
		}
		std::string dev_buffer(buffer_char);
		d_memory_data.name = dev_buffer;
		d_data.push_back(d_memory_data);
		buffer.clear();
		

	}

	main_base::~main_base()
	{
	}

	std::vector<char> main_base::get_memory_data(std::string name) const
	{
		for (int i = 0; i < d_data.size(); i++)
		{
			if (d_data[i].name == name)
			{
				return d_data[i].t;
			}
		}

		
	}
}