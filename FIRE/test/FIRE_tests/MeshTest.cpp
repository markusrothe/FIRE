#include <FIRE/Mesh3D.h>
#include <gtest/gtest.h>
#include <string>
namespace
{
std::string const name{"name"};
std::vector<glm::vec3> const vecs = {
    {0.0f, 1.0f, 2.0f},
    {4.0f, 3.0f, 0.0f}};

class AMesh : public ::testing::Test
{
public:
protected:
    FIRE::Mesh3D mesh{name, FIRE::MeshType(FIRE::MeshCategory::Custom, FIRE::MeshPrimitives::Triangles)};
};

} // namespace

TEST_F(AMesh, HasAName)
{
    EXPECT_EQ(name, mesh.Name());
}

TEST_F(AMesh, AllowsToAddPositionsIndividually)
{
    mesh.AddPosition(glm::vec3{});
    EXPECT_EQ(1u, mesh.Positions().size());
}

TEST_F(AMesh, AllowsToAddMultiplePositionsAtOnce)
{
    mesh.AddPositions(vecs);
    EXPECT_EQ(vecs.size(), mesh.Positions().size());
}

TEST_F(AMesh, AllowsToAddIndicesIndividually)
{
    mesh.AddPosition(glm::vec3{});
    mesh.AddIndex(0);
    EXPECT_EQ(1u, mesh.Indices().size());
}

TEST_F(AMesh, AllowsToAddMultipleIndicesAtOnce)
{
    mesh.AddPositions(vecs);
    mesh.AddIndices({0, 1});
    EXPECT_EQ(2u, mesh.Indices().size());
}

TEST_F(AMesh, AllowsToAddNormalsIndividually)
{
    mesh.AddNormal(glm::vec3{});
    EXPECT_EQ(1u, mesh.Normals().size());
}

TEST_F(AMesh, AllowsToAddMultipleNormalsAtOnce)
{
    mesh.AddNormals(vecs);
    EXPECT_EQ(vecs.size(), mesh.Normals().size());
}

TEST_F(AMesh, AllowsToAddUVsIndividually)
{
    mesh.AddUV(glm::vec2{});
    EXPECT_EQ(1u, mesh.UVs().size());
}

TEST_F(AMesh, AllowsToAddMultipleUVsAtOnce)
{
    mesh.AddUVs({{0.0f, 1.0f}, {1.0f, 0.0f}});
    EXPECT_EQ(vecs.size(), mesh.UVs().size());
}

TEST_F(AMesh, HasAVertexDeclaration)
{
    auto& vDecl = mesh.GetVertexDeclaration();

    std::string const attributeName{"vPos"};
    auto const size = 3u * sizeof(float);
    auto const offset = 42u;
    vDecl.AddSection(attributeName, size, offset);

    auto const sections = vDecl.GetSections();
    ASSERT_EQ(1u, sections.size());
    EXPECT_EQ(size, sections.at(attributeName).size);
    EXPECT_EQ(offset, sections.at(attributeName).offset);
}

TEST_F(AMesh, HasAMeshType)
{
    auto const meshType = mesh.GetMeshType();
    EXPECT_EQ(FIRE::MeshCategory::Custom, meshType.category);
    EXPECT_EQ(FIRE::MeshPrimitives::Triangles, meshType.primitives);
}
