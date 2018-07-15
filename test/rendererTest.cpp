#include "fire/renderer.h"
#include "fire/binder.h"
#include "fire/material.h"
#include "fire/renderable.h"
#include "fire/renderingDelegate.h"
#include "fire/vertexData.h"
#include "fire/vertexDeclaration.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <utility>
#include <vector>

namespace
{
using namespace ::testing;

Fire::VertexData vertexData;
Fire::VertexDeclaration vertexDecl;
Fire::Renderable testRenderable("name", nullptr);

class RenderingDelegateMock : public Fire::RenderingDelegate
{
public:
    MOCK_METHOD1(Bind, void(Fire::Renderable*));
    MOCK_METHOD1(Render, void(Fire::Renderable*));
    MOCK_METHOD1(Unbind, void(Fire::Renderable*));
};

class BinderMock : public Fire::Binder
{
public:
    MOCK_CONST_METHOD1(Bind, void(Fire::Renderable*));
    MOCK_CONST_METHOD1(Unbind, void(Fire::Renderable*));
};

class RendererTest : public Test
{
public:
    RendererTest()
        : m_renderingDelegateMock(
              std::make_unique<NiceMock<RenderingDelegateMock>>())
        , m_textureBinderMock(std::make_unique<NiceMock<BinderMock>>())
        , m_materialBinderMock(std::make_unique<NiceMock<BinderMock>>())
        , m_renderingDelegate(m_renderingDelegateMock.get())
        , m_textureBinder(m_textureBinderMock.get())
        , m_materialBinder(m_materialBinderMock.get())
        , m_renderer(
              std::move(m_renderingDelegateMock),
              std::move(m_textureBinderMock), std::move(m_materialBinderMock))
    {
    }

    void ExpectRenderCall(Fire::Renderable* renderable)
    {
        EXPECT_CALL(*m_renderingDelegate, Render(renderable)).Times(1);
    }

    void
    ExpectBindBeforeRendering(BinderMock* binder, Fire::Renderable* renderable)
    {
        InSequence ensureSequentialExpectations;
        EXPECT_CALL(*binder, Bind(renderable)).Times(1);
        ExpectRenderCall(renderable);
    }

    void
    ExpectUnbindAfterRendering(BinderMock* binder, Fire::Renderable* renderable)
    {
        InSequence ensureSequentialExpectations;
        ExpectRenderCall(renderable);
        EXPECT_CALL(*binder, Unbind(renderable)).Times(1);
    }

    void Render(Fire::Renderable* renderable)
    {
        auto renderableVec = {renderable};
        m_renderer.Render(renderableVec);
    }

private:
    std::unique_ptr<NiceMock<RenderingDelegateMock>> m_renderingDelegateMock;
    std::unique_ptr<NiceMock<BinderMock>> m_textureBinderMock;
    std::unique_ptr<NiceMock<BinderMock>> m_materialBinderMock;

protected:
    RenderingDelegateMock* m_renderingDelegate;
    BinderMock* m_textureBinder;
    BinderMock* m_materialBinder;

    Fire::Renderer m_renderer;
};

} // namespace

TEST_F(RendererTest, CanRenderRenderables)
{
    ExpectRenderCall(&testRenderable);
    Render(&testRenderable);
}

TEST_F(RendererTest, BindsTexturesBeforeRendering)
{
    ExpectBindBeforeRendering(m_textureBinder, &testRenderable);
    Render(&testRenderable);
}

TEST_F(RendererTest, UnbindsTexturesAfterRendering)
{
    ExpectUnbindAfterRendering(m_textureBinder, &testRenderable);
    Render(&testRenderable);
}

TEST_F(RendererTest, BindsMaterialsBeforeRendering)
{
    ExpectBindBeforeRendering(m_materialBinder, &testRenderable);
    Render(&testRenderable);
}

TEST_F(RendererTest, UnbindsMaterialsAfterRendering)
{
    ExpectUnbindAfterRendering(m_materialBinder, &testRenderable);
    Render(&testRenderable);
}
