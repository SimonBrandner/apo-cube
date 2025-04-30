#ifndef SIDE_HPP
#define SIDE_HPP

#include "../math/vector.hpp"
#include "../render/color.hpp"
#include <array>

#define SIDE_SUBDIVISION 4

class Side {
	private:
		Vector center;
		Vector corners[4];
		Color color;

	public:
		Side(Vector center, float side_length, Color color, char orientation,
		 int i, int j);
		Vector get_center_point() const;
		std::array<Vector, 4> get_corners() const;
		Color get_color() const { return color; }
};

#endif //SIDE_HPP
