#pragma once

namespace liminal {

// Size of the rendered landscape in pixels. This is deliberately separate from the
// window size (WindowProperties): in debug builds the window is wider because of the
// debug panel, but the scene, and therefore everything generated from it, must stay
// the same in debug and release builds.
struct SceneSize {
    float width;
    float height;
};

} // namespace liminal
