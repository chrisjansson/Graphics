#include "BaseRenderer.h"

void BaseRenderer::ReSize(int width, int height)
{
	glViewport(0, 0, width, height);

	if(_settings.ProjectionType == ProjectionTypeEnum::Perspective) 
	{
		this->_projectionMatrix = glm::perspective(
			_settings.FieldOfView, 
			(float)width/(float)height, 
			_settings.NearPlane, 
			_settings.FarPlane);
	}
	else if(_settings.ProjectionType == ProjectionTypeEnum::Orthographic)
	{
		this->_projectionMatrix = glm::ortho(
			_settings.Left,
			_settings.Right,
			_settings.Bottom,
			_settings.Top,
			_settings.NearPlane,
			_settings.FarPlane);
	}
}