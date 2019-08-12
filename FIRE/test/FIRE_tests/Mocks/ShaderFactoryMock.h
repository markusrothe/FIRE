#ifndef FIRE_SHADERFACTORYMOCK_H
#define FIRE_SHADERFACTORYMOCK_H
#include <ShaderFactory.h>
#include <gmock/gmock.h>
namespace FIRE_tests
{

class ShaderFactoryMock : public FIRE::ShaderFactory
{
public:
    MOCK_METHOD0(CreateDefaultShader, unsigned int(void));
    MOCK_METHOD0(CreateDefaultTextShader, unsigned int(void));
    MOCK_METHOD1(Create, unsigned int(FIRE::Shaders const&));
};

} // namespace FIRE_tests

#endif //FIRE_SHADERFACTORYMOCK_H
