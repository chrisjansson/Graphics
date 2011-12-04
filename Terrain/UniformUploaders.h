#ifndef UNIFORMUPLOADERS_H
#define UNIFORMUPLOADERS_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void UploadUniform(GLint location, glm::detail::tvec3<float> value);
void UploadUniform(GLint location, glm::detail::tvec4<float> value);

void UploadUniform(GLint location, glm::detail::tmat3x3<float> value);
void UploadUniform(GLint location, glm::detail::tmat4x4<float> value);

#endif