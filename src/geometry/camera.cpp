#include "camera.hpp"

#include "../math/utils.hpp"
#include "../math/vector.hpp"
#include "cube.hpp"

#include <cmath>

Camera::Camera()
	: position(0, 0, 0), yaw(0), pitch(0), fov(90), roll(0), distance_from_cube(20) {}


float Camera::get_min_distance_limit() {
	// the goal is to find min distance from which the cube is fully visible.
	// cube can be rotating anyway, so we can assume the cube is a sphere.
	float r = std::sqrt(3.0f) * CUBE_EDGE_LENGTH * 0.5f;

	// angle from the center of the sphere to the edge of view frustum
	float half_fov = fov * 0.5f;

	// the angle which the sphere "occupies" in the view frustum
	float sin_half = sin_deg(half_fov);

	// if the sphere radius is too small, make it invisible
	// (simulating far plane).
	if (std::abs(sin_half) < 1e-6f) {
		return std::numeric_limits<float>::infinity();
	}

	// the distance must be <= r / sin_half, but the minimum distance is equal.
	// because the angle of a sphere must fit into the fov angle.
	float min_n = r / sin_half;
	return min_n;
}



void Camera::update(KnobRotation input_delta) {
	this->pitch += (float)input_delta.green;
	this->yaw += (float)input_delta.blue;
	this->distance_from_cube += (float)input_delta.red;
	this->distance_from_cube = max(get_min_distance_limit(), this->distance_from_cube);
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
