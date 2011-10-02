#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

struct VertexPositionNormal
{
	glm::vec3 Position;
	glm::vec3 Normal;
};

const float* PointsFromData(const float* data, int width, int height);
const float* LinesFromData(const float* data, int width, int height);
const float* TrianglesFromData(const float* data, int width, int height);
const glm::vec3* TrianglesFromDataGLM(const float* data, int width, int height);
void VerticesAndIndicesFromData(const float* data, int width, int height, VertexPositionNormal** vertices, GLuint** indices);