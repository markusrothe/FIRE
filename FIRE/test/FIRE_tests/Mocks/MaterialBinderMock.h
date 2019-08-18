#ifndef FIRE_MATERIALBINDERMOCK_H
#define FIRE_MATERIALBINDERMOCK_H

#include "MaterialBinder.h"
#include <gmock/gmock.h>

namespace FIRE_tests
{
class MaterialBinderMock : public FIRE::MaterialBinder
{
public:
    MOCK_METHOD1(Bind, void(FIRE::Material&));
    MOCK_METHOD0(Release, void(void));
};
} // namespace FIRE_tests

#endif //FIRE_MATERIALBINDERMOCK_H
