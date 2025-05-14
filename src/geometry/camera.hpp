#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/vector.hpp"
#include "../peripherals/input.hpp"

/**
 * @brief The Camera stores the camera position and orientation in the 3D space.
 * (for rendering purposes)
 */
class Camera {
	private:
		Vector position; // camera position in 3D space
		float yaw;		 // rotation around the Y axis
		float pitch;	 // rotation around the X axis
		float fov;		 // field of view (in degrees)
		float roll;		 // rotation around the Z axis
		float distance;	 // distance from the camera to the object being viewed

	public:
		/**
		 * @brief Constructor for the Camera class.
		 * Initializes the camera position, yaw, pitch, fov, roll, and distance.
		 */
		Camera();

		/**
		 * @brief Getter for the position
		 */
		Vector get_position() const;

		/**
		 * @brief Function finds the minimum distance in which the cube is
		 * fully visible
		 * calculating using the lowest angle of the view frustum
		 * with fully visible cube
		 */
		float get_min_distance() const;

		/**
		 * @brief Getter for yaw
		 */
		float get_yaw() const;

		/**
		 * @brief Getter for pitch
		 */
		float get_pitch() const;

		/**
		 * @brief Getter for roll
		 */
		float get_roll() const;

		/**
		 * @brief Getter for fov
		 */
		float get_fov() const;

		/**
		 * @brief Getter for distance
		 */
		float get_distance() const;

		/**
		 * @brief Update the camera position and orientation based on input
		 * @param input_delta The input delta from the knobs
		 */
		void update(KnobRotation input_delta);

		/**
		 * @brief Set the camera position
		 * @param x The x coordinate of the camera position
		 * @param y The y coordinate of the camera position
		 * @param z The z coordinate of the camera position
		 */
		void set_position(float x, float y, float z);
};

#endif // CAMERA_HPP
