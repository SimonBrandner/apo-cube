#include "transform_2d.hpp"

#include <array>
#include <cmath>

#include "color.hpp"
#include "screen.hpp"
#include "../geometry/cube.hpp"
#include "../math/vector.hpp"
#include "../math/utils.hpp"


/* LIST OD TODO:
 * RENDER [MANDATORY]:
 * - z-buffering based of the side distance, not the pixel distance
 * - ignore if any of the vertices are behind the camera
 * - render only if at least 1 vertex is in the camera view
 * - fix the rounding issue that is causing the lines to glitch
 * - fix the filling of the rows edge case when the side is across the whole screen
 * - calculate one matrix and then apply it to all the vertices, instead of calculating it for each
 *
 * STRUCTURE:
 * - fix cpp const issues with classes
 * - rather use void as return type and pass the pointer as parameter during render [OPTIMIZE]
 * - use & for const& for input vectors/arrays, to avoid expensive coping of the data [OPTIMIZE]
 * - remove optional from the cube and sides [OPTIMIZE]
 * - separate the virtual and real peripherals in camera
 * - sort the render folder into more organized structure
 */

// rescale the 2D coordinates to match the screen size
Vector rescale_2d_to_screen(const Vector &point2d) {
	float x_screen, y_screen;

	// adjust the coordinates based on the screen aspect ratio
	if (SCREEN_WIDTH >= SCREEN_HEIGHT) {
		float scale = 0.5f * SCREEN_HEIGHT;
		x_screen = (point2d.get_x() + 1.0f) * scale + (SCREEN_WIDTH - SCREEN_HEIGHT) * 0.5f;
		y_screen = (1.0f - point2d.get_y()) * scale;
	} else {
		float scale = 0.5f * SCREEN_WIDTH;
		x_screen = (point2d.get_x() + 1.0f) * scale;
		y_screen = (1.0f - point2d.get_y()) * scale + (SCREEN_HEIGHT - SCREEN_WIDTH) * 0.5f;
	}

	return Vector(x_screen, y_screen, point2d.get_z());
}

// convert 3D point to 2D point using perspective projection
Vector convert_to_2d(const Vector &point, float fov) {
	float x = point.get_x();
	float y = point.get_y();
	float z = point.get_z();

	if (std::abs(z) < 1e-6f) {
		z = (z >= 0.0f) ? 1e-6f : -1e-6f; // preserving sign, for future optimization
	}

	// perspective projection
	float scale = tan_deg(fov * 0.5f);
	float x_ndc = (x / z) / scale;
	float y_ndc = (y / z) / scale;

	// 3rd value could be 0, but is kept as z for z-buffering
	return rescale_2d_to_screen(Vector(x_ndc, y_ndc, z));
}

// calculates the line pixels of the side
void calculate_pixels_bresenham(const std::array<Vector, 4> &vertices, Color color,
								Screen &screen,
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH] = {false};

	// my implementation of Bresenham's line algorithm (used in vba excel)
	// draw the lines between the vertices
	for (size_t i = 0; i < vertices.size(); ++i) {
		Vector start = vertices[i];
		Vector end = vertices[(i + 1) % vertices.size()];

		int x0 = static_cast<int>(start.get_x());
		int y0 = static_cast<int>(start.get_y());
		float z0 = start.get_z();

		int x1 = static_cast<int>(end.get_x());
		int y1 = static_cast<int>(end.get_y());
		float z1 = end.get_z();

		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int err = dx - dy;

		int total_steps = std::max(dx, dy);
		int step_count = 0;

		// draw the line
		while (true) {
			if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT) {
				float t = (total_steps == 0) ? 0.0f : (float)(step_count) / total_steps;
				float z = z0 + t * (z1 - z0);

				if (z > z_buffer[y0][x0]) {
					z_buffer[y0][x0] = z;
					screen.at(x0, y0) = color;
					is_pixel[y0][x0] = true;
				}
			}

			if (x0 == x1 && y0 == y1) break;

			// Bresenham's algorithm
			int e2 = 2 * err;
			if (e2 > -dy) {
				err -= dy;
				x0 += sx;
			}
			if (e2 < dx) {
				err += dx;
				y0 += sy;
			}
			++step_count;
		}
	}

	fill_side(vertices, color, screen, z_buffer, is_pixel);
}

// fills the sides with the square by lines
void fill_side(const std::array<Vector, 4> &vertices, Color color,
								Screen &screen,
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH],
								const bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	int min_x = SCREEN_WIDTH, min_y = SCREEN_HEIGHT;
	int max_x = 0, max_y = 0;

	// find the bounding box of the square, so all the vertices are inside the box
	for (const Vector& corner : vertices) {
		int x = static_cast<int>(corner.get_x());
		int y = static_cast<int>(corner.get_y());
		min_x = std::min(min_x, x);
		min_y = std::min(min_y, y);
		max_x = std::max(max_x, x);
		max_y = std::max(max_y, y);
	}

	// making sure the box is inside the screen
	min_x = std::max(min_x-1, 0);
	min_y = std::max(min_y-1, 0);
	max_x = std::min(max_x+1, SCREEN_WIDTH-1);
	max_y = std::min(max_y+1, SCREEN_HEIGHT-1);

	// fill the pixels inside the bounding box
	for (int y = min_y; y <= max_y; ++y) {
		bool is_inside = false;
		float z_start = 0.0f;
		float z_end = 0.0f;
		int span_length = 0;

		// get the z values of the pixels and length in the given line
		for (int x = min_x; x <= max_x; ++x) {
			if (is_pixel[y][x]) {
				if (!is_inside) {
					z_start = z_buffer[y][x];
				}
				is_inside = !is_inside;

				if (is_inside) {
					++span_length;
					z_end = z_buffer[y][x];
				}
			}
		}

		// if in the current row left and right square side pixels are the same
		if (is_inside == true) {
			span_length = 1;
			z_end = z_start;
		}

		is_inside = false;
		int fill_index = 0;

		// fill the pixels in the given line in-between the square side pixels
		for (int x = min_x; x <= max_x; ++x) {
			if (is_pixel[y][x]) {
				is_inside = !is_inside;
			}

			if (is_inside && x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
				// linear interpolation of the z value
				float z = z_start + (z_end - z_start) * (float)((fill_index) / std::max(1, span_length));
				++fill_index;

				if (z > z_buffer[y][x]) {
					z_buffer[y][x] = z;
					screen.at(x, y) = color;
				}
			}
		}
	}
}
