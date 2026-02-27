# OpenGL Starter Template

A clean, modular C++ starter template for OpenGL graphics projects.

## Features

- **Modern OpenGL**: OpenGL 4.4 Core Profile with MSAA (4x anti-aliasing)
- **Window Management**: GLFW-based window creation and event handling
- **Math Library**: GLM vector and matrix operations
- **Immediate Mode GUI**: ImGui integration for runtime controls and debugging
- **Camera System**: Built-in 3D camera with keyboard and mouse controls
- **Shader Loading**: Template shader loader system for vertex and fragment shaders
- **Cross-Platform**: Makefile support for Windows, Linux, and macOS

## Project Structure

```
BMPYM_OGL_Starter/
├── Main.cpp                    # Main application entry point and render loop
├── Makefile                    # Build configuration (cross-platform)
├── External/                   # Third-party dependencies
│   ├── External/
│   │   ├── stb_image.h        # Image loading library
│   │   ├── glad/              # OpenGL function loader
│   │   │   ├── glad.c
│   │   │   └── glad.h
│   │   ├── GLFW/              # Window management & input
│   │   │   ├── glfw3.h
│   │   │   └── glfw3native.h
│   │   ├── glm/               # Mathematics library (vectors, matrices)
│   │   │   └── [header files and implementations]
│   │   └── imgui/             # Immediate mode GUI
│   │       ├── imgui.h
│   │       ├── imgui.cpp
│   │       ├── imgui_impl_glfw.h/cpp
│   │       └── imgui_impl_opengl3.h/cpp
│   └── Include/
│       ├── Camera.h           # 3D camera system
│       └── Camera.cpp
├── Shaders/                    # GLSL shader files
│   └── Loaders/
│       ├── shader_t.h         # Template-based shader loader
│       └── shader_c.h         # C-style shader loader
└── Scripts/                    # Utility scripts
```

## Core Components

### 1. **Main Application** (`Main.cpp`)
The entry point that:
- Initializes GLFW window (1280×720, 4x MSAA)
- Sets up OpenGL context and loads GLAD
- Creates and manages ImGui UI
- Implements the main render loop with delta time
- Handles camera input and wireframe mode toggling
- Displays FPS counter

### 2. **Camera System** (`External/Include/Camera.h/cpp`)
A 3D camera implementation with:
- Keyboard-based movement (WASD)
- Mouse-based look direction
- Configurable speed and field of view (FOV)
- Automatic view and projection matrix generation

### 3. **Shader Loading** (`Shaders/Loaders/`)
- `shader_t.h`: Template-based shader loader
- `shader_c.h`: C-style shader loader
Place your GLSL shaders in the `Shaders/` directory

### 4. **External Dependencies**
- **GLFW**: Window creation, event handling
- **GLAD**: OpenGL extension loading
- **GLM**: High-performance math operations
- **ImGui**: Lightweight UI system with OpenGL3 renderer
- **stb_image**: Simple image loading

## Building & Running

### Windows
```bash
make
./Main.exe
```

### Linux / macOS
```bash
make
./Main
```

### Building with Specific Configuration
```bash
make clean          # Remove build artifacts
make all            # Full rebuild
```

Compiled executable will be generated in the `build/` directory.

## Input Controls

| Key | Action |
|-----|--------|
| **ESC** | Release camera control (enables UI interaction) |
| **W / A / S / D** | Move camera forward/left/backward/right |
| **Mouse Movement** | Look around (when camera is active) |
| **Left Mouse Click** | Recapture camera control |

## ImGui Controls

The template includes a sample ImGui panel (top-right corner) with:
- Camera speed slider
- Field of view (FOV) slider
- Wireframe mode toggle
- Real-time FPS counter

## Getting Started

1. **Clone or extract the template**
2. **Add your shaders** to the `Shaders/` directory
3. **Initialize shader objects** in `Main.cpp` using the shader loaders
4. **Create geometry** (meshes, models) and render them in the main loop
5. **Customize ImGui** controls for your specific project needs

### Example: Adding a Simple Shader

```cpp
// In Main.cpp, after shader init comment:
// ShaderProgram myShader("path/to/vertex.glsl", "path/to/fragment.glsl");

// In the render loop:
// myShader.Use();
// myShader.SetMat4("view", view);
// myShader.SetMat4("projection", proj);
// ... render your geometry ...
```

## OpenGL Context Specifications

- **Version**: OpenGL 4.4 Core Profile
- **MSAA**: 4x Multi-Sample Anti-Aliasing
- **Depth Testing**: Enabled
- **V-Sync**: Disabled (uncapped framerate)

## Notes

- The template currently has minimal rendering code; it's designed to serve as a starting point
- Modify `SCREEN_WIDTH` and `SCREEN_HEIGHT` constants to change window resolution
- The camera can be deactivated by pressing ESC to interact with ImGui panels
- Frame time is calculated and available for physics simulations or dynamic adjustments

## Dependencies

All dependencies are included in the `External/` folder:
- **GLFW 3**
- **GLAD (OpenGL 4.4)**
- **GLM (latest)**
- **ImGui (docking branch compatible)**

No external package manager setup required!

## License

This is a starter template. Do whatever you want with it.

## Tips for Extension

- Implement a mesh/model loader for 3D assets
- Add texture support using `stb_image.h` and OpenGL texture objects
- Extend shaders with lighting, normal mapping, and advanced effects
- Create custom ImGui panels for your specific tools
- Implement mouse picking or debug visualization
- Add more sophisticated camera modes (orbital, flight, etc.)

---
