#include <FIRE/Mesh.h>
#include <FIRE/Vector.h>
#include <gtest/gtest.h>
#include <string>
namespace
{
std::string const name{"name"};
std::initializer_list<FIRE::Vector3> const vecs = {
    {0.0f, 1.0f, 2.0f},
    {4.0f, 3.0f, 0.0f}};

class AMesh : public ::testing::Test
{
public:
protected:
    FIRE::Mesh mesh{name};
};

} // namespace

TEST_F(AMesh, HasAName)
{
    EXPECT_EQ(name, mesh.Name());
}

TEST_F(AMesh, AllowsToAddPositionsIndividually)
{
    mesh.AddPosition(FIRE::Vector3{});
    EXPECT_EQ(1u, mesh.Positions().size());
}

TEST_F(AMesh, AllowsToAddMultiplePositionsAtOnce)
{
    mesh.AddPositions(vecs);
    EXPECT_EQ(vecs.size(), mesh.Positions().size());
}

TEST_F(AMesh, AllowsToAccessPositionsAsAVectorOfFloats)
{
    mesh.AddPositions(vecs);
    auto const positionsVec = mesh.Positions();

    auto positions = mesh.PositionsAsArray();
    ASSERT_EQ(vecs.size() * 3, positions.size());
    EXPECT_FLOAT_EQ(positionsVec[0].x, positions[0]);
    EXPECT_FLOAT_EQ(positionsVec[0].y, positions[1]);
    EXPECT_FLOAT_EQ(positionsVec[0].z, positions[2]);
    EXPECT_FLOAT_EQ(positionsVec[1].x, positions[3]);
    EXPECT_FLOAT_EQ(positionsVec[1].y, positions[4]);
    EXPECT_FLOAT_EQ(positionsVec[1].z, positions[5]);
}

TEST_F(AMesh, AllowsToAddIndicesIndividually)
{
    mesh.AddPosition(FIRE::Vector3{});
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
    mesh.AddNormal(FIRE::Vector3{});
    EXPECT_EQ(1u, mesh.Normals().size());
}

TEST_F(AMesh, AllowsToAddMultipleNormalsAtOnce)
{
    mesh.AddNormals(vecs);
    EXPECT_EQ(vecs.size(), mesh.Normals().size());
}

TEST_F(AMesh, AllowsToAccessNormalsAsAVectorOfFloats)
{
    mesh.AddNormals(vecs);
    auto const normalsVec = mesh.Normals();

    auto normals = mesh.NormalsAsArray();
    ASSERT_EQ(vecs.size() * 3, normals.size());
    EXPECT_FLOAT_EQ(normalsVec[0].x, normals[0]);
    EXPECT_FLOAT_EQ(normalsVec[0].y, normals[1]);
    EXPECT_FLOAT_EQ(normalsVec[0].z, normals[2]);
    EXPECT_FLOAT_EQ(normalsVec[1].x, normals[3]);
    EXPECT_FLOAT_EQ(normalsVec[1].y, normals[4]);
    EXPECT_FLOAT_EQ(normalsVec[1].z, normals[5]);
}

TEST_F(AMesh, HasAVertexDeclaration)
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

using MeshDeathTest = AMesh;
TEST_F(MeshDeathTest, IndicesCannotBeHigherThanVertexCount)
{
    mesh.AddPosition({0.0f, 0.0f, 0.0f});
    EXPECT_DEATH(mesh.AddIndices({0, 1}), "");
    EXPECT_DEATH(mesh.AddIndex(2), "");
}
