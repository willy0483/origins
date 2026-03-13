#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace config
{
	extern const unsigned int width;
	extern const unsigned int height;
	extern const std::string title;

	namespace assets
	{
		extern const std::string wall;
		extern const std::string face;
	} // namespace assets

} // namespace config

#endif
