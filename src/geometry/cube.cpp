#include "cube.hpp"

#include <array>
#include <cmath>
#include <iostream>

#include "../graphics/color.hpp"
#include "../math/vector.hpp"
#include "./face.hpp"

CubeColorConfig::CubeColorConfig() {
	this->front = Color::Red();
	this->back = Color::Blue();
	this->left = Color::Magenta();
	this->right = Color::Cyan();
	this->top = Color::Green();
	this->bottom = Color::Yellow();
}

Color &CubeColorConfig::at(size_t index) {
	switch (index) {
	case 0:
		return this->front;
	case 1:
		return this->back;
	case 2:
		return this->left;
	case 3:
		return this->right;
	case 4:
		return this->top;
	case 5:
		return this->bottom;
	}

	std::cerr << "Unknown face: " << index << std::endl;
	exit(-1);
}

Cube::Cube(Vector center_point, float edge_length, CubeColorConfig color_config)
	: edge_length(edge_length) {
	for (int i = 0; i < 3; ++i) {
		this->center[i] = center_point.at(i);
	}

	struct FaceConfig {
		float dx, dy, dz;
		Color color;
		char id;
	};

	std::array<FaceConfig, NUMBER_OF_FACES> faces = {{
		{ 0,  0,  1, color_config.front,  'f'},
		{ 0,  0, -1, color_config.back,   'b'},
		{ 0,  1,  0, color_config.top,    't'},
		{ 0, -1,  0, color_config.bottom, 'd'},
		{ 1,  0,  0, color_config.right,  'r'},
		{-1,  0,  0, color_config.left,   'l'}
	}};

	// create the faces of the cube and subdivides them, for clipping purposes
	int face_index = 0;
	for (const auto &face : faces) {
		this->faces[face_index++] = Face(
			offset_center(face.dx, face.dy, face.dz),
			edge_length,
			face.color,
			face.id
		);
	}
}

Vector Cube::offset_center(float x, float y, float z) const {
	return Vector(
		center[0] + x * edge_length * 0.5f,
		center[1] + y * edge_length * 0.5f,
		center[2] + z * edge_length * 0.5f
	);
}

std::array<Face, NUMBER_OF_FACES>& Cube::get_faces() {
	return this->faces;
}
