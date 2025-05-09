#include "camera.hpp"

#include "../math/utils.hpp"
#include "../math/vector.hpp"
#include "cube.hpp"

#include <complex>

Camera::Camera()
	: position(0, 0, 0), yaw(0), pitch(0), fov(60), roll(0), distance_from_cube(15) {}


float get_min_distance_limit(float fov) {
	// diagonal of the cube
	float min_limit = std::sqrt(3.0f) * CUBE_EDGE_LENGTH;

	// diagonal of the cube face
	min_limit = min_limit / std::sqrt(2.0f);

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

Vector Camera::get_position() const { return this->position; }
float Camera::get_yaw() const { return this->yaw; }
float Camera::get_pitch() const { return this->pitch; }
float Camera::get_roll() const { return this->roll; }
float Camera::get_fov() const { return this->fov; }
float Camera::get_distance_from_cube() const { return this->distance_from_cube; }
