#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/vector.hpp"
#include "../peripherals/input.hpp"

class Camera {
	private:
		Vector position;
		float yaw;
		float pitch;

	public:
		Camera();
		void update(KnobRotation input_delta);
		Vector get_position();
};

#endif // CAMERA_HPP
