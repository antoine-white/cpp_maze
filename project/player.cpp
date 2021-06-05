#include "player.h"
#include "moves.h"



void core::player::load_grid(grid* g)
{
	curr_grid = g;
}

bool core::player::is_goable(core::Directions D) const
{
	return curr_grid->is_goable(D);
}

bool core::player::move(core::Directions D)
{
	return curr_grid->move(D);
}

bool core::player::is_end() const
{
	return curr_grid->is_end();
}

void core::player::tag()
{
	curr_grid->tag_curr();
}

