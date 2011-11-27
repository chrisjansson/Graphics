#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

smooth out vec4 interpColor;

uniform mat4 cameraToClipMatrix;

uniform vec3 dirToLight;
uniform vec4 lightIntensity;

uniform mat4 modelToCameraMatrix;
uniform mat3 normalModelToCameraMatrix;

vec3 diffuseColor;

void main()
{
	gl_Position = cameraToClipMatrix * (modelToCameraMatrix * vec4(position, 1.0));

	vec3 normCamSpace = normalize(normalModelToCameraMatrix * normal);
	
	float cosAngIncidence = dot(normCamSpace, dirToLight);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	diffuseColor.x = (position.x + 64) / 128;
	diffuseColor.y = (position.y + 64) / 128;
	diffuseColor.z = 1.0; //(position.z + 10) / 20;
	
	interpColor = vec4(diffuseColor, 1.0) * lightIntensity * cosAngIncidence;
}
