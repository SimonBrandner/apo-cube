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

	// move front in the direction of  orientation of the cam, scales by the red knob
	Vector forward_vector {
		cos_deg(pitch) * sin_deg(yaw) * (float)input_delta.red,
		sin_deg(pitch) * (float)input_delta.red,
		cos_deg(pitch) * cos_deg(yaw) * (float)input_delta.red
	};

	this->position = this->position + forward_vector;
}

Vector Camera::get_position() { return this->position; }
float Camera::get_yaw() { return this->yaw; }
float Camera::get_pitch() { return this->pitch; }
float Camera::get_fov() { return this->fov; }
