#ifndef SIDE_HPP
#define SIDE_HPP

#include "../math/vector.hpp"
#include "../render/color.hpp"
#include <array>

#define SIDE_SUBDIVISION 4

class Side {
	private:
		Vector center;
		std::array<Vector, 4> vertices;
		Color color;

	public:
		Side();
		Side(Vector center, float edge_length, Color color, char orientation,
			 int i, int j);
		Vector get_center_point() const;
		std::array<Vector, 4> &get_vertices();
		Color get_color() const { return color; }
};

#endif // SIDE_HPP
