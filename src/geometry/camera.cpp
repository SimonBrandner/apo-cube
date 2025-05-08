#include "camera.hpp"

#include "../math/utils.hpp"
#include "../math/vector.hpp"
#include "cube.hpp"

#include <complex>

Camera::Camera() : position(0, 0, 0), yaw(0), pitch(0), fov(60), distance_from_cube(15), roll(0)  {}

float get_min_distance_limit(float fov) {
	// diagonal of the cube
	float min_limit = sqrt(3.0f,2) * CUBE_EDGE_LENGTH;

	// diagonal of the cube face
	min_limit = min_limit / sqrt(2.0f,2);

	// include the fov into the distance limit
	min_limit = min_limit * (sin_deg(45.0f) / sin_deg(fov * 0.5f));

	return min_limit;
}

void Camera::update(KnobRotation input_delta) {
	this->pitch += (float)input_delta.green;
	this->yaw += (float)input_delta.blue;
	this->distance_from_cube += (float)input_delta.red;
	this->distance_from_cube = max(get_min_distance_limit(fov), this->distance_from_cube);
}

void Camera::set_position(float x, float y, float z) {
	this->position = Vector(x, y, z);
}

Vector Camera::get_position() { return this->position; }
float Camera::get_yaw() { return this->yaw; }
float Camera::get_pitch() { return this->pitch; }
float Camera::get_roll() { return this->roll; }
float Camera::get_fov() { return this->fov; }
float Camera::get_distance_from_cube() { return this->distance_from_cube; }
