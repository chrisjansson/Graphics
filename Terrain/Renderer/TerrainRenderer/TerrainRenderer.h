#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "../BaseRenderer.h"

class TerrainRenderer : BaseRenderer
{
public:
	void Render();
	void Initialize();
	void Finalize();
private:
	void ProjectionMatrixChanged();
};

#endif