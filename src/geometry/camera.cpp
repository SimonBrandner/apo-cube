#include "camera.hpp"

Camera::Camera() : position(10, 0, 0), yaw(0), pitch(0) {}

void Camera::update(KnobRotation input_delta) {
	// update props
}

Vector Camera::get_position() { return this->position; }
