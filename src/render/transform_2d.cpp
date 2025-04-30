#include "transform_2d.hpp"
#include <array>

#define FOV 90.0f

Vector rescale_2d_to_screen(Vector point2d) {
	float x_screen;
	float y_screen;

	if (SCREEN_WIDTH >= SCREEN_HEIGHT) {
		x_screen = (point2d.get_x() + 1.0f) * 0.5f * SCREEN_HEIGHT + (SCREEN_WIDTH - SCREEN_HEIGHT) * 0.5f;
		y_screen = (1.0f - point2d.get_y()) * 0.5f * SCREEN_HEIGHT;
	} else {
		x_screen = (point2d.get_x() + 1.0f) * 0.5f * SCREEN_WIDTH;
		y_screen = (1.0f - point2d.get_y()) * 0.5f * SCREEN_WIDTH + (SCREEN_HEIGHT - SCREEN_WIDTH) * 0.5f;
	}

	return Vector(x_screen, y_screen, point2d.get_z());
}

Vector convert_to_2d(Vector point) {
	float x = point.get_x();
	float y = point.get_y();
	float z = point.get_z();

	if (z == 0) {
		z = 0.0001f; // avoid division by zero
	}

	// prerspective projection

	float scale = tan_deg(FOV * 0.5f);
	float x_ndc = (x / z) * scale; // normalized device coordinates
	float y_ndc = (y / z) * scale;

	Vector rescaled = Vector(x_ndc, y_ndc, z); // z will be used for z-buffer
	rescaled = rescale_2d_to_screen(rescaled);

	return rescaled;
}

// TODO: prettify this function, format it and separate it into multiple functions
void calculate_pixels_bresenham(std::array<Vector, 4> corners, Color color,
								Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH],
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH];
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			is_pixel[y][x] = false;
		}
	}

	// my implementation of Bresenham's line algorithm (used in vba excel)
	for (size_t i = 0; i < corners.size(); ++i) {
		Vector start = corners[i];
		Vector end = corners[(i + 1) % corners.size()];

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

		while (true) {
			if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT) {
				float t = (total_steps == 0) ? 0.0f : (float)step_count / total_steps;
				float z = z0 + t * (z1 - z0);

				if (z > z_buffer[y0][x0]) {
					z_buffer[y0][x0] = z;
					pixels[y0][x0] = color;
					is_pixel[y0][x0] = true;
				}
			}

			if (x0 == x1 && y0 == y1) break;

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

	fill_side(corners, color, pixels, z_buffer, is_pixel);
}

// fills the sides with the square by lines
void fill_side(std::array<Vector, 4> corners, Color color,
								Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH],
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH],
								bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	int min_x = SCREEN_WIDTH, min_y = SCREEN_HEIGHT;
	int max_x = 0, max_y = 0;

	// find the bounding box of the square, so all the vertices are inside the box
	for (Vector& corner : corners) {
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
				// linear interpolation of z
				float z = z_start + (z_end - z_start) * (float)((fill_index) / std::max(1, span_length));

				++fill_index;

				// check if the pixel is visible
				if (z > z_buffer[y][x]) {
					z_buffer[y][x] = z;
					pixels[y][x] = color;
				}
			}
		}
	}
}
