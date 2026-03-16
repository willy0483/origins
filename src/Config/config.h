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
		namespace path
		{
			extern const std::string wall;
			extern const std::string face;
		} // namespace path
	} // namespace assets

} // namespace config

#endif
