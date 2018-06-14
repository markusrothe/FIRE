#include "glslShader.h"

namespace Fire
{
	GLSLShader::GLSLShader(std::string name)
		: m_name(name)
		, m_bound(false)
	{

	}

    std::string const& GLSLShader::GetName() const
    {
        return m_name;
    }

    void GLSLShader::Bind()
    {
        m_bound = true;
    }
    
	void GLSLShader::Unbind()
	{
		m_bound = false;
	}

    bool GLSLShader::Bound() const
    {
        return m_bound;
    }
} // namespace Fire
