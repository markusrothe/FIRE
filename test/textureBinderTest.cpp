#include <gtest/gtest.h>
#include "fire/textureBinder.h"
#include "fire/texture.h"
#include "fire/renderable.h"

namespace
{
    Fire::Renderable renderable("dummy");

    class TextureStub : public Fire::Texture
    {
    public:
        TextureStub(): m_bound(false) { }
        void Bind() { m_bound = true; }
        void Unbind() { m_bound = false; }
        bool Bound() const{ return m_bound; }
    private:
        bool m_bound;
    };

    TextureStub texture;
    
    class TextureBinderTest : public ::testing::Test
    {
    public:
        TextureBinderTest()
            : m_texBinder()
        {
            renderable.AddTexture(&texture);
        }
        
        Fire::TextureBinder m_texBinder;
        
    };
} // namespace

TEST_F(TextureBinderTest, BindsATexture)
{    
    m_texBinder.Bind(&renderable);
    
    EXPECT_TRUE(texture.Bound());
}

TEST_F(TextureBinderTest, UnbindsABoundTexture)
{
    m_texBinder.Bind(&renderable);
    m_texBinder.Unbind(&renderable);

    EXPECT_FALSE(texture.Bound());
}
