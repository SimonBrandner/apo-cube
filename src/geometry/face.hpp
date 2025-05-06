#ifndef FACE_HPP
#define FACE_HPP

#include <array>

#include "../math/vector.hpp"
#include "../render/color.hpp"

#define FACE_SUBDIVISION 4

class Face {
	private:
		Vector center;
		std::array<Vector, 4> vertices;
		Color color;

	public:
		Face();
		Face(Vector center, float edge_length, Color color, char orientation,
			 int i, int j);
		Vector get_center_point() const;
		std::array<Vector, 4> &get_vertices();
		Color get_color() const { return color; }
};

#endif // FACE_HPP
