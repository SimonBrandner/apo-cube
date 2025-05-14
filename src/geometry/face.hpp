#ifndef FACE_HPP
#define FACE_HPP

#include <array>

#include "../graphics/color.hpp"
#include "../math/vector.hpp"

#define VERTICES 4 // Number of vertices in a face

/**
 * @brief Enum class representing the orientation of a face.
 */
enum class FaceOrientation {
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

/**
 * @brief Class representing a face of a cube.
 */
class Face {
	private:
		Vector center; // Center point of the face
		Color color; // Color of the face
		std::array<Vector, VERTICES> vertices; // 4 vertices of the face
		float distance_from_camera = 0.0f; // Distance from the camera
		FaceOrientation orientation; // Orientation of this face

	public:
		/**
		 * @brief Default constructor for the Face class, used for
		 * cube initialization.
		 */
		Face();

		/**
		 * @brief Constructor for the Face class.
		 *
		 * @param center Center point of the face.
		 * @param edge_length Length of the edge of the cube.
		 * @param color Color of the face.
		 * @param orientation Orientation of the face.
		 */
		Face(Vector center, float edge_length, Color color, FaceOrientation orientation);

		/**
		 * @brief Getter for the vertices of the face.
		 */
		std::array<Vector, VERTICES> &get_vertices();

		/**
		 * @brief Getter for the center point of the face.
		 */
		Vector &get_center_point();

		/**
		 * @brief Getter for the color of the face.
		 */
		Color get_color() const { return color; }

		/**
		 * @brief Getter for the distance from the camera.
		 */
		float get_distance_from_camera() const;

		/**
		 * @brief Getter for the orientation of the face.
		 */
		FaceOrientation get_orientation() const { return orientation; }

		/**
		 * @brief Setter for the distance from the camera.
		 *
		 * @param distance Distance from the camera.
		 */
		void set_distance_from_camera(float distance);
};

#endif // FACE_HPP
