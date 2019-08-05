#ifndef FIRE_GLMATERIALBINDER_H
#define FIRE_GLMATERIALBINDER_H
#include "MaterialBinder.h"
namespace FIRE
{
class GLMaterialBinder : public MaterialBinder
{
public:
    void Bind(Material& material) override;
    void Release() override;
};
} // namespace FIRE
#endif //FIRE_GLMATERIALBINDER_H
