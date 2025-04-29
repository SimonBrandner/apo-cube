#ifndef SIDE_HPP
#define SIDE_HPP

#include "../math/vector.hpp"
#include "../render/color.hpp"
#include <array>

class Side {
	private:
		Vector middle_vector;
		Vector corners[4];
		Color color;

	public:
		Side(Vector middle, float side_length);
		Vector get_middle_vector() const;
		std::array<Vector, 4> get_corners() const;
};

#endif //SIDE_HPP
