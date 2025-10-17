#pragma once

#include <string>
#include <vector>

namespace sf
{
	class Shape;
}

namespace engine
{
	namespace graphics
	{
		class ShapeList
		{
		public:
			// Container type for storing pointers to SFML shapes.
			using Shapes = std::vector<sf::Shape*>;

			// Loads shapes from an XML file with the given name.
			// Returns true on success, false on parse or file error.
			bool load(const std::string& name);

			// Returns a const reference to the internal list of shapes.
			const Shapes& getShapes() const;

		private:
			// Stores pointers to dynamically allocated SFML shapes.
			Shapes shapes;
		};
	}
}
