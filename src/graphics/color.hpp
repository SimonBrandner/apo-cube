#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

/**
 * @brief Color class represents a color in RGB format.
 * It provides methods to create common colors and convert to RGB565 format.
 */
class Color {
	private:
		uint8_t red; // Red color component (0-255)
		uint8_t green; // Green color component (0-255)
		uint8_t blue; // Blue color component (0-255)

	public:
		static Color White(); // White color (255, 255, 255)
		static Color Black(); // Black color (0, 0, 0)
		static Color Red(); // Red color (255, 0, 0)
		static Color Blue(); // Blue color (0, 0, 255)
		static Color Magenta(); // Magenta color (255, 0, 255)
		static Color Cyan(); // Cyan color (0, 255, 255)
		static Color Green(); // Green color (0, 255, 0)
		static Color Yellow(); // Yellow color (255, 255, 0)

		/**
		 * @brief Default constructor initializes color to black (0, 0, 0).
		 */
		Color();

		/**
		 * @brief Constructor initializes color with specified RGB values.
		 * @param red Red component (0-255)
		 * @param green Green component (0-255)
		 * @param blue Blue component (0-255)
		 */
		Color(uint8_t red, uint8_t green, uint8_t blue);

		/**
		 * @brief Converts the color to RGB565 format.
		 * @return 16-bit RGB565 representation of the color.
		 */
		uint16_t to_rgb565() const;

		/**
		 * @brief Gets the red component of the color.
		 * @return Red component (0-255)
		 */
		uint8_t get_red() const;

		/**
		 * @brief Gets the green component of the color.
		 * @return Green component (0-255)
		 */
		uint8_t get_green() const;

		/**
		 * @brief Gets the blue component of the color.
		 * @return Blue component (0-255)
		 */
		uint8_t get_blue() const;
};

#endif // COLOR_HPP
