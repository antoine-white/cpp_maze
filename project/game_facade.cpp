#include "game_facade.h"

core::game_facade::game_facade(std::string grid_str) : 
	move_handlers({
	core::move_handler::turn_left,
	core::move_handler::turn_right,
	core::move_handler::stairs,
	core::move_handler::random,
})
{
	
	g = new grid(grid_str);
	p = new player();
	p->load_grid(g);
}

core::game_facade::~game_facade()
{
	delete p;
	delete g;
}

std::vector<std::string> core::game_facade::str_moves_types() const
{
	std::vector<std::string> res;
	for (auto m : core::game_facade::move_handlers)
		res.push_back(m.name());
	return res;
}

std::pair<core::parcour_res, std::string> core::game_facade::move(size_t index)
{
	if (index >= move_handlers.size())
		throw std::range_error("index must be at or under " + (move_handlers.size() - 1));
	if (g == nullptr)
		throw std::exception("Grid not initialized");
	tracer t = move_handlers[index](p);
	g->reset();
	core::parcour_res par = t.get_stats();
	std::string res = *g;
	g->untag_all();
	return std::make_pair(par, res);
}

std::vector<core::parcour_res> core::game_facade::get_stats()
{
	std::vector<core::parcour_res> res;
	for (auto m : move_handlers) {
		res.push_back(m(p).get_stats());
		g->untag_all();
		g->reset();
	}
	return res;
}

std::string core::game_facade::display_grid() const
{
	if (g == nullptr)
		throw std::exception("Grid not initialized");
	else
		return *g;
}

