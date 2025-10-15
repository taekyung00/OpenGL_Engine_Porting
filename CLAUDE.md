# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build System Commands

### Quick Build (Recommended)
```bash
# Automated build script that handles all configurations
python3 scripts/scan_build_project.py

# Show build options and filters
python3 scripts/scan_build_project.py --help
```

### Manual Build Commands
**Windows:**
```bash
# Configure
cmake --preset windows-debug
cmake --preset windows-developer-release
cmake --preset windows-release
cmake --preset web-debug-on-windows

# Build
cmake --build --preset windows-debug
cmake --build --preset windows-developer-release
cmake --build --preset windows-release
cmake --build --preset web-debug-on-windows
```

**Linux:**
```bash
# Configure
cmake --preset linux-debug
cmake --preset linux-developer-release
cmake --preset linux-release
cmake --preset web-debug
cmake --preset web-developer-release
cmake --preset web-release

# Build
cmake --build --preset linux-debug
cmake --build --preset linux-developer-release
cmake --build --preset linux-release
cmake --build --preset web-debug
cmake --build --preset web-developer-release
cmake --build --preset web-release
```

### Build Configuration Types
- **Debug**: Active development with breakpoints, no optimizations, console output, all developer features
- **Developer-Release**: Optimized performance with console output, verbose logging, developer assertions (no breakpoints)
- **Release**: Final production builds with full optimizations, minimal logging, no console, smallest executable

### Code Formatting
The project uses clang-format with custom settings defined in `.clang-format`. Key formatting rules:
- 4-space indentation, no tabs
- Allman brace style
- 200 character line limit
- Align consecutive assignments and declarations
- Break after opening brackets

## Architecture Overview

### Core Engine Architecture
The project follows a layered architecture built around a central `Engine` singleton that manages all subsystems:

**Engine (`source/Engine/Engine.hpp`)**:
- Singleton pattern providing global access to all subsystems
- Manages complete application lifecycle (Start→Update loop→Stop)
- Coordinates Window, Input, Renderer2D, GameStateManager, TextureManager, Logger

**Game State System**:
- State-based architecture using `GameStateManager` for different application modes
- Current implementation uses `DemoShapes` as the primary state (see `main.cpp:66`)
- Demo states in `source/Demo/`: `DemoShapes`, `DemoFramebuffer`, `DemoText`

### Rendering System
The project implements a 2D immediate-mode renderer with two rendering paths:

**IRenderer2D Interface (`source/CS200/IRenderer2D.hpp`)**:
- Abstract base class defining rendering operations
- Methods: DrawQuad, DrawCircle, DrawRectangle, DrawLine

**ImmediateRenderer2D Implementation (`source/CS200/ImmediateRenderer2D.hpp`)**:
- Immediate-mode rendering (each draw call renders directly)
- **Textured Quad Path**: Standard texture mapping with transforms and tinting
- **SDF Shape Path**: Signed Distance Field rendering for perfect circles/rectangles
- Uses two separate OpenGL shaders and vertex arrays

### OpenGL Abstraction Layer
**Location**: `source/OpenGL/`
- Provides C++ wrappers around OpenGL resources
- Key classes: `Texture`, `Shader`, `Buffer`, `VertexArray`
- RAII pattern for automatic resource management
- Handles cross-platform OpenGL differences

### Cross-Platform Support
- **Native builds**: Uses SDL2 for windowing, OpenGL for rendering
- **Web builds**: Emscripten compilation to WebAssembly
- Conditional compilation using `__EMSCRIPTEN__` preprocessor macro
- Web-specific main loop and window resize handling

### Mathematics and Utilities
**Key Components**:
- `Math::TransformationMatrix` for 2D transformations
- `Math::vec2`, `Math::ivec2` for 2D vectors
- `CS200::RGBA` for color values
- NDC (Normalized Device Coordinates) utilities in `source/CS200/NDC.hpp`
- Matrix operations in `source/Engine/Matrix.hpp`

## Important Development Notes

### Shader Assets
SDF rendering uses fragment shaders located in `Assets/shaders/ImmediateRenderer2D/sdf.frag`. The SDF shape types defined in the C++ code must stay synchronized with shader constants.

### Resource Management
- All OpenGL resources use RAII wrappers
- Texture management through `TextureManager` prevents duplicate loading
- Engine manages initialization order of interdependent systems

### Demo Structure
The three demo states showcase different aspects of the rendering system:
- `DemoShapes`: Basic primitive rendering (circles, rectangles, lines)
- `DemoFramebuffer`: Framebuffer and texture rendering techniques
- `DemoText`: Text rendering using font systems

### Multi-Platform Considerations
When making changes:
- Test both native and web builds if modifying core systems
- Use platform-specific code blocks only when necessary
- Web builds require special handling for main loop and window events