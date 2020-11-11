#include "Engine/Maths/Vector3.hpp"

bool Engine::Math::vec3f::operator == (const vec3f & other) const noexcept
{
    return x == other.x && y == other.y && z == other.z;
}
