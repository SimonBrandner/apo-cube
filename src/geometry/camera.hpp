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
		float zoom;

	public:
		Camera();
		void update(KnobRotation input_delta);
		Vector get_position() const;
		float get_min_zoom_level();
		float get_yaw() const;
		float get_pitch() const;
		float get_roll() const;
		float get_fov() const;
		float get_zoom() const;
		void set_position(float x, float y, float z);
};

#endif // CAMERA_HPP
