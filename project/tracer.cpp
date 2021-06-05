#include "tracer.h"
#include <string>

core::tracer::~tracer()
{
	trace.clear();
}

void core::tracer::add_to_trace(Directions d)
{
	trace.push_back(d);
}

void core::tracer::has_find_end(bool b)
{
	has_reach = b;
}


core::parcour_res core::tracer::get_stats() const
{
	core::parcour_res res;
	res.nb_depl = static_cast<int>(trace.size());
	res.has_reach = has_reach;
	return res;
}

core::parcour_res::operator std::string() const 
{
	std::string res = "nombre de deplacement : " + std::to_string(nb_depl);
	if (has_reach) {
		res += "\nA atteint la sortie";
	}
	else {
		res += "\nN'a pas atteint la sortie";
	}

	return res;
}