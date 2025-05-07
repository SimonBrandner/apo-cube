#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/vector.hpp"
#ifdef VIRTUAL_PERIPHERALS
#include "../periphs_virtual/input.hpp"
#else
#include "../peripherals/input.hpp"
#endif

class Camera {
	private:
		Vector position;
		float yaw;
		float pitch;
		float fov;
		float roll;
		float distance_from_cube;

	public:
		Camera();
		void update(KnobRotation input_delta);
		Vector get_position();
		float get_yaw();
		float get_pitch();
		float get_roll();
		float get_fov();
		float get_distance_from_cube();
		void set_position(float x, float y, float z);
};

#endif // CAMERA_HPP
