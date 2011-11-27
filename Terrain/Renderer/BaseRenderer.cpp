#include "BaseRenderer.h"

BaseRenderer::BaseRenderer(ProjectionSettings projectionSettings) 
{
	this->_settings = projectionSettings;
}

void BaseRenderer::ReSize(int width, int height)
{
	glViewport(0, 0, width, height);

	if(_settings.ProjectionType == Perspective) 
	{
		this->_projectionMatrix = glm::perspective(
			_settings.FieldOfView, 
			(float)width/(float)height, 
			_settings.NearPlane, 
			_settings.FarPlane);
	}
	else if(_settings.ProjectionType == Orthographic)
	{
		this->_projectionMatrix = glm::ortho(
			_settings.Left,
			_settings.Right,
			_settings.Bottom,
			_settings.Top,
			_settings.NearPlane,
			_settings.FarPlane);
	}

	ProjectionMatrixChanged();
}

