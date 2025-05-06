#include "camera.hpp"

#include "../math/vector.hpp"
#include "../math/utils.hpp"

Camera::Camera() : position(0, 0, 0), yaw(0), pitch(0), fov(90) {}

void Camera::update(KnobRotation input_delta) {
	/* assuming, may change later...
	 * R: Move front/back by the direction camera orientation
	 * G: Pitch increase/decrease
	 * B: Yaw increase/decrease
	 */

	// in degrees
	this->pitch += (float)input_delta.green;
	this->yaw += (float)input_delta.blue;
	this->roll += (float)input_delta.red;
}

void Camera::set_position(float x, float y, float z) {
	this->position = Vector(x, y, z);
}

Vector Camera::get_position() { return this->position; }
float Camera::get_yaw() { return this->yaw; }
float Camera::get_pitch() { return this->pitch; }
float Camera::get_roll() { return this->roll; }
float Camera::get_fov() { return this->fov; }
