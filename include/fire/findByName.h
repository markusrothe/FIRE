#ifndef fire_findbyname_h
#define fire_findbyname_h

#include <algorithm>
#include <functional>
#include <string>

namespace Fire
{
template <typename Collection>
typename Collection::value_type FindByName(
    Collection collection, std::string const& name,
    std::function<std::string(typename Collection::value_type)> nameAccessor)
{
    auto const foundIt = std::find_if(
        std::begin(collection), std::end(collection),
        [&](typename Collection::value_type entry) {
            return name.compare(nameAccessor(entry)) == 0;
        });

    return foundIt != std::end(collection) ? *foundIt
                                           : typename Collection::value_type{};
}
} // namespace Fire

#endif // fire_findbyname_h
