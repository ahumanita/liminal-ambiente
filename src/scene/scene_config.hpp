#pragma once

#include "background/mountain_config.hpp"
#include "background/sky_config.hpp"
#include "background/ground_config.hpp"
#include "natural_elements/rain_config.hpp"
#include "natural_elements/fog_config.hpp"
#include "natural_elements/forest_config.hpp"

namespace liminal {

// All configs of the scene in one place: how every element is generated and how it
// reacts to the world. This bundle (together with the EnvironmentState) is what a
// preset will save and load later (#14).
//
// It includes the element config headers, never the other way around, so the elements
// stay independent of each other and of the bundle.
//
// The elements keep a *copy* of their config when they are constructed: changing a
// field here afterwards has no effect until the element is regenerated from it.
struct SceneConfig {
    MountainConfig mountains;
    SkyConfig sky;
    GroundConfig ground;
    RainConfig rain;
    FogConfig fog;
    ForestConfig forest;
};

} // namespace liminal
