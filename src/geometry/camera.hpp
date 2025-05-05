#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/vector.hpp"
//#include "../peripherals/input.hpp"
#include "../periphs_virtual/input.hpp"

/*
 * WARNING: You have to CURRENTLY comment / uncomment the peripherals you will be using!
 * TODO: SOLVE PERIPHERALS REAL/VITRUAL ISSUE.
 */

class Camera {
	private:
		Vector position;
		float yaw;
		float pitch;
		float fov;

	public:
		Camera();
		void update(KnobRotation input_delta);
		Vector get_position();
		float get_yaw();
		float get_pitch();
		float get_fov();
};

#endif // CAMERA_HPP
