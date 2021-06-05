#include "grid.h"
#include <iostream>
#include <sstream>

core::grid::grid(std::string s)
{
	parse_string(s);
}

//TODO split code
void core::grid::parse_string(std::string s)
{
	std::vector<std::string> lines;
	std::stringstream stream(s);
	std::string line;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}

	std::vector<std::vector<grid_cell*>> _grid;

	for (std::string line : lines) {
		std::vector<grid_cell*> curr_line;
		std::vector<char> cells(line.begin(), line.end());
		for (char cell : cells) {
			if (cell == '#')
				curr_line.push_back(new wall());
			else 
				curr_line.push_back(new empty_cell());
		}
		_grid.push_back(curr_line);
		curr_line.clear();
	}

	delete _grid[0][0];
	_grid[0][0] = new start_cell();
	delete _grid[_grid.size() - 1 ][_grid[0].size() - 1];
	_grid[_grid.size() - 1][_grid[0].size() - 1] = new end_cell();

	for (size_t i = 0; i < _grid.size(); i++) {
		for (size_t j = 0; j < _grid[i].size(); j++) {
			if (i != 0)
				_grid[i][j]->_up = _grid[i - 1][j];
			if (i != (_grid.size() - 1))
				_grid[i][j]->_down = _grid[i + 1][j];
			if (j != 0)
				_grid[i][j]->_left = _grid[i][j - 1];
			if (j != _grid[i].size() -1)
				_grid[i][j]->_right = _grid[i][j + 1];
			
		}
	}
	start = static_cast<core::start_cell*>(_grid[0][0]);
	end = static_cast<core::end_cell*>(_grid[_grid.size() - 1][_grid[0].size() - 1]);
	current = _grid[0][0];
}


core::grid::operator std::string () const
{

	std::string res_string;

	std::vector<grid_cell*> firsts;
	grid_cell* curr = start;
	while (curr != nullptr) {
		firsts.push_back(curr);
		curr = curr->_down;
	}

	for (grid_cell* f : firsts) {
		curr = f;
		while (curr != nullptr) {
			res_string += *curr;
			curr = curr->_right;
		}
		res_string += "\n";
	}

	return res_string;
}

void core::grid::tag_curr()
{
	auto tmp = static_cast<core::empty_cell*>(current);
	tmp->tag();
	tagged.push_back(tmp);
}

void core::grid::untag_all()
{
	for (core::empty_cell* tag : tagged)
		tag->tag();
}

bool core::grid::is_goable(core::Directions D) const
{
	return core::isGoable(current->next(D));
}

bool core::grid::move(core::Directions D)
{
	core::grid_cell* next = current->next(D);

	if (core::isGoable(next))
	{
		current = next;
		return true;
	}
	else
	{
		return false;
	}
}

bool core::grid::is_end() const
{
	return current == end;
}

void core::grid::reset()
{
	current = static_cast<grid_cell*>(start);
}



/*
int main() {
	std::string s;
	s += "   #######\n";
	s += "         #\n";
	s += "####  ####\n";
	s += "#     #  #\n";
	s += "#  #  #  #\n";
	s += "#  #      \n";
	s += "#######   ";

	core::grid g(s);
	std::string ss = g;
	std::cout << ss << std::endl;
}
*/