#include <FIRE/Mesh.h>
#include <FIRE/Vertex.h>
#include <gtest/gtest.h>
#include <string>
namespace
{
std::string const name{"name"};

class MeshTest : public ::testing::Test
{
public:
protected:
    FIRE::Mesh mesh{name};
};

} // namespace

TEST_F(MeshTest, HasAName)
{
    EXPECT_EQ(name, mesh.Name());
}

TEST_F(MeshTest, AddVerticesIndividually)
{
    mesh.AddVertex(FIRE::Vertex{});
    EXPECT_EQ(1u, mesh.Vertices().size());
}

TEST_F(MeshTest, AddVerticesGrouped)
{
    mesh.AddVertices({{0.0f, 1.0f, 2.0f}, {4.0f, 3.0f, 0.0f}});
    EXPECT_EQ(2u, mesh.Vertices().size());
}

TEST_F(MeshTest, AddIndicesIndividually)
{
    mesh.AddVertex(FIRE::Vertex{});
    mesh.AddIndex(0);
    EXPECT_EQ(1u, mesh.Indices().size());
}

TEST_F(MeshTest, AddIndicesGrouped)
{
    mesh.AddVertices({{0.0f, 1.0f, 2.0f},
                      {4.0f, 3.0f, 0.0f},
                      {4.0f, 3.0f, 0.0f},
                      {4.0f, 3.0f, 0.0f},
                      {4.0f, 3.0f, 0.0f}});
    mesh.AddIndices({0, 1, 2, 3, 4});
    EXPECT_EQ(5u, mesh.Indices().size());
}

TEST_F(MeshTest, AccessVerticesAsArray)
{
    mesh.AddVertices({{0.0f, 1.0f, 2.0f}, {3.0f, 4.0f, 5.0f}});
    auto const verticesVec = mesh.Vertices();

    auto vertices = mesh.VerticesAsArray();
    ASSERT_EQ(6u, vertices.size());
    EXPECT_FLOAT_EQ(verticesVec[0].x, vertices[0]);
    EXPECT_FLOAT_EQ(verticesVec[0].y, vertices[1]);
    EXPECT_FLOAT_EQ(verticesVec[0].z, vertices[2]);
    EXPECT_FLOAT_EQ(verticesVec[1].x, vertices[3]);
    EXPECT_FLOAT_EQ(verticesVec[1].y, vertices[4]);
    EXPECT_FLOAT_EQ(verticesVec[1].z, vertices[5]);
}

TEST_F(MeshTest, HasAVertexDeclaration)
{
    auto& vDecl = mesh.GetVertexDeclaration();

    std::string const attributeName{"vPos"};
    auto const size = 3u * sizeof(float);
    auto const offset = 0u;
    auto const stride = 3u * sizeof(float);
    vDecl.AddSection(attributeName, size, offset, stride);

    auto sections = vDecl.GetSections();
    ASSERT_EQ(1u, sections.size());
    EXPECT_EQ(size, sections.at(attributeName).size);
    EXPECT_EQ(offset, sections.at(attributeName).offset);
    EXPECT_EQ(stride, sections.at(attributeName).stride);
}

using MeshDeathTest = MeshTest;
TEST_F(MeshDeathTest, IndicesCannotBeHigherThanVertexCount)
{
    mesh.AddVertex({0.0f, 0.0f, 0.0f});
    EXPECT_DEATH(mesh.AddIndices({0, 1}), "");
    EXPECT_DEATH(mesh.AddIndex(2), "");
}
