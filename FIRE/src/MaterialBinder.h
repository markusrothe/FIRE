#ifndef FIRE_MATERIALBINDER_H
#define FIRE_MATERIALBINDER_H

namespace FIRE
{
class Material;
class MaterialBinder
{
public:
    virtual ~MaterialBinder() = default;
    virtual void Bind(Material& material) = 0;
    virtual void Release() = 0;
};
} // namespace FIRE

#endif //FIRE_MATERIALBINDER_H
