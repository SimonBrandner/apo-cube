#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/vector.hpp"

class Camera {
	private:
		Vector position;
		float yaw;
		float pitch;

	public:
		Camera();
		//void update(InputDelta input_delta);
		Vector get_position();
		float get_yaw();
		float get_pitch();
};

#endif // CAMERA_HPP
