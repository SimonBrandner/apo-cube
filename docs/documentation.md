## Project Architecture and Structure

Our project uses a combination of C (mz_apo template) and C++ (our implementation) to create a 3D graphics application for the MZ_APO board.
The application is designed to render a 3D cube on an LCD, allowing user interaction through rotary knobs and visual feedback via LEDs.

We used C++ for the ability to use its class system and OOP features that would be more challenging to implement in C.

The project uses the default [MZ APO template](https://cw.fel.cvut.cz/b242/courses/b35apo/semestral/template) that has the basic functions to communicate with the MZ_APO hardware.
### Project Structure

The project is organized into several directories, each folder containing specific files related to the functionality of the application.
Here is the list of all directories and their contents:

#### `src/geometry/`

This directory contains the geometry objects related to the 3D cube rendering.

- `Cube.cpp` class: Represents the cube, containing the 6 faces, the cube center position, and edge size.
- `Face.cpp` class: Represents a single face of the cube, containing its vertices, color and distance from the camera.
- `Camera.cpp` class: Represents the camera's position and orientation in 3D space, including yaw, pitch, (roll) and distance from the cube.

#### `src/graphics/`

This directory contains the graphics-related classes and functions.

- `Screen.cpp` class: Represents the LCD screen buffer, containing pixel data and methods for drawing shapes and text.
- `Color.cpp` class: Manages color representation and conversion to RGB565 format that the LCD uses.
- `menu.cpp`: Contains the menu elements and manages the menu rendering.

#### `src/math/`

This directory contains mathematical objects like vectors and matrices or custom functions.

- `Matrix.cpp` class: Represents a 3x3 matrix and provides methods for matrix operations.
- `Vector.cpp` class: Represents a 3D vector and provides methods for vector operations.
- `utils.cpp`: Contains utility functions for mathematical operations, such as goniometric functions and mod operation.

#### `src/render/`

This directory contains the rendering-related classes for 3D and 2D graphics.

- `Renderer.cpp` class: Manages the rendering process, transforming 3D coordinates to 2D screen coordinates, and drawing the cube on the screen.
- `transform_3d.cpp`: Contains functions for calculating the transformation matrix and applying it to the cube and camera.
- `transform_2d.cpp`: Contains perspective projection functions, Bresenham's line algorithm for drawing lines and filling shapes on the screen.
- `test_render.cpp`: Is a file with main, which is used for testing the render processing with the virtual peripherals.

#### `src/mz_apo/`

This directory contains the MZ_APO functions written in C provided by the [MZ APO template](https://cw.fel.cvut.cz/b242/courses/b35apo/semestral/template).

#### `src/peripherals/`

This directory contains the classes and functions for handling the input and output peripherals of the MZ_APO.

- `Input.cpp` class: Handles the rotary knobs input, reading their state and rotation values
- `Output.cpp` class: Handles the output to the LCD and LEDs, writing pixel data to the screen and updating the LED states.
- `Mapping.cpp` class: Handles the memory mapping of the MZ_APO hardware registers, allowing direct access to the hardware.
- `utils.cpp`: Contains setup functions for the peripherals.

#### `scripts/virtual_peripherals/`

- This directory contains the Python script for simulating the MZ_APO peripherals using files located in `memory/`.

- To check how to run the script, check the `README.md` file in this directory.

- The python script constantly renders the pixels on the virtual screen and also contains the knobs that can be interacted with.

- The directory contains the same files as the `src/peripherals/` directory, but are redirected to files and the Mapping class for the project consistency is empty.

`test_virtual.cpp`: is a file with main, which is used for testing the render processing with the virtual peripherals.

#### `src/main.cpp`

The main file that initializes the application and manages the state of the program between the menu and render loop.

### Application Flow

1. **Initialization (MZ_APO Only)**: After uploading the program into the MZ_APO, the program starts with *setting up access to the MZ_APO's hardware*.
2. **Menu**: The application presents a **menu on the LCD**.
    *   Users can navigate options using **red and blue knob clicks**.
    *   If a cube face is selected, **knob rotation changes its color**, with RGB values displayed as text.
    *   Pressing the **green knob selects an option**, either starting the 3D view *(step 3)* or exiting the program *(step 4)*.
3. **Render**: If "Start" is selected, the program switches to rendering the 3D cube on the LCD.
    *   **Knob rotations control the Camera**: Red changes distance, green changes pitch, and blue changes yaw.
    *   The **Camera's distance is shown visually on the 32 LED diodes**.
    *   Pressing the **red knob returns to the menu,** *(step 2)*.
4. **Cleanup (MZ_APO Only)**: Before the program finishes (after exiting from the menu), any held resources, like the serialization lock, are released.

### Cube Rendering Pipeline

1. An empty `Screen` (buffer) is created.
2. A `Cube` instance is created with its properties (center, edge length, colors). The cube is initially centered at `(0, 0, -15)` with an edge length of 10.
3. Based on the `Camera` and `Cube`, the transformation matrix is calculated. 
4. The camera is moved to position around the cube based on the yaw and pitch, and the looking vector of the camera is set to the center of the cube.
5. Each vertex of all cube faces with middles is transformed in 3D using the transformation matrix.
6. All faces are sorted from farthest to closest based on the distance from the camera to ensure the correct visibility order of the faces.
7. All vertices of the faces are projected onto a 2D plane using perspective projection.
8. Using Bresenham's line algorithm, the edges of the projected faces are drawn on the screen.
9. The interior of the faces is filled based on the edges drawn.
10. The `Screen` buffer is sent to the LCD for display.

### Camera Properties

The camera contains the following properties:
- `yaw`: The rotation around the Y-axis, controlling the left-right view.
- `pitch`: The rotation around the X-axis, controlling the up-down view.
- `roll`: The rotation around the Z-axis, not used in this project.
- `distance`: The distance from the camera to the cube, controlled by the red knob.

The distance is limited to a minimum value based on the cube properties, ensuring the cube remains fully visible. The camera's position is calculated based on the yaw and pitch angles, and the distance from the cube center.

All the properties except the roll can be changed using the knobs. The roll is not used in this project, but it is included in the Camera class for future use.