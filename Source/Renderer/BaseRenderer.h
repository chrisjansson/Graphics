#ifndef BASE_RENDERER_H
#define BASE_RENDERER_H

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ProjectionTypeEnum 
{
	Orthographic,
	Perspective
};

struct ProjectionSettings 
{
	ProjectionSettings() 
	{
		ProjectionType = Perspective; 
		FieldOfView = 50.f;
		NearPlane = 1.f;
		FarPlane = 500.f;

		Left = -1.f;
		Right = 1.f;
		Top = 1.f;
		Bottom = -1.f;
	}

	ProjectionTypeEnum ProjectionType;
	float FieldOfView;
	float NearPlane;
	float FarPlane;

	float Left;
	float Right;
	float Top;
	float Bottom;
};

class BaseRenderer
{
public:
	BaseRenderer(ProjectionSettings projectionSettings);
	void ReSize(int width, int height);

	virtual void Render(float elapsedTime) = 0;
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
protected:
	glm::mat4 _projectionMatrix;
private:
	ProjectionSettings _settings;
	virtual void ProjectionMatrixChanged() = 0;
};

#endif