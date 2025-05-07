#include "transform_2d.hpp"

#include <array>
#include <cmath>
#include <iostream>

#include "../math/utils.hpp"
#include "../math/vector.hpp"
#include "color.hpp"
#include "screen.hpp"

/* LIST OD TODOs:
 * RENDER [MANDATORY]:
 * - TODO renderer only if at least 1 vertex is in the camera view
 * - FIXME fix the rounding issue that is causing the lines to glitch
 * - TODO only show 3 faces at once if outside and backtrace the given subfaces
 *
 * STRUCTURE:
 * - TODO separate the virtual and real peripherals in camera
 * - TODO sort the renderer folder into more organized structure
 * - FIXME revisit + add consts in functions where needed
 */

// rescale the 2D coordinates to match the screen size
void rescale_2d_to_screen(Vector &point2d) {
	float x_screen, y_screen;

	// adjust the coordinates based on the screen aspect ratio
	if (SCREEN_WIDTH >= SCREEN_HEIGHT) {
		float scale = 0.5f * SCREEN_HEIGHT;
		x_screen = (point2d.get_x() + 1.0f) * scale +
				   (SCREEN_WIDTH - SCREEN_HEIGHT) * 0.5f;
		y_screen = (1.0f - point2d.get_y()) * scale;
	} else {
		float scale = 0.5f * SCREEN_WIDTH;
		x_screen = (point2d.get_x() + 1.0f) * scale;
		y_screen = (1.0f - point2d.get_y()) * scale +
				   (SCREEN_HEIGHT - SCREEN_WIDTH) * 0.5f;
	}
	point2d = Vector(x_screen, y_screen, point2d.get_z());
}

// convert 3D point to 2D point using perspective projection
void convert_to_2d(Vector &point, float fov) {
	float x = point.get_x();
	float y = point.get_y();
	float z = point.get_z();

	if (std::abs(z) < 1e-6f) {
		z = (z >= 0.0f) ? 1e-6f : -1e-6f; // preserve the sign
	}

	// perspective projection
	float scale = tan_deg(fov * 0.5f);
	float x_ndc = (x / z) / scale;
	float y_ndc = (y / z) / scale;

	// 3rd value could be 0, but is kept as z for z-buffering
	Vector projected(x_ndc, y_ndc, z);
	rescale_2d_to_screen(projected);
	point = projected;
}

// calculates the line pixels of the face
void calculate_pixels_bresenham(Face &face, Screen &screen) {
	bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH] = {false};

	// my implementation of Bresenham's line algorithm (used in vba excel)
	// draw the lines between the vertices
	for (size_t i = 0; i < face.get_vertices().size(); ++i) {
		Vector start = face.get_vertices()[i];
		Vector end = face.get_vertices()[(i + 1) % face.get_vertices().size()];

		int x0 = static_cast<int>(start.get_x());
		int y0 = static_cast<int>(start.get_y());

		int x1 = static_cast<int>(end.get_x());
		int y1 = static_cast<int>(end.get_y());

		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int err = dx - dy;

		// draw the line
		while (true) {
			if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT) {
				screen.at(x0, y0) = face.get_color();
				is_pixel[y0][x0] = true;
			}

			if (x0 == x1 && y0 == y1) {
				break;
			}

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
		}
	}

	fill_face(face, screen, is_pixel);
}

// fills the faces with the square by lines
void fill_face(Face &face, Screen &screen,  bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	int min_x = SCREEN_WIDTH, min_y = SCREEN_HEIGHT;
	int max_x = 0, max_y = 0;

	// find a bounding box of the square, so all the vertices are inside the box
	for (const Vector &corner : face.get_vertices()) {
		int x = static_cast<int>(corner.get_x());
		int y = static_cast<int>(corner.get_y());
		min_x = std::min(min_x, x);
		min_y = std::min(min_y, y);
		max_x = std::max(max_x, x);
		max_y = std::max(max_y, y);
	}

	// making sure the box is inside the screen
	min_x = std::max(min_x - 1, 0);
	min_y = std::max(min_y - 1, 0);
	max_x = std::min(max_x + 1, SCREEN_WIDTH - 1);
	max_y = std::min(max_y + 1, SCREEN_HEIGHT - 1);

	// check the start and end of the line
	for (int y = min_y; y <= max_y; ++y) {
		int start_x = 0, end_x = 0;
		bool is_inside = false;

		for (int x = min_x; x <= max_x; ++x) {
			if (is_pixel[y][x]) {
				if (!is_inside) {
					start_x = x;
					end_x = x;
					is_inside = true;
				} else {
					end_x = x;
				}
			}
		}

		if (start_x == end_x && start_x == 0) {
			continue; // no line found
		}

		screen.draw_rectangle(start_x, y, end_x - start_x + 1, 1, face.get_color());
	}
}
