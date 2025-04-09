# Brașov History Museum 3D Virtual Tour
This project is a 3D virtual tour application of the Brașov History Museum, created using OpenGL and C++. The application allows users to explore a detailed 3D model of the museum and view various historical artifacts in an immersive environment.

## Overview
The virtual tour provides a realistic representation of the museum with three distinct rooms, each showcasing different historical artifacts and exhibits from Romanian history. The application features detailed 3D models, dynamic lighting, shadows, and an intuitive first-person navigation system.

## Key Features
- **Immersive 3D Environment**: Explore a detailed 3D model of the Brașov History Museum
- **Interactive Navigation**: Move freely through the museum using first-person camera controls (WASD keys for movement, mouse for looking around)
- **Historical Artifacts**: View detailed 3D models of historical objects including:
  - Famous historical figures like Vlad Tepes (Dracula)
  - Medieval armors and weapons
  - Ancient documents and scrolls
  - Historical scientific instruments like telescopes
  - Antique furniture and household items
- **Dynamic Lighting System**: Features three light sources with different colors and intensities that create a realistic museum atmosphere
- **Shadow Mapping**: Implements shadow mapping techniques for realistic shadows
- **Rotating Exhibits**: Some exhibits (like the Vlad Tepes statue and telescope) rotate to provide a better viewing experience

## Technical Implementation
The project is built using modern C++ and OpenGL, with the following components:

- **GLFW**: For window management and input handling
- **GLEW**: OpenGL extension loading
- **GLM**: Mathematics library for 3D transformations
- **TinyOBJ**: For loading 3D models
- **STB Image**: For texture loading

The architecture follows an object-oriented design with classes for:
- **Application**: Main application class handling the window and game loop
- **Scene**: Manages all models, lighting, and shadow maps
- **Camera**: First-person camera with collision detection
- **Model**: Handles loading and rendering 3D models
- **Mesh**: Represents geometric data for rendering
- **Shader**: GLSL shader program management
- **Texture**: Texture loading and management
- **Light**: Light source properties and parameters

## Controls
- **W, A, S, D**: Move forward, left, backward, right
- **Mouse**: Look around
- **Escape**: Exit the application
- **L**: Enable lights
- **O**: Disable lights

## Special Exhibit Areas
1. **Room 1**: Features antique items including an old chest, vintage camera, cash register, old telephone, and a medieval desk with a Torah scroll
2. **Room 2**: Displays military artifacts including swords, an old wooden cart, and a ship cannon
3. **Room 3**: Houses Romanian historical items including Vlad Tepes statue, Bran Castle model, Romanian coat of arms, and medieval weaponry

Experience the rich history of Brașov through this virtual museum tour!
