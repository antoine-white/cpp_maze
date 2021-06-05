
#include "maze_loader.h"
#include "fstream"

std::vector<std::string> maze_loader::available_mazes()
{
	std::vector<std::string> tmp;
	for (auto m : mazes)
		tmp.push_back(m.first);
	return tmp;
}

std::string maze_loader::maze_as_str(size_t index)
{
	if (index >= mazes.size())
		throw std::range_error("index must be at or under " + (mazes.size() - 1));
	std::ifstream file;
	try {
		file.open(mazes[index].second);
	}
	catch (const std::ifstream::failure& e) {
		throw std::exception(e.what());
	}
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return content;
}

std::array<std::pair<std::string, std::string>, 4> maze_loader::mazes = {
	make_pair(std::string("labyrinthe 3x3"),std::string("lab_3_x_3.txt")),
	make_pair(std::string("labyrinthe 10x10"),std::string("lab_10_x_10_1.txt")),
	make_pair(std::string("labyrinthe 10x10"),std::string("lab_10_x_10_2.txt")),
	make_pair(std::string("labyrinthe 50x50"),std::string("lab_50_x_50.txt")),
};
