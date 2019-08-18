#include "ComponentStub.h"
#include "VertexLayoutStub.h"
#include <FIRE/Message.h>
#include <FIRE/Renderable.h>
#include <FIRE/RenderableSubmitter.h>
#include <FIRE/RenderingComponent.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/TextOverlay.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace FIRE;

namespace
{
class TestRenderingComponent : public RenderingComponent
{
public:
    explicit TestRenderingComponent(RenderableSubmitter& submitter, std::vector<Renderable> renderables)
        : RenderingComponent(submitter, std::move(renderables))
    {
    }

    std::optional<std::any> Receive(FIRE::Message const&, SceneObject&) override
    {
        return std::nullopt;
    }

    void DoUpdate(double, SceneObject&, Scene&) override
    {
        updated = true;
    }

    bool updated{false};
};

class RenderableSubmitterMock : public RenderableSubmitter
{
public:
    MOCK_METHOD1(Submit, void(Renderable const&));
};

class ARenderingComponent : public Test
{
public:
    ARenderingComponent()
        : scene{}
        , obj{scene.CreateSceneObject("")}
    {
        renderables.emplace_back("renderable0", Material(), nullptr);

        auto componentStub = std::make_unique<FIRE_tests::ComponentStub>();
        componentStub->AddMessageHandler(FIRE::Message(MessageID::GetViewMatrix), [] { return glm::mat4x4(2.0f); });
        componentStub->AddMessageHandler(FIRE::Message(MessageID::GetProjectionMatrix), [] { return glm::mat4x4(2.0f); });
        componentStub->AddMessageHandler(FIRE::Message(MessageID::GetLightPosition), [] { return glm::vec3({1.0f, 2.0f, 3.0f}); });
        obj.AddComponent(std::move(componentStub));
    }

    template <typename ParamType, typename ParamVal>
    static void EXPECT_SHADERPARAM_EQ(Material const& material, std::string const& paramName, ParamType type, ParamVal const& val)
    {
        auto const shaderParam = material.GetShaderParameter(paramName).value();
        ASSERT_THAT(shaderParam.first, Eq(type));
        ASSERT_THAT(std::any_cast<ParamVal>(shaderParam.second), Eq(val));
    }

    RenderableSubmitterMock renderableSubmitter;
    Scene scene;
    SceneObject& obj;
    std::vector<Renderable> renderables;
};

} // namespace

TEST_F(ARenderingComponent, UpdatesDerivedClasses)
{
    TestRenderingComponent derivedRenderingComponent(renderableSubmitter, {});
    derivedRenderingComponent.Update(0.0, obj, scene);
    ASSERT_THAT(derivedRenderingComponent.updated, IsTrue());
}

TEST_F(ARenderingComponent, SubmitsRenderables)
{
    EXPECT_CALL(renderableSubmitter, Submit(_));
    RenderingComponent renderingComponent(renderableSubmitter, renderables);
    renderingComponent.Update(0.0f, obj, scene);
}

TEST_F(ARenderingComponent, SetsTheModelMatrixShaderParameter)
{
    Renderable submittedRenderable;
    EXPECT_CALL(renderableSubmitter, Submit(_))
        .WillOnce(SaveArg<0>(&submittedRenderable));

    RenderingComponent renderingComponent(renderableSubmitter, renderables);
    renderingComponent.Update(0.0f, obj, scene);

    EXPECT_SHADERPARAM_EQ(submittedRenderable.material, "M", ShaderParameterType::MAT4x4, obj.GetTransform().ModelMatrix());
}

TEST_F(ARenderingComponent, SetsTheViewProjectionMatrixShaderParameter)
{
    Renderable submittedRenderable;
    EXPECT_CALL(renderableSubmitter, Submit(_))
        .WillOnce(SaveArg<0>(&submittedRenderable));

    RenderingComponent renderingComponent(renderableSubmitter, renderables);
    renderingComponent.Update(0.0f, obj, scene);

    EXPECT_SHADERPARAM_EQ(submittedRenderable.material, "VP", ShaderParameterType::MAT4x4, glm::mat4x4(4.0f));
}

TEST_F(ARenderingComponent, SetsTheLightPosShaderParameter)
{
    Renderable submittedRenderable;
    EXPECT_CALL(renderableSubmitter, Submit(_))
        .WillOnce(SaveArg<0>(&submittedRenderable));

    RenderingComponent renderingComponent(renderableSubmitter, renderables);
    renderingComponent.Update(0.0f, obj, scene);

    EXPECT_SHADERPARAM_EQ(submittedRenderable.material, "LightPos", ShaderParameterType::VEC3, glm::vec3(1.0f, 2.0f, 3.0f));
}