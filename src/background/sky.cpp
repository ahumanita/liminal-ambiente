#include "sky.hpp"
#include <raylib.h>
#include <cstdlib>

namespace liminal {

Sky::Sky(const SkyConfig& config) noexcept
    : config(config) {}

} // namespace liminal