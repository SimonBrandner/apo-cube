#ifndef TRANSFORM_2D_HPP
#define TRANSFORM_2D_HPP

#include "../geometry/face.hpp"
#include "../graphics/screen.hpp"
#include "../math/vector.hpp"

/**
 * @brief Rescales the 2D point to fit within the screen dimensions.
 *
 * @param point2d The 2D point to be rescaled.
 */
void rescale_2d_to_screen(Vector &point2d);

/**
 * @brief Converts a 3D point to a 2D point using the camera's field of view,
 * using perspective projection.
 *
 * @param point The 3D point to be converted.
 * @param fov The field of view of the camera.
 */
void convert_to_2d(Vector &point, float fov);

/**
 * @brief Draws all edges of a face on the screen using Bresenham's line
 * algorithm.
 *
 * @param face The face to be drawn.
 * @param screen The screen on which the face will be drawn.
 */
void calculate_pixels_bresenham(Face &face, Screen &screen);

/**
 * @brief Fills the face on the screen using a scanline algorithm.
 *
 * @param face The face to be filled.
 * @param screen The screen on which the face will be filled.
 * @param is_pixel A 2D array indicating which pixels are already filled.
 */
void fill_face(Face &face, Screen &screen,
			   bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH]);

#endif // TRANSFORM_2D_HPP
