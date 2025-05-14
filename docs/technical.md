## Project Architecture and Structure

Our project uses a combination of **C (based on the `mz_apo` template)** and **C++ (our implementation)** to create a 3D graphics application for the **MZ_APO board**.
The application renders a 3D cube on an LCD and allows user interaction through rotary knobs, with visual feedback via LEDs.

We chose C++ for its object-oriented programming (OOP) features, such as classes and encapsulation, which are more challenging to implement in pure C.

The project builds upon the default [MZ APO template](https://cw.fel.cvut.cz/b242/courses/b35apo/semestral/template), which provides basic functions for communicating with the MZ_APO hardware.

---

### Project Structure

The project is organized into several directories, each containing specific files related to application functionality.

#### `src/geometry/`

Contains classes related to the render process.

* `Cube.cpp`: Represents the cube, including its 6 faces, center position, and edge size.
* `Face.cpp`: Represents a single cube face, storing its vertices, color, and distance from the camera.
* `Camera.cpp`: Manages the camera's position and orientation in 3D space, including `yaw`, `pitch`, `roll` (unused), and distance from the cube.

#### `src/graphics/`

Handles the display-related functionalities.

* `Screen.cpp`: Represents the LCD screen buffer, containing pixel data and drawing methods.
* `Color.cpp`: Manages color representation and conversion to the RGB565 format used by the LCD.
* `menu.cpp`: Contains the menu elements and rendering logic.

#### `src/math/`

Implements custom math utilities.

* `Matrix.cpp`: Implements a 3x3 matrix with standard matrix operations.
* `Vector.cpp`: Represents a 3D vector with vector math operations.
* `utils.cpp`: Provides helper functions for mathematical operations (e.g., trigonometric functions, modulo).

#### `src/render/`

Responsible for rendering both 3D and 2D graphics.

* `Renderer.cpp`: Core renderer that transforms 3D coordinates to 2D and draws the cube.
* `transform_3d.cpp`: Calculates and applies 3D transformation matrices.
* `transform_2d.cpp`: Handles perspective projection and drawing using Bresenham’s algorithm.

#### `src/mz_apo/`

Contains C files from the [MZ APO template](https://cw.fel.cvut.cz/b242/courses/b35apo/semestral/template), used for interacting with MZ_APO hardware.

#### `src/peripherals/`

Manages input/output peripherals.

* `Input.cpp`: Handles rotary knob input (clicks and rotation).
* `Output.cpp`: Manages output to the LCD and LEDs.
* `Mapping.cpp`: Maps memory addresses for direct hardware access.
* `utils.cpp`: Provides setup routines for peripherals.

#### `scripts/virtual_peripherals/`

Contains a Python-based virtual peripheral simulator.

* A Python script renders the virtual LCD and simulates knobs via file-based I/O in the `memory/` directory.
* Usage instructions are provided in `scripts/virtual_peripherals/README.md`.
* The script mimics the structure of `src/peripherals/`, but hardware access is replaced with file-based emulation. The `Mapping` class is voided.

#### `src/main.cpp`

The main file that initializes the application and switches between the menu and rendering modes.

---

### Application Flow

1. **Initialization (MZ_APO Only)**

   * The program begins by setting up access to MZ_APO hardware after being flashed.

2. **Menu Mode**

   * A menu is displayed on the LCD.
   * The **red and blue knob clicks** navigate menu options.
   * If a cube face is selected, **knob rotation** changes its color (RGB shown as text).
   * **Green knob click** confirms the selection - either starting the 3D view (step 3) or exiting (step 4).

3. **3D Render Mode**

   * If "Start" is selected, the cube is rendered in real time on the LCD.

   * **Knob rotation controls the camera**:

      * Red = Distance
      * Green = Pitch
      * Blue = Yaw

   * **LEDs** visualize the camera's distance using 32 LEDs.
   * **Red knob click** returns to the menu.

4. **Cleanup (MZ_APO Only)**

   * Resources, such as memory-mapped regions or synchronization locks, are released.

---

### Cube Rendering Pipeline

1. Create a blank `Screen` buffer.
2. Instantiate a `Cube` with center `(0, 0, -15)` and edge length 10.
3. Compute the 3D transformation matrix using the `Camera` and `Cube` data.
4. Position the camera based on `yaw`, `pitch`, and `distance`; camera always looks at the cube's center.
5. Transform all cube face vertices into the 3D of the camera coordinate system.
6. Sort cube faces from farthest to nearest (painter’s algorithm).
7. Project 3D vertices to 2D using perspective projection.
8. Draw edges using Bresenham’s algorithm.
9. Fill the pixels inside the faces based on the edges drawn.
10. Push the final `Screen` buffer to the LCD.

---

### World Axis

The world axis is defined as follows (a right-handed coordinate system):
* X-axis: Left to Right
* Y-axis: Bottom to Top
* Z-axis: Back to Front

---

### Camera Properties

The `Camera` class includes:

* `yaw`: Y-axis rotation.
* `pitch`: X-axis rotation.
* `roll`: Z-axis rotation (unused but defined).
* `distance`: Distance from camera to cube.

Camera position is calculated using spherical coordinates (`yaw`, `pitch`, `distance`).
`roll` is not used in this implementation but is included for potential future extensions.

Minimal distance is dynamically calculated and limited based on the cube's edge length to ensure the cube is always visible.