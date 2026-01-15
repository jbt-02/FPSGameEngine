🛠️ First Principles FPS Engine
Overview

This project is my first game engine, built from scratch with the goal of deeply understanding how game engines work under the hood.
The engine is designed specifically to support a basic first-person shooter (FPS) game.

Rather than using an existing engine like Unity or Unreal, this project focuses on learning and implementing core engine systems manually, including rendering, input handling, physics, and game logic.

## This is not meant to be a production-ready engine. It is a learning engine built to:

- Understand low-level systems

- Practice engine architecture

- Learn graphics programming

- Strengthen C++ and systems programming skills

## Goals

- Build a minimal but complete game engine

- Support a playable first-person shooter demo

- Learn how real engines are structured internally

- Avoid black-box abstractions as much as possible

## ✅ Development Checklist (In Order)

### 1️⃣ Project Foundation
- [ ] Create Git repository
- [ ] Set up CMake project
- [ ] Confirm build works on all machines
- [ ] Define folder structure
- [ ] Add `.gitignore`
- [ ] Create basic `main.cpp`

---

### 2️⃣ Core Engine Loop
- [ ] Implement engine `run()` loop
- [ ] Add delta time calculation
- [ ] Add frame rate limiting
- [ ] Implement graceful shutdown
- [ ] Create basic logging system

---

### 3️⃣ Window & Platform Layer
- [ ] Create window using GLFW
- [ ] Initialize OpenGL context
- [ ] Handle window resize events
- [ ] Handle window close events

---

### 4️⃣ Input System
- [ ] Keyboard input handling
- [ ] Mouse movement tracking
- [ ] Mouse lock / unlock for FPS camera
- [ ] Input state abstraction

---

### 5️⃣ Math System
- [ ] Vector2 implementation
- [ ] Vector3 implementation
- [ ] Matrix4 implementation
- [ ] Transform structure (position, rotation, scale)
- [ ] World → View → Projection math

---

### 6️⃣ Rendering Pipeline
- [ ] Initialize OpenGL
- [ ] Load and compile shaders
- [ ] Vertex buffer and index buffer setup
- [ ] Render a triangle
- [ ] Render a 3D cube
- [ ] Implement perspective projection
- [ ] Implement camera view matrix

---

### 7️⃣ First-Person Camera
- [ ] FPS camera class
- [ ] Mouse look (yaw / pitch)
- [ ] Keyboard movement (WASD)
- [ ] Movement speed control
- [ ] Basic camera collision

---

### 8️⃣ Entity System
- [ ] Entity ID system
- [ ] Transform component
- [ ] Mesh component
- [ ] Camera entity
- [ ] Scene update loop
- [ ] Scene render loop

---

### 9️⃣ Asset System
- [ ] Load shaders from files
- [ ] Texture loading
- [ ] Simple model loading (OBJ)
- [ ] Asset lifetime management

---

### 🔟 Physics & Collision
- [ ] Axis-Aligned Bounding Boxes (AABB)
- [ ] Player collision handling
- [ ] Gravity system
- [ ] Ground detection
- [ ] Basic raycasting

---

### 1️⃣1️⃣ Shooting Mechanics
- [ ] Shooting input handling
- [ ] Raycast weapon implementation
- [ ] Hit detection
- [ ] Debug ray visualization

---

### 1️⃣2️⃣ Enemy & Game Logic
- [ ] Enemy entity
- [ ] Basic AI movement
- [ ] Health component
- [ ] Enemy damage handling
- [ ] Enemy death logic

---

### 1️⃣3️⃣ Game Loop Integration
- [ ] Define update order (input → physics → logic → render)
- [ ] Pause system
- [ ] Level reset functionality
- [ ] Simple HUD / crosshair

---

### 1️⃣4️⃣ Debug & Tools
- [ ] FPS counter
- [ ] Debug overlays
- [ ] Wireframe rendering mode
- [ ] Improved logging

---

### 1️⃣5️⃣ Final Demo
- [ ] Create small FPS level
- [ ] Spawn multiple enemies
- [ ] Player shooting and collisions working
- [ ] Stable frame rate
- [ ] Capture screenshots / video for README
