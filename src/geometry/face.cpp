#include "face.hpp"

#include <array>
#include <cmath>
#include <iostream>

#include "../math/vector.hpp"
#include "../render/color.hpp"

Face::Face() {}

Face::Face(Vector center, float edge_length, Color color, char orientation,
		   int i, int j)
	: center(center), color(color), orientation(orientation) {

	float half = edge_length / 2.0f;
	float subface_len = edge_length / FACE_SUBDIVISION;

	Vector base, offset1, offset2;
	Vector ij00(i, j, 0), ij01(i, j + 1, 0);
	Vector ij11(i + 1, j + 1, 0), ij10(i + 1, j, 0);

	// calculates the 4 vertices, based of the given face and the given
	// subdivision i,j
	switch (orientation) {
	case 'f':
	case 'b': {
		base = Vector(center.at(0) - half, center.at(1) - half, center.at(2));
		offset1 = Vector(subface_len, 0, 0);
		offset2 = Vector(0, subface_len, 0);
		break;
	}
	case 't':
	case 'd': {
		base = Vector(center.at(0) - half, center.at(1), center.at(2) - half);
		offset1 = Vector(subface_len, 0, 0);
		offset2 = Vector(0, 0, subface_len);
		ij00 = Vector(i, 0, j);
		ij01 = Vector(i, 0, j + 1);
		ij11 = Vector(i + 1, 0, j + 1);
		ij10 = Vector(i + 1, 0, j);
		break;
	}
	case 'l':
	case 'r': {
		base = Vector(center.at(0), center.at(1) - half, center.at(2) - half);
		offset1 = Vector(0, subface_len, 0);
		offset2 = Vector(0, 0, subface_len);
		ij00 = Vector(0, i, j);
		ij01 = Vector(0, i + 1, j);
		ij11 = Vector(0, i + 1, j + 1);
		ij10 = Vector(0, i, j + 1);
		break;
	}
	default:
		std::cerr << "Unknown face orientation: " << orientation << std::endl;
		exit(-1);
	}

	vertices[0] = base + offset1 * ij00 + offset2 * ij00;
	vertices[1] = base + offset1 * ij01 + offset2 * ij01;
	vertices[2] = base + offset1 * ij11 + offset2 * ij11;
	vertices[3] = base + offset1 * ij10 + offset2 * ij10;

	//Vector new_center = (vertices[0] + vertices[3]) / 2.0f;
	//this->center = new_center;
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

std::array<Vector, 4> &Face::get_vertices() {
	return this->vertices;
}