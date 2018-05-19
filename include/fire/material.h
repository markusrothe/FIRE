#ifndef fire_material_f
#define fire_material_f

#include <string>

namespace Fire
{
    class Material
    {
    public:
        explicit Material(std::string const& name);
        
        std::string GetName() const;

        void Bind();
        void Unbind();

        bool IsBound() const;
    private:
        std::string const m_name;
        bool m_bound;
    };
} // namespace Fire

#endif // fire_material_f
