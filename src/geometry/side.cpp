#include "side.hpp"

#include <array>
#include <cmath>
#include <iostream>

#include "../math/vector.hpp"
#include "../render/color.hpp"

Side::Side() {}

Side::Side(Vector center, float edge_length, Color color, char orientation,
		   int i, int j)
	: center(center), color(color) {
	float half = edge_length / 2.0f;
	float subside_len = edge_length / SIDE_SUBDIVISION;

	Vector base, offset1, offset2;
	Vector ij00(i, j, 0), ij01(i, j + 1, 0);
	Vector ij11(i + 1, j + 1, 0), ij10(i + 1, j, 0);

	// calculates the 4 vertices, based of the given side and the given
	// subdivision i,j
	switch (orientation) {
	case 'f':
	case 'b': {
		base = Vector(center.at(0) - half, center.at(1) - half, center.at(2));
		offset1 = Vector(subside_len, 0, 0);
		offset2 = Vector(0, subside_len, 0);
		break;
	}
	case 't':
	case 'd': {
		base = Vector(center.at(0) - half, center.at(1), center.at(2) - half);
		offset1 = Vector(subside_len, 0, 0);
		offset2 = Vector(0, 0, subside_len);
		ij00 = Vector(i, 0, j);
		ij01 = Vector(i, 0, j + 1);
		ij11 = Vector(i + 1, 0, j + 1);
		ij10 = Vector(i + 1, 0, j);
		break;
	}
	case 'l':
	case 'r': {
		base = Vector(center.at(0), center.at(1) - half, center.at(2) - half);
		offset1 = Vector(0, subside_len, 0);
		offset2 = Vector(0, 0, subside_len);
		ij00 = Vector(0, i, j);
		ij01 = Vector(0, i + 1, j);
		ij11 = Vector(0, i + 1, j + 1);
		ij10 = Vector(0, i, j + 1);
		break;
	}
	default:
		std::cerr << "Unknown side orientation: " << orientation << std::endl;
		exit(-1);
	}

	vertices[0] = base + offset1 * ij00 + offset2 * ij00;
	vertices[1] = base + offset1 * ij01 + offset2 * ij01;
	vertices[2] = base + offset1 * ij11 + offset2 * ij11;
	vertices[3] = base + offset1 * ij10 + offset2 * ij10;
}

Vector Side::get_center_point() const { return center; }

std::array<Vector, 4> &Side::get_vertices() { return this->vertices; }
