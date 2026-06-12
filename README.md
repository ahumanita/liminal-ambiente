# liminal-ambiente
A cozy computational ecosystem and ambient simulation sandbox written in C++.

## Dependencies

- CMake
- Raylib (libraylib-dev)
- C++

## Theories and methods behind the visuals

### Color palettes

The colors for each element type are based on color ramps consisting of a sequence of 8 related colors each, in the style of:

0. Deep shadow
1. Shadow
2. Dark
3. Mid
4. Light
5. Highlight
6. Atmosphere
7. Fog-tinted

Four base-palettes are defined for the four key daytimes: Dusk, dawn, day, night.
Each of these hold color ramps for the different materials (e.g. forest, grass, sky, ...).

For the specific time of day, two of these palettes are blended.

Besides the time of day, the world state controls the color grading parameters
brightness, saturation and contrast of the rendering.