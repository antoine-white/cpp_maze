#include "grid_cell.h"
#include "moves.h"
core::grid_cell::grid_cell(char c, bool a) : character(c), _accesible(a)
{
	_left = nullptr;
	_down = nullptr;
	_up = nullptr;
	_right = nullptr;
}

core::grid_cell::~grid_cell(){
	delete _left;
	delete _down;
	delete _up;
	delete _right;
}

core::grid_cell::operator std::string () const
{
	std::string s(1, character);
	return s;
}

const bool core::grid_cell::accessible() const
{
	return _accesible;
}


core::grid_cell* core::grid_cell::next(core::Directions D) {
	switch (D)
	{
	case core::Directions::LEFT:
		return _left;
	case core::Directions::RIGHT:
		return _right;
	case core::Directions::UP:
		return _up;
	case core::Directions::DOWN:
		return _down;
	default: 
		return nullptr;
	}
}

bool core::isGoable(core::grid_cell* cell)
{
	return cell != nullptr && cell->accessible();
}

void core::empty_cell::tag()
{
	character = core::DEFAULT_CHAR_EMPTY_TAGGED;

}

void core::empty_cell::untag()
{
	character = core::DEFAULT_CHAR_EMPTY;
}
