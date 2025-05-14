#include "camera.hpp"

#include <cmath>

#include "../math/utils.hpp"
#include "../math/vector.hpp"
#include "cube.hpp"

Camera::Camera()
	: position(0, 0, 0), yaw(0), pitch(0), fov(60), roll(0), distance(20) {}

// this function finds the minimum distance in which is the cube fully visible
// calculating using the lowest angle of the view frustum with fully visible cube
float Camera::get_min_distance() const {

	// a cube can be rotating anyway, so we can assume the cube is a sphere.
	// assuming the sphere (cube) center will be in the middle of the screen.
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
	this->pitch += static_cast<float>(input_delta.green);
	this->yaw += static_cast<float>(input_delta.blue);
	this->distance += static_cast<float>(input_delta.red);

	// applying the distance limit of the cube to fit it in the screen
	this->distance = std::max(get_min_distance(), this->distance);
}

void Camera::set_position(float x, float y, float z) {
	this->position = Vector(x, y, z);
}

Vector Camera::get_position() const { return this->position; }
float Camera::get_yaw() const { return this->yaw; }
float Camera::get_pitch() const { return this->pitch; }
float Camera::get_roll() const { return this->roll; }
float Camera::get_fov() const { return this->fov; }
float Camera::get_distance() const { return this->distance; }
