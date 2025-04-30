#include "side.hpp"

Side::Side(Vector center, float side_length, Color color, char orientation, int i, int j)
	: center(center), color(color) {
	float half = side_length / 2.0f;
	float subside_side_len = side_length / SIDE_SUBDIVISION;
	Vector offset;
	Vector base;
	switch (orientation) {
	case 'f':
	case 'b':
		offset = Vector(
			subside_side_len,
			subside_side_len,
			0
		);

		base = Vector(center.at(0) - half, center.at(1) - half, center.at(2));

		corners[0] = base + offset * Vector(i, j, 0);
		corners[1] = base + offset * Vector(i, j + 1, 0);
		corners[2] = base + offset * Vector(i + 1, j + 1, 0);
		corners[3] = base + offset * Vector(i + 1, j, 0);
		break;

	case 't':
	case 'd':
		offset = Vector(
			subside_side_len,
			0,
			subside_side_len
		);

		base = Vector(center.at(0) - half, center.at(1), center.at(2) - half);

		corners[0] = base + offset * Vector(i, 0, j);
		corners[1] = base + offset * Vector(i, 0, j + 1);
		corners[2] = base + offset * Vector(i + 1, 0, j + 1);
		corners[3] = base + offset * Vector(i + 1, 0, j);
		break;

	case 'l':
	case 'r':
	default: // default should not ever happen
		offset = Vector(
			0,
			subside_side_len,
			subside_side_len
		);

		base = Vector(center.at(0), center.at(1) - half, center.at(2) - half);
		corners[0] = base + offset * Vector(0, i, j);
		corners[1] = base + offset * Vector(0, i + 1, j);
		corners[2] = base + offset * Vector(0, i + 1, j + 1);
		corners[3] = base + offset * Vector(0, i, j + 1);
		break;
	}
}

Vector Side::get_center_point() const {
	return center;
}

std::array<Vector, 4> Side::get_corners() const {
	return {corners[0], corners[1], corners[2], corners[3]};
}
