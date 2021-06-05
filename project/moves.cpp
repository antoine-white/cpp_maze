#include "moves.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <utility>
#include <array>

/******* HELPER FUNCTIONS **********/
int go_in_direction(core::player* p, core::Directions D)
{
	int nb = 0;
	while (p->is_goable(D))
	{
		p->move(D);
		p->tag();
		nb++;
	}
	return nb;
}

core::tracer go_straight_turn(
	core::player* p,
	core::Directions direction,
	std::function<core::Directions(core::Directions)> next_direction
)
{
	core::tracer t;
	int ite = 0;
	std::array < std::pair<core::Directions,int>, 2 > last_two = { 
		std::make_pair(direction, -1),
		std::make_pair(direction, -1) 
	};
	while (!p->is_end()
		&& ite < core::move_handler::max_ite)
	{
		int vec = go_in_direction(p, direction);
		if (vec > 0)
		{
			if (direction == last_two[0].first && vec == last_two[0].second)
				break;
			last_two[0] = last_two[1];
			last_two[1] = std::make_pair(direction,vec);
			for (int i = 0; i < vec; i++)
				t.add_to_trace(direction);
			ite++;
		}

		direction = next_direction(direction);
	}
	t.has_find_end(p->is_end());
	return t;
}
/**************************************/


core::move_handler::move_handler(std::string s, std::function<tracer(core::player*)> f)
	: _name(s), fun(f)
{
}

core::tracer core::move_handler::operator()(core::player* p) const
{
	return fun(p);
}

std::string core::move_handler::name() const
{
	return _name;
}

core::move_handler core::move_handler::turn_left = core::move_handler(
	std::string("tout droit puis gauche"),
	[](core::player* p) -> core::tracer {
		return go_straight_turn(
			p,
			core::Directions::DOWN,
			[](core::Directions direction) -> core::Directions {
				switch (direction)
				{
				case core::Directions::LEFT:
					direction = core::Directions::DOWN;
					break;
				case core::Directions::RIGHT:
					direction = core::Directions::UP;
					break;
				case core::Directions::UP:
					direction = core::Directions::LEFT;
					break;
				case core::Directions::DOWN:
					direction = core::Directions::RIGHT;
					break;
				default:
					break;
				}
				return direction;
			}
		);
	}
);

core::move_handler core::move_handler::turn_right = core::move_handler(
	std::string("tout droit puis droite"),
	[](core::player* p) -> core::tracer {
		return go_straight_turn(
			p,
			core::Directions::RIGHT,
			[](core::Directions direction) -> core::Directions {
				switch (direction)
				{
				case core::Directions::LEFT:
					direction = core::Directions::UP;
					break;
				case core::Directions::RIGHT:
					direction = core::Directions::DOWN;
					break;
				case core::Directions::UP:
					direction = core::Directions::RIGHT;
					break;
				case core::Directions::DOWN:
					direction = core::Directions::LEFT;
					break;
				default:
					break;
				}
				return direction;
			}
		);
	}
);

core::move_handler core::move_handler::stairs = core::move_handler(
	std::string("Escalier"),
	[](core::player* p) -> core::tracer {
		tracer t;
		bool right = true;
		bool stuck = false;
		while (!p->is_end() && !stuck) {
			p->tag();
			auto reacheable = std::make_pair(
				p->is_goable(core::Directions::DOWN),
				p->is_goable(core::Directions::RIGHT)
			);
			if ((!reacheable.first) && (!reacheable.second)) {
				stuck = true;
			}
			else {
				core::Directions dir = core::Directions::RIGHT;
				if (right) {
					if (reacheable.second) {
						right = false;
					}
					else {
						dir = core::Directions::DOWN;
					}
				}
				else {
					if (reacheable.first)
					{
						dir = core::Directions::DOWN;
						right = true;
					}
				}
				p->move(dir);
				t.add_to_trace(dir);
			}
		}
		t.has_find_end(p->is_end());
		return t;
	}
);

core::move_handler core::move_handler::random = core::move_handler(
	std::string("Aleatoire a chaque embranchement"),
	[](core::player* p) -> core::tracer {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		int ite = 0;
		tracer t;
		while (!p->is_end()
			&& ite < core::move_handler::max_ite)
		{
			std::array<core::Directions, 4> arr = {
				core::Directions::DOWN,
				core::Directions::UP,
				core::Directions::LEFT,
				core::Directions::RIGHT,
			};
			std::vector<core::Directions> possibilities;
			for (auto dir : arr)
				if (p->is_goable(dir))
					possibilities.push_back(dir);

			core::Directions dirr = possibilities[std::rand() % possibilities.size()];
			p->move(dirr);
			p->tag();
			ite++;
			t.add_to_trace(dirr);
		}
		t.has_find_end(p->is_end());
		return t;
	}
);