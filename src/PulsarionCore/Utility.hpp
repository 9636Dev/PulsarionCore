#pragma once

#include <forward_list>

namespace Pulsarion
{
#define PULSARION_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
}
