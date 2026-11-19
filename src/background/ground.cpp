#include "ground.hpp"
#include <raylib.h>
#include <cstdlib>

namespace liminal {

Ground::Ground(const GroundConfig& config) noexcept
    : config(config) {}

} // namespace liminal