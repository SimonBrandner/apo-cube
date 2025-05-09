#include "face.hpp"

#include <array>
#include <cmath>
#include <iostream>

#include "../math/vector.hpp"
#include "../render/color.hpp"

Face::Face() : center(0, 0, 0), color(Color::Black()),
								   orientation('f') {}

Face::Face(Vector center, float edge_length, Color color, char orientation)
	: center(center), color(color), orientation(orientation) {

	float half = edge_length / 2.0f;

	switch (orientation) {
	case 'f':
	case 'b':
		vertices[0] = Vector(center.at(0) - half, center.at(1) - half, center.at(2));
		vertices[1] = Vector(center.at(0) - half, center.at(1) + half, center.at(2));
		vertices[2] = Vector(center.at(0) + half, center.at(1) + half, center.at(2));
		vertices[3] = Vector(center.at(0) + half, center.at(1) - half, center.at(2));
		break;

	case 't':
	case 'd':
		vertices[0] = Vector(center.at(0) - half, center.at(1), center.at(2) - half);
		vertices[1] = Vector(center.at(0) - half, center.at(1), center.at(2) + half);
		vertices[2] = Vector(center.at(0) + half, center.at(1), center.at(2) + half);
		vertices[3] = Vector(center.at(0) + half, center.at(1), center.at(2) - half);
		break;

	case 'l':
	case 'r':
	default: // default should not ever happen
		vertices[0] = Vector(center.at(0), center.at(1) - half, center.at(2) - half);
		vertices[1] = Vector(center.at(0), center.at(1) - half, center.at(2) + half);
		vertices[2] = Vector(center.at(0), center.at(1) + half, center.at(2) + half);
		vertices[3] = Vector(center.at(0), center.at(1) + half, center.at(2) - half);
		break;
	}
}

void Face::set_distance_from_camera(float distance) {
	this->distance_from_camera = distance;
}

float Face::get_distance_from_camera() const {
	return this->distance_from_camera;
}

Vector &Face::get_center_point() {
	return this->center;
}

std::array<Vector, VERTICES> &Face::get_vertices() {
	return this->vertices;
}