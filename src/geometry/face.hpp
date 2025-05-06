#ifndef FACE_HPP
#define FACE_HPP

#include <array>

#include "../math/vector.hpp"
#include "../render/color.hpp"

#define FACE_SUBDIVISION 64

class Face {
	private:
		Vector center;
		std::array<Vector, 4> vertices;
		Color color;
		float distance_from_camera = 0.0f;

	public:
		Face();
		Face(Vector center, float edge_length, Color color, char orientation,
			 int i, int j);
		Vector &get_center_point();
		std::array<Vector, 4> &get_vertices();
		Color get_color() const { return color; }
		void set_distance_from_camera(float distance);
		float get_distance_from_camera() const;
};

#endif // FACE_HPP
