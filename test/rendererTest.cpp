#include "fire/renderer.h"
#include "fire/vertexData.h"
#include "fire/vertexDeclaration.h"
#include "fire/renderable.h"
#include "fire/renderingDelegate.h"
#include "fire/binder.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>
#include <utility>

namespace
{
    using namespace ::testing;
    
    Fire::VertexData vertexData;
    Fire::VertexDeclaration vertexDecl;
    Fire::Renderable testRenderable("name");
    
    class RenderingDelegateMock : public Fire::RenderingDelegate
    {
    public:
        MOCK_METHOD1(Render, void(Fire::Renderable*));
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
            : m_renderingDelegateMock(std::make_unique<RenderingDelegateMock>())
            , m_textureBinderMock(std::make_unique<BinderMock>())
            , m_materialBinderMock(std::make_unique<BinderMock>())
            , m_renderingDelegate(m_renderingDelegateMock.get())
            , m_textureBinder(m_textureBinderMock.get())
            , m_materialBinder(m_materialBinderMock.get())
            , m_renderer(std::move(m_renderingDelegateMock), std::move(m_textureBinderMock),
                         std::move(m_materialBinderMock))
        {
        }

        void ExpectRenderCall(Fire::Renderable* renderable)
        {
            EXPECT_CALL(*m_renderingDelegate, Render(renderable)).Times(1);
        }

        void ExpectBindBeforeRendering(BinderMock* binder, Fire::Renderable* renderable)
        {
            EXPECT_CALL(*binder, Bind(renderable)).Times(1);
            ExpectRenderCall(renderable);
        }

        void ExpectUnbindAfterRendering(BinderMock* binder, Fire::Renderable* renderable)
        {
            ExpectRenderCall(renderable);
            EXPECT_CALL(*binder, Unbind(renderable)).Times(1);
        }

        void CheckBindBeforeRendering(BinderMock* binder)
        {
            InSequence ensureSequentialExpectations;
            ExpectBindBeforeRendering(binder, &testRenderable);
            Render(&testRenderable);
        }

        void CheckUnbindAfterRendering(BinderMock* binder)
        {
            InSequence ensureSequentialExpectations;
            ExpectUnbindAfterRendering(binder, &testRenderable);
            Render(&testRenderable);
        }

        void Render(Fire::Renderable* renderable)
        {
            auto renderableVec = {renderable};
            m_renderer.Render(renderableVec);
        }

    private:
        std::unique_ptr<RenderingDelegateMock> m_renderingDelegateMock;
        std::unique_ptr<BinderMock> m_textureBinderMock;
        std::unique_ptr<BinderMock> m_materialBinderMock;
        
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
    CheckBindBeforeRendering(m_textureBinder);
}

TEST_F(RendererTest, UnbindsTexturesAfterRendering)
{
    CheckUnbindAfterRendering(m_textureBinder);
}

TEST_F(RendererTest, BindsMaterialsBeforeRendering)
{
    CheckBindBeforeRendering(m_materialBinder);
}

TEST_F(RendererTest, UnbindsMaterialsAfterRendering)
{
    CheckUnbindAfterRendering(m_materialBinder);
}

TEST_F(RendererTest, UploadsUniformsBeforeRendering)
{
    
}

/*
      EXPECT_CALL(m_textureBinder, Unbind()).Times(1);*/
