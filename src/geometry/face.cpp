#include "face.hpp"

#include <array>
#include <iostream>

#include "../graphics/color.hpp"
#include "../math/vector.hpp"

Face::Face()
	: center(0, 0, 0), color(Color::Black()),
	  orientation(FaceOrientation::FRONT) {}
Face::Face(Vector center, float edge_length, Color color,
		   FaceOrientation orientation)
	: center(center), color(color), orientation(orientation) {

	float half = edge_length * 0.5f;

	switch (orientation) {
	case FaceOrientation::FRONT:
	case FaceOrientation::BACK:
		vertices[0] =
			Vector(center.at(0) - half, center.at(1) - half, center.at(2));
		vertices[1] =
			Vector(center.at(0) - half, center.at(1) + half, center.at(2));
		vertices[2] =
			Vector(center.at(0) + half, center.at(1) + half, center.at(2));
		vertices[3] =
			Vector(center.at(0) + half, center.at(1) - half, center.at(2));
		break;

	case FaceOrientation::TOP:
	case FaceOrientation::BOTTOM:
		vertices[0] =
			Vector(center.at(0) - half, center.at(1), center.at(2) - half);
		vertices[1] =
			Vector(center.at(0) - half, center.at(1), center.at(2) + half);
		vertices[2] =
			Vector(center.at(0) + half, center.at(1), center.at(2) + half);
		vertices[3] =
			Vector(center.at(0) + half, center.at(1), center.at(2) - half);
		break;

	case FaceOrientation::LEFT:
	case FaceOrientation::RIGHT:
		vertices[0] =
			Vector(center.at(0), center.at(1) - half, center.at(2) - half);
		vertices[1] =
			Vector(center.at(0), center.at(1) - half, center.at(2) + half);
		vertices[2] =
			Vector(center.at(0), center.at(1) + half, center.at(2) + half);
		vertices[3] =
			Vector(center.at(0), center.at(1) + half, center.at(2) - half);
		break;

	default:
		throw std::invalid_argument("Unknown face orientation");
	}
}

void Face::set_distance_from_camera(float distance) {
	this->distance_from_camera = distance;
}

float Face::get_distance_from_camera() const {
	return this->distance_from_camera;
}

Vector &Face::get_center_point() { return this->center; }

std::array<Vector, VERTICES> &Face::get_vertices() { return this->vertices; }
