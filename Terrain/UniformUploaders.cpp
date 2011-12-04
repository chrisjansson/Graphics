#include "UniformUploaders.h"

void UploadUniform(GLint location, glm::detail::tvec3<float> value)
{
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void UploadUniform(GLint location, glm::detail::tmat4x4<float> value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void UploadUniform( GLint location, glm::detail::tvec4<float> value)
{
	glUniform4fv(location, 1, glm::value_ptr(value));
}

void UploadUniform( GLint location, glm::detail::tmat3x3<float> value )
{
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
