#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/vector.hpp"
//#include "../peripherals/input.hpp" TODO: SOLVE PERIPHERIALS REAL/VITRUAL ISSUE.
#include "../periphs_virtual/input.hpp"


class Camera {
	private:
		Vector position;
		float yaw;
		float pitch;

	public:
		Camera();
		void update(KnobRotation input_delta);
		Vector get_position();
		float get_yaw();
		float get_pitch();
};

#endif // CAMERA_HPP
