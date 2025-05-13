#ifndef FACE_HPP
#define FACE_HPP

#include <array>

#include "../graphics/color.hpp"
#include "../math/vector.hpp"

#define VERTICES 4

enum class FaceOrientation {
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class Face {
	private:
		Vector center;
		Color color;
		std::array<Vector, VERTICES> vertices;
		float distance_from_camera = 0.0f;
		FaceOrientation orientation;

	public:
		Face();
		Face(Vector center, float edge_length, Color color, FaceOrientation orientation);
		std::array<Vector, VERTICES> &get_vertices();
		Vector &get_center_point();
		Color get_color() const { return color; }
		float get_distance_from_camera() const;
		FaceOrientation get_orientation() const { return orientation; }
		void set_distance_from_camera(float distance);
};

#endif // FACE_HPP
