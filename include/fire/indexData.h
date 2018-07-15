#ifndef fire_indexdata_h
#define fire_indexdata_h

#include <vector>

namespace Fire
{
class IndexData
{
public:
    std::vector<unsigned int> const& GetIndices() const;
    void AddIndex(unsigned int idx);
    void AddIndices(std::initializer_list<unsigned int> const& indices);

private:
    std::vector<unsigned int> m_indices;
};
} // namespace Fire

#endif // fire_indexdata_h
