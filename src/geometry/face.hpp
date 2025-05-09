#ifndef FACE_HPP
#define FACE_HPP

#include <array>

#include "../math/vector.hpp"
#include "../render/color.hpp"

#define VERTICES 4

class Face {
	private:
		Vector center;
		std::array<Vector, VERTICES> vertices;
		Color color;
		float distance_from_camera = 0.0f;
		char orientation;

	public:
		Face();
		Face(Vector center, float edge_length, Color color, char orientation);
		Vector &get_center_point();
		std::array<Vector, VERTICES> &get_vertices();
		Color get_color() const { return color; }
		void set_distance_from_camera(float distance);
		float get_distance_from_camera() const;
		char get_orientation() const { return orientation; }
};

#endif // FACE_HPP
