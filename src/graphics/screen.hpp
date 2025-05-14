#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>

#include "../mz_apo/font_types.h"
#include "color.hpp"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

#define CHARACTER_SPACING 4 // pixels

/**
 * @brief Class representing a screen buffer.
 */
class Screen {
	private:
		Color data[SCREEN_WIDTH * SCREEN_HEIGHT]; // Screen buffer

	public:
		/**
		 * @brief Default constructor for the Screen class.
		 */
		Screen();

		/**
		 * @brief Accessor for the screen buffer.
		 * @param x The x-coordinate of the pixel.
		 * @param y The y-coordinate of the pixel.
		 * @return Reference to the color at the specified coordinates.
		 */
		Color &at(size_t x, size_t y);

		/**
		 * @brief Draw a rectangle on the screen.
		 *
		 * @param x The x-coordinate of the top-left corner of the rectangle.
		 * @param y The y-coordinate of the top-left corner of the rectangle.
		 * @param width The width of the rectangle.
		 * @param height The height of the rectangle.
		 * @param color The color of the rectangle.
		 */
		void draw_rectangle(size_t x, size_t y, size_t width, size_t height,
							Color color);

		/**
		 * @brief Draw a character on the screen from the font descriptor.
		 *
		 * @param character The character to draw.
		 * @param x The x-coordinate of the top-left corner of the character.
		 * @param y The y-coordinate of the top-left corner of the character.
		 * @param color The color of the character.
		 * @param font_descriptor Pointer to the font descriptor.
		 * @return The width of the drawn character.
		 */
		size_t draw_character(char character, size_t x, size_t y, Color color,
							  font_descriptor_t *font_descriptor);

		/**
		 * @brief Draw a string of text on the screen.
		 *
		 * @param text The text to draw.
		 * @param x The x-coordinate of the top-left corner of the text.
		 * @param y The y-coordinate of the top-left corner of the text.
		 * @param color The color of the text.
		 * @param font_descriptor Pointer to the font descriptor.
		 */
		void draw_text(std::string text, size_t x, size_t y, Color color,
					   font_descriptor_t *font_descriptor);
};

#endif // SCREEN_HPP
