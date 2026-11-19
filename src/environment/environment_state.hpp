#pragma once

namespace liminal {

// The world state: everything that is changed by the clock, the weather or the
// simulation (later: fed from the SMHI forecast). It is stored exactly once, and each
// element reads the fields it reacts to in update(dt, env). How strongly an element
// reacts is defined in its config, e.g. RainConfig::maxSpeedMultiplier.
struct EnvironmentState {
    float timeOfDay = 0.5f;       // 0.0 to 1.0, where 0.0 is midnight and 0.5 is noon
    float rainIntensity = 0.33f;  // 0.0 to 1.0, where 0.0 is no rain and 1.0 is heavy rain
    float fogDensity = 0.5f;      // 0.0 to 1.0, where 0.0 is clear and 1.0 is dense fog
    float windSpeed = 2.0f;       // Horizontal wind in pixels per second (placeholder until real units are decided)
    // Future additions are going to include:
    // float cloudCover;       // 0.0 to 1.0, where 0.0 is clear and 1.0 is stormy
};

} // namespace liminal
