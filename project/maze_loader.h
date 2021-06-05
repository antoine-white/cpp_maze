#include <array>
#include <vector>
#include <string>

/**
	\brief Use to load some predifined mazes.
	
	It's not really part of the game on itself. It's a helper so 
	the user does not have to set up his own mazes.
	\note You have to have the 4 files in the same directory to use it
*/
class maze_loader
{
	maze_loader() {};
	static std::array<std::pair<std::string,std::string>, 4> mazes;
public:
	static std::vector<std::string> available_mazes();
	static std::string maze_as_str(size_t index);
};
