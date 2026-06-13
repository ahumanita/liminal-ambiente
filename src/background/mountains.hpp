#include <raylib.h>
#include <vector>

#include "color_palettes/scene_palette.hpp"
#include "gui/window_properties.hpp"

class Mountains {
public:
    Mountains(WindowProperties* props);
    ~Mountains();

    void draw(ScenePalette& palette);

private:
    std::vector<Vector2> ridgeLine; // Ridge line points for mountain shapes
    WindowProperties* windowProps; // To access screen dimensions for drawing
    int numRidgePoints = 8; // Number of control points for the ridge line
    int numRefinements = 3; // Number of times to refine the ridge line for smoother mountains
};