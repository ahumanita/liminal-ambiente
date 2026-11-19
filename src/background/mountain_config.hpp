#pragma once

#include <cstddef> // for std::size_t
#include <cstdint> // for std::uint32_t

namespace liminal {

struct MountainConfig {
    std::uint32_t seed = 42; // Seed for the generator: the same seed always produces the same mountains
    std::size_t numLayers = 5; // Number of mountain layers to generate
    std::size_t numRidgePoints = 8; // Number of control points for the ridge line
    std::size_t numRefinements = 3; // Number of times to refine the ridge line
    float midpointDisplacement = 20.0f; // Maximum vertical offset for ridge points
    float roughness = 0.5f; // Factor to reduce vertical roughness after each refinement
    float nearElevation = 200.0f; // Elevation of the nearest mountain layer
    float farElevation = 400.0f; // Elevation of the farthest mountain
    float nearAmplitude = 50.0f; // Amplitude of the nearest mountain layer
    float farAmplitude = 100.0f; // Amplitude of the farthest mountain
};

} // namespace liminal
