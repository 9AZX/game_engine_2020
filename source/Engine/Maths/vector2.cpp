#include "Engine/Maths/Vector2.hpp"

bool Engine::Math::vec2f::operator == (const vec2f & other) const noexcept
{
    return x == other.x && y == other.y;
}
