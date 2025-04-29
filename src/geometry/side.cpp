#include "side.hpp"

Side::Side(Vector center, float side_length, Color color, char orientation)
	: center(center), color(color) {
	float half = side_length / 2.0f;

	switch (orientation) {
	case 'f':
	case 'b':
		corners[0] = Vector(center.at(0) - half, center.at(1) - half, center.at(2));
		corners[1] = Vector(center.at(0) - half, center.at(1) + half, center.at(2));
		corners[2] = Vector(center.at(0) + half, center.at(1) + half, center.at(2));
		corners[3] = Vector(center.at(0) + half, center.at(1) - half, center.at(2));
		break;

	case 't':
	case 'd':
		corners[0] = Vector(center.at(0) - half, center.at(1), center.at(2) - half);
		corners[1] = Vector(center.at(0) - half, center.at(1), center.at(2) + half);
		corners[2] = Vector(center.at(0) + half, center.at(1), center.at(2) + half);
		corners[3] = Vector(center.at(0) + half, center.at(1), center.at(2) - half);
		break;

	case 'l':
	case 'r':
	default: // default should not ever happen
		corners[0] = Vector(center.at(0), center.at(1) - half, center.at(2) - half);
		corners[1] = Vector(center.at(0), center.at(1) - half, center.at(2) + half);
		corners[2] = Vector(center.at(0), center.at(1) + half, center.at(2) + half);
		corners[3] = Vector(center.at(0), center.at(1) + half, center.at(2) - half);
		break;
	}
}

Vector Side::get_center_point() const {
	return center;
}

std::array<Vector, 4> Side::get_corners() const {
	return {corners[0], corners[1], corners[2], corners[3]};
}