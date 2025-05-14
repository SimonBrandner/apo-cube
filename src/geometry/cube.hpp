#ifndef CUBE_HPP
#define CUBE_HPP

#include "../graphics/color.hpp"
#include "face.hpp"

#define CUBE_CENTER Vector(0, 0, -15) // Default center point of the cube
#define CUBE_EDGE_LENGTH 10			  // Default edge length of the cube
#define NUMBER_OF_FACES 6			  // Number of faces in a cube

/**
 * @brief CubeColorConfig is a struct that holds the color configuration for
 * a cube.
 * It contains six colors, one for each face of the cube.
 */
struct CubeColorConfig {
	public:
		/**
		 * @brief Default constructor that initializes the colors of the cube
		 * to default values.
		 */
		CubeColorConfig();

		/**
		 * @brief Returns a reference to the color at the specified index.
		 * @param index The index of the color to return (0-5).
		 * @return A reference to the color at the specified index.
		 */
		Color &at(size_t index);

		Color front;
		Color back;
		Color top;
		Color bottom;
		Color left;
		Color right;
};

/**
 * @brief Cube is a class that represents a 3D cube in space.
 * It contains the center point, edge length, and color configuration of the
 * cube.
 */
class Cube {
	private:
		CubeColorConfig color_config; // color configuration of the cube
		float edge_length;			  // length of the edges of the cube
		Vector center;				  // center point of the cube
		std::array<Face, NUMBER_OF_FACES> faces; // array of faces of the cube

	public:
		/**
		 * @brief Constructor that initializes the cube with a center point,
		 * edge length, and color configuration.
		 * @param center_point The center point of the cube.
		 * @param edge_length The length of the edges of the cube.
		 * @param color_config The color configuration of the cube.
		 */
		Cube(Vector center_point, float edge_length,
			 CubeColorConfig color_config);

		/**
		 * @brief Returns the center point of the cube.
		 * @param x The x-coordinate offset from the center.
		 * @param y The y-coordinate offset from the center.
		 * @param z The z-coordinate offset from the center.
		 * @return The center point of the cube.
		 */
		Vector offset_center(float x, float y, float z) const;

		/**
		 * @brief Getter for an array of faces of the cube.
		 * @return The array of faces of the cube.
		 */
		std::array<Face, NUMBER_OF_FACES> &get_faces();
};

#endif // CUBE_HPP
