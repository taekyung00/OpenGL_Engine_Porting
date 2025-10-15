# CS230 Engine Components Documentation

This document provides a comprehensive overview of all engine components and services in the CS230 game engine.

## Engine Architecture Overview

The CS230 engine follows a singleton pattern where the `Engine` class provides centralized access to all core subsystems. All engine components are in the `CS230` namespace and are accessed through static methods on the Engine class.

---

## Core Engine Services

### Engine (Engine.h)

**Purpose**: Main engine singleton that manages all subsystems and the game loop.

**Key Features**:

- Singleton pattern implementation providing global access
- Frame rate management (30 FPS target)
- Centralized access to all engine subsystems
- Main game loop coordination

**Access Pattern**:

```cpp
Engine::GetLogger()          // Access logging system
Engine::GetWindow()          // Access window management
Engine::GetInput()           // Access input handling
Engine::GetTextureManager()  // Access texture loading
Engine::GetFont(index)       // Access font rendering
Engine::GetGameStateManager() // Access state management
```

**Methods**:

- `Start(title)`: Initialize engine with window title
- `Update()`: Main game loop update
- `Stop()`: Shutdown engine
- `HasGameEnded()`: Check if game should exit

---

## Core Subsystems

### Logger (Logger.h)

**Purpose**: Centralized logging system with severity levels and file output.

**Severity Levels**:

- `Verbose`: Minor messages
- `Debug`: Development debugging information
- `Event`: General events (key presses, state changes)
- `Error`: Error conditions (file load failures)

**Features**:

- File and console output support
- Timestamp tracking from engine start
- Severity filtering
- Automatic log file management

**Usage**:

```cpp
Engine::GetLogger().LogError("Error message");
Engine::GetLogger().LogEvent("Event occurred");
Engine::GetLogger().LogDebug("Debug info");
Engine::GetLogger().LogVerbose("Verbose details");
```

### Window (Window.h)

**Purpose**: Window management and rendering context.

**Configuration**:

- Default size: 800x600 pixels
- Uses Raylib for window creation
- Supports window close detection
- Background color management

**Key Methods**:

- `Start(title)`: Create window with title
- `Update()`: Process window events
- `IsClosed()`: Check if window should close
- `GetSize()`: Get current window dimensions
- `Clear(color)`: Clear screen with color

### Input (Input.h)

**Purpose**: Keyboard input handling with state tracking.

**Supported Keys**:

- A-Z alphabet keys
- Arrow keys (Left, Up, Right, Down)
- Special keys (Space, Enter, Escape, Tab, One, Two)

**Input States**:

- `KeyDown(key)`: Currently pressed
- `KeyJustPressed(key)`: Pressed this frame
- `KeyJustReleased(key)`: Released this frame

**Features**:

- Frame-based input state tracking
- Previous frame state comparison
- Automatic state updates per frame

### TextureManager (TextureManager.h)

**Purpose**: Texture loading, caching, and render target management.

**Features**:

- Automatic texture caching by file path
- Render-to-texture support
- Memory management for loaded textures
- File path-based texture lookup

**Key Methods**:

- `Load(file_path)`: Load and cache texture
- `Unload()`: Free all loaded textures
- `StartRenderTextureMode(w, h)`: Begin render-to-texture
- `EndRenderTextureMode()`: End render-to-texture and return result

### Font (Font.h)

**Purpose**: Bitmap font rendering with custom font support.

**Features**:

- Custom bitmap font loading
- Character rectangle calculation
- Text-to-texture rendering
- Color support for text rendering

**Character Range**: Supports characters from space (' ') to 'z'

**Key Methods**:

- `Font(file_path)`: Load font from file
- `PrintToTexture(text, color)`: Render text to texture

---

## Game State Management

### GameStateManager (GameStateManager.h)

**Purpose**: Manages game state transitions and lifecycle.

**State Lifecycle**:

1. `STARTING`: Initialize state manager
2. `LOADING`: Load new game state
3. `UPDATING`: Normal game state updates
4. `UNLOADING`: Clean up current state
5. `STOPPING`: Prepare for shutdown
6. `EXIT`: Engine shutdown

**Features**:

- Automatic state transition handling
- State loading/unloading management
- Component access delegation
- Game end detection

**Key Methods**:

- `AddGameState(state)`: Register available state
- `SetNextGameState(index)`: Queue state transition
- `ReloadState()`: Reload current state
- `HasGameEnded()`: Check for game exit condition

### GameState (GameState.h)

**Purpose**: Abstract base class for all game states.

**Required Methods**:

- `Load()`: Initialize state resources
- `Update(dt)`: Per-frame state logic
- `Unload()`: Clean up state resources
- `Draw()`: Render state content
- `GetName()`: State identification

**Component Support**:

- Each state has its own ComponentManager
- Template methods for component access
- Automatic component lifecycle management

---

## GameObject System

### GameObject (GameObject.h)

**Purpose**: Base class for all game entities with transform, collision, and state machine support.

**Core Features**:

- Transform system (position, rotation, scale, velocity)
- Built-in collision detection
- State machine implementation
- Component system integration

**Required Overrides**:

- `Type()`: Return GameObjectTypes enum value
- `TypeName()`: Return string representation

**Transform Operations**:

- Position: `GetPosition()`, `SetPosition()`, `UpdatePosition()`
- Rotation: `GetRotation()`, `SetRotation()`, `UpdateRotation()`
- Scale: `GetScale()`, `SetScale()`, `UpdateScale()`
- Velocity: `GetVelocity()`, `SetVelocity()`, `UpdateVelocity()`

**Collision System**:

- `IsCollidingWith(object)`: Object-to-object collision
- `IsCollidingWith(point)`: Point collision test
- `CanCollideWith(type)`: Collision filtering
- `ResolveCollision(object)`: Collision response

**State Machine**:

- Abstract `State` class for behavior states
- `current_state`: Active state pointer
- `change_state(new_state)`: State transition

### GameObjectManager (GameObjectManager.h)

**Purpose**: Manages collections of GameObjects within game states.

**Responsibilities**:

- GameObject lifecycle management
- Batch updates and rendering
- Collision detection coordination
- Memory cleanup

**Key Methods**:

- `Add(object)`: Add GameObject to manager
- `UpdateAll(dt)`: Update all managed objects
- `DrawAll(camera_matrix)`: Render all objects
- `CollisionTest()`: Check collisions between objects
- `Unload()`: Clean up all objects

---

## Component System

### Component (Component.h)

**Purpose**: Base interface for all components.

**Interface**:

- `Update(dt)`: Per-frame component logic
- Virtual destructor for proper cleanup

### ComponentManager (ComponentManager.h)

**Purpose**: Manages component collections for GameObjects and GameStates.

**Features**:

- Template-based component access
- Dynamic component addition/removal
- Automatic memory management
- Type-safe component retrieval

**Key Methods**:

- `AddComponent(component)`: Add component instance
- `GetComponent<T>()`: Retrieve component by type
- `RemoveComponent<T>()`: Remove component by type
- `UpdateAll(dt)`: Update all components
- `Clear()`: Remove all components

---

## Graphics Components

### Sprite (Sprite.h)

**Purpose**: Sprite rendering component with animation support.

**Features**:

- Sprite sheet support
- Multi-frame animations
- Hot spot definition for positioning
- Frame-based animation playback

**Key Methods**:

- `Load(sprite_file, object)`: Load sprite data
- `Draw(matrix)`: Render sprite
- `PlayAnimation(index)`: Start animation
- `AnimationEnded()`: Check animation completion
- `GetHotSpot(index)`: Get frame positioning data
- `GetFrameSize()`: Get frame dimensions

### Animation (Animation.h)

**Purpose**: Frame-based animation system with commands.

**Animation Commands**:

- `PlayFrame`: Display specific frame for duration
- `Loop`: Jump to earlier command index
- `End`: Mark animation completion

**Features**:

- Command-based animation scripting
- Frame timing with delta time
- Loop support for repeating animations
- Animation completion detection

**Key Methods**:

- `Update(dt)`: Advance animation timing
- `CurrentFrame()`: Get active frame index
- `Reset()`: Restart animation
- `Ended()`: Check if animation finished

---

## Collision System

### Collision (Collision.h)

**Purpose**: Abstract base for collision detection components.

**Collision Shapes**:

- `RectCollision`: Axis-aligned rectangular collision
- `CircleCollision`: Circular collision detection

**Common Interface**:

- `Shape()`: Return collision shape type
- `Draw(matrix)`: Debug collision visualization
- `IsCollidingWith(object)`: Object collision test
- `IsCollidingWith(point)`: Point collision test

### RectCollision

**Features**:

- Axis-aligned bounding box collision
- World-space boundary calculation
- Rectangle-to-rectangle intersection
- Point-in-rectangle testing

### CircleCollision

**Features**:

- Circular collision bounds
- Distance-based collision detection
- Circle-to-circle intersection
- Point-in-circle testing

---

## Camera System

### Camera (Camera.h)

**Purpose**: 2D camera with player following and boundary limits.

**Features**:

- Player zone-based following
- Camera boundary limits
- Smooth position updates
- Transformation matrix generation

**Key Methods**:

- `SetPosition(pos)`: Direct camera positioning
- `Update(player_pos)`: Update camera to follow player
- `SetLimit(bounds)`: Set camera movement boundaries
- `GetMatrix()`: Get camera transformation matrix

---

## Graphics System

### Texture (Texture.h)

**Purpose**: Texture rendering and management with sprite sheet support.

**Key Features**:

- Built on Raylib's Texture2D system
- Move-only semantics (no copying)
- Support for full texture and partial texture rendering
- Color tinting support
- Integration with TextureManager for caching

**Key Methods**:

- `Draw(matrix, color)`: Render full texture with transformation
- `Draw(matrix, texel_pos, frame_size, color)`: Render specific region (sprite frames)
- `GetSize()`: Get texture dimensions as Math::ivec2

**Usage**:

```cpp
// Full texture rendering
texture->Draw(transform_matrix, 0xFFFFFFFF);

// Sprite frame rendering
texture->Draw(transform_matrix, {0, 0}, {32, 32}, 0xFFFFFFFF);
```

**Note**: Textures are managed by TextureManager and should not be created directly.

---

## Particle System

### Particle (Particle.h)

**Purpose**: Individual particle entity with lifecycle management.

**Lifecycle**:

- `Start(position, velocity, max_life)`: Initialize particle
- `Update(dt)`: Update position and decrease life
- `Alive()`: Check if particle is still active
- `Draw(camera_matrix)`: Render particle

**Inheritance**: Extends GameObject, requires sprite file in constructor

### ParticleManager<T> (Particle.h)

**Purpose**: Template-based particle pool manager for efficient particle systems.

**Template Requirements**:

- T must inherit from Particle
- T must define `static const int MaxCount` (pool size)
- T must define `static const double MaxLife` (particle lifetime)

**Key Features**:

- Pre-allocated particle pool for performance
- Circular buffer reuse of particles
- Automatic registration with GameObjectManager
- Configurable emission parameters

**Key Methods**:

- `Emit(count, position, velocity, direction, spread)`: Emit particles
  - `count`: Number of particles to emit
  - `position`: Emission origin
  - `velocity`: Base velocity for particles
  - `direction`: Direction vector for emission
  - `spread`: Angular spread in radians

**Usage**:

```cpp
// Define custom particle type
class MyParticle : public CS230::Particle {
public:
    static const int MaxCount = 100;
    static const double MaxLife = 2.0;
    MyParticle() : Particle("Assets/particle.spt") {}
    std::string TypeName() override { return "MyParticle"; }
};

// Use particle manager
CS230::ParticleManager<MyParticle>* particles;
particles->Emit(10, {100, 100}, {0, 0}, {1, 0}, 0.5);
```

---

## Mathematical Utilities

### Vec2 (Vec2.h)

**Purpose**: 2D vector mathematics for positions, velocities, and directions.

**Types**:

- `Math::vec2`: Double-precision floating point (x, y)
- `Math::ivec2`: Integer vector (x, y) with conversion to vec2

**Vec2 Operations**:

- Arithmetic: `+`, `-`, `*`, `/` with vectors and scalars
- Assignment: `+=`, `-=`, `*=`, `/=`
- Comparison: `==`, `!=`
- `Normalize()`: Convert to unit vector
- Unary minus: `-vec` for negation

**IVec2 Operations**:

- Same arithmetic operations as vec2
- Integer-specific operations with int scalars
- Double operations return vec2
- Explicit conversion: `static_cast<Math::vec2>(ivec)`

**Usage**:

```cpp
Math::vec2 position{100.0, 200.0};
Math::vec2 velocity{5.0, -3.0};
position += velocity * deltaTime;

Math::ivec2 grid_pos{10, 15};
Math::vec2 world_pos = static_cast<Math::vec2>(grid_pos) * 32.0;
```

### Matrix (Matrix.h)

**Purpose**: 2D transformation matrix system for graphics operations.

**Matrix Types**:

- `TransformationMatrix`: Base 3x3 transformation matrix
- `TranslationMatrix`: Translation transformation
- `ScaleMatrix`: Scale transformation
- `RotationMatrix`: Rotation transformation

**Key Operations**:

- Matrix multiplication: `matrix1 * matrix2`
- Vector transformation: `matrix * vector`
- Scalar multiplication: `matrix * scale`
- Assignment operators: `*=`
- Array access: `matrix[row][col]`
- `Reset()`: Set to identity matrix

**Usage**:

```cpp
// Compose transformations
Math::TransformationMatrix transform;
transform *= Math::TranslationMatrix(position);
transform *= Math::RotationMatrix(rotation);
transform *= Math::ScaleMatrix(scale);

// Transform vector
Math::vec2 transformed = transform * local_point;

// For rendering
sprite.Draw(transform);
```

### Rect (Rect.h)

**Purpose**: Rectangle utilities for bounds, collision, and area calculations.

**Types**:

- `Math::rect`: Double-precision rectangle (point_1, point_2)
- `Math::irect`: Integer rectangle (point_1, point_2)

**Key Methods**:

- `Left()`, `Right()`, `Top()`, `Bottom()`: Get boundary coordinates
- `Size()`: Get width/height as vector
- Rectangle is defined by two corner points

**Usage**:

```cpp
Math::rect bounds{{0.0, 0.0}, {100.0, 50.0}};
double width = bounds.Size().x;
double height = bounds.Size().y;

Math::irect collision_box{{-16, -16}, {16, 16}};
if (point.x >= collision_box.Left() && point.x <= collision_box.Right()) {
    // Point is within horizontal bounds
}
```

---

## Utility Components

### Timer (Timer.h)

**Purpose**: Component-based countdown timer with automatic updates.

**Features**:

- Automatic countdown with delta time
- Reset to original duration
- Remaining time access (double and int)
- TickTock alternating boolean state

**Key Methods**:

- `Timer(max_time)`: Constructor with timer duration
- `Set(time)`: Set remaining time
- `Update(dt)`: Automatic countdown (called by component system)
- `Reset()`: Reset to original duration
- `TickTock()`: Returns alternating true/false based on timer state
- `Remaining()`: Get remaining time as double
- `RemainingInt()`: Get remaining time as integer

**Usage**:

```cpp
// As GameObject component
AddGOComponent(new CS230::Timer(5.0)); // 5 second timer

// In Update method
CS230::Timer* timer = GetGOComponent<CS230::Timer>();
if (timer->Remaining() <= 0) {
    // Timer expired
}

// For blinking effects
if (timer->TickTock()) {
    // Draw sprite
}
```

### ShowCollision (ShowCollision.h)

**Purpose**: Debug component for toggling collision visualization.

**Features**:

- Input-based toggle for collision visualization
- Global debug state management
- Integrates with GameObject collision drawing

**Key Methods**:

- `ShowCollision()`: Constructor (enables by default)
- `Update(dt)`: Check for toggle input
- `Enabled()`: Get current debug state

**Usage**:

```cpp
// Add to game state for debug visualization
AddGSComponent(new CS230::ShowCollision());

// Collision components automatically check this state for drawing
```

**Input**: Uses engine input system to toggle collision display (specific key binding in implementation)

---

## Game-Specific Engine Components

### Fonts Enumeration (Game/Fonts.h)

**Purpose**: Font index enumeration for accessing engine fonts.

**Available Fonts**:

- `Fonts::Simple`: Basic font (index 0)
- `Fonts::Outlined`: Outlined font (index 1)

**Usage**:

```cpp
// Access fonts through Engine
Engine::GetFont(Fonts::Simple).PrintToTexture("Hello", 0xFFFFFFFF);
Engine::GetFont(Fonts::Outlined).PrintToTexture("Title", 0xFF0000FF);
```

### Gravity Component (Game/Gravity.h)

**Purpose**: Physics component for applying gravitational forces to GameObjects.

**Features**:

- Simple gravity value storage
- Component-based physics integration
- Configurable gravity strength

**Key Methods**:

- `Gravity(value)`: Constructor with gravity strength
- `GetValue()`: Get current gravity value

**Usage**:

```cpp
// Add gravity to GameObject
AddGOComponent(new Gravity(-9.8)); // Downward gravity

// Access gravity in physics calculations
Gravity* gravity = GetGOComponent<Gravity>();
velocity.y += gravity->GetValue() * dt;
```

### ScreenWrap Component (Game/ScreenWrap.h)

**Purpose**: Component for wrapping GameObjects around screen boundaries.

**Features**:

- Automatic position wrapping when objects exit screen
- Reference to GameObject for position modification
- Component-based screen boundary management

**Key Methods**:

- `ScreenWrap(object)`: Constructor with GameObject reference
- `Update(dt)`: Automatic boundary checking and wrapping

**Usage**:

```cpp
// Add screen wrapping to GameObject
AddGOComponent(new ScreenWrap(*this));

// Component automatically handles wrapping in Update()
```

### Particle Type Definitions (Game/Particles.h)

**Purpose**: Concrete particle implementations demonstrating ParticleManager usage.

**Available Particle Types**:

**Smoke Particles**:

- Sprite: "Assets/Smoke.spt"
- Max Count: 3 particles
- Max Life: 5.0 seconds
- Usage: Long-lasting smoke effects

**Hit Particles**:

- Sprite: "Assets/Hit.spt"
- Max Count: 10 particles
- Max Life: 1.0 seconds
- Usage: Impact and collision effects

**MeteorBit Particles**:

- Sprite: "Assets/MeteorBit.spt"
- Max Count: 150 particles
- Max Life: 1.25 seconds
- Usage: Explosion debris and meteor fragments

**Usage Example**:

```cpp
// Use predefined particle types
CS230::ParticleManager<Particles::Smoke>* smoke_manager;
CS230::ParticleManager<Particles::Hit>* hit_manager;
CS230::ParticleManager<Particles::MeteorBit>* meteor_manager;

// Emit particles
smoke_manager->Emit(1, explosion_pos, {0, 0}, {0, 1}, 0.0);
hit_manager->Emit(5, impact_pos, {0, 0}, {1, 0}, 1.57); // 90 degree spread
meteor_manager->Emit(50, meteor_pos, meteor_vel, {0, -1}, 3.14); // 180 degree spread
```

---

## Engine Implementation Details

### Debug Configuration

The engine automatically adjusts logging levels based on build configuration:

- **Debug Build**: Logger severity set to `Debug` level
- **Release Build**: Logger severity set to `Event` level

### Random Number Generation

The engine initializes a random seed in `Engine::Start()`:

- Uses current time as seed: `srand(time(NULL))`
- Logs the seed value for debugging reproducibility
- Used by particle systems for random velocity variations

### Frame Rate Management

The engine implements fixed timestep with target 30 FPS:

- Delta time calculation using `std::chrono`
- Frame skipping when system can't maintain target rate
- Verbose logging of engine updates

### File Output

Logger automatically creates "Trace.log" file for debugging:

- All log messages written to file
- Console output configurable via constructor
- Automatic file flushing and closing on destruction

---

## Usage Patterns

### Creating a New GameObject

```cpp
class MyGameObject : public CS230::GameObject {
public:
    MyGameObject(Math::vec2 pos) : GameObject(pos) {
        // Add components
        AddGOComponent(new CS230::Sprite("path/to/sprite.spt", this));
        AddGOComponent(new CS230::RectCollision({0, 0, 32, 32}, this));
    }

    GameObjectTypes Type() override { return GameObjectTypes::MyType; }
    std::string TypeName() override { return "MyGameObject"; }
};
```

### Creating a New Game State

```cpp
class MyGameState : public CS230::GameState {
public:
    void Load() override {
        AddGSComponent(new CS230::GameObjectManager());
        // Initialize state
    }

    void Update(double dt) override {
        UpdateGSComponents(dt);
        // State-specific logic
    }

    void Draw() override {
        // Render state content
    }

    void Unload() override {
        ClearGSComponents();
    }

    std::string GetName() override { return "MyGameState"; }
};
```

---

## Engine Initialization

The typical engine startup sequence:

1. Create Engine instance
2. Add fonts with `AddFont()`
3. Register game states with GameStateManager
4. Call `Engine::Start()` with window title
5. Main loop calls `Engine::Update()` until `HasGameEnded()`
6. Call `Engine::Stop()` for cleanup