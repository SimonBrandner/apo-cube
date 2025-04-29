#include "camera.hpp"

Camera::Camera() : position(10, 0, 0), yaw(0), pitch(0) {}

void Camera::update(InputDelta input_delta) {
	// update props
}

Vector Camera::get_position() {
	return this->position;
}

float Camera::get_yaw() {
	return this->yaw;
}

float Camera::get_pitch() {
	return this->pitch;
}
