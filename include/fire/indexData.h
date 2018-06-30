#ifndef fire_indexdata_h
#define fire_indexdata_h

#include <vector>

namespace Fire
{
    class IndexData
    {
    public:
	std::vector<unsigned int> GetIndices() const;
	
    private:
	std::vector<unsigned int> m_indices;
    };
}

#endif // fire_indexdata_h
