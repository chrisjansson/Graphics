#ifndef UNIFORM_H
#define UNIFORM_H

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "UniformUploaders.h"

template <class T>
class Uniform
{
public:
	Uniform() {}
	Uniform(GLint location) : _location(location) {}
	Uniform(GLint location, T value) : _location(location), _value(value) {}

	T GetUniform()
	{
		return _value;
	}

	void SetUniform(T newValue)
	{
		_value = newValue;
	}

	void Upload()
	{
		UploadUniform(_location, _value);
	}

	void Upload(T newValue)
	{
		SetUniform(newValue);
		Upload();
	}
private:
	T _value;
	GLint _location;
};

#endif