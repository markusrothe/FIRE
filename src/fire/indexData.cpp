#include "indexData.h"

namespace Fire
{
    std::vector<unsigned int> const& IndexData::GetIndices() const
    {
	return m_indices;
    }

    void IndexData::AddIndex(unsigned int idx)
    {
	m_indices.push_back(idx);
    }
    
    void IndexData::AddIndices(std::initializer_list<unsigned int> const& indices)
    {
	m_indices.insert(m_indices.end(), indices.begin(), indices.end());
    }
} // namespace Fire
