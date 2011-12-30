#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

smooth out vec3 interpColor;
smooth out vec4 cameraSpacePosition;
smooth out vec3 vertexNormal;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

vec3 diffuseColor;
void main()
{
	cameraSpacePosition = (modelToCameraMatrix * vec4(position, 1.0));
	gl_Position = cameraToClipMatrix * cameraSpacePosition;

	vertexNormal = normal;
	//
	//diffuseColor.x = (position.x + 64) / 128;
	//diffuseColor.y = (position.y + 64) / 128;
	//diffuseColor.z = 1.0; //(position.z + 10) / 20;
	
	if(position.z < -2.5)
		diffuseColor = vec3(0.0, 0.0, 0.5);
	else if(position.z >= -2.5 && position.z < 0.0)
		diffuseColor = vec3(0.0, 0.0, 1.0);
	else if(position.z >= 0.0 && position.z < 0.625)
		diffuseColor = vec3(0.0, 0.5, 1.0);
	else if(position.z >= 0.625 && position.z < 1.25)
		diffuseColor = vec3(0.9, 0.9, 0.2);
	else if(position.z >= 1.25 && position.z < 3.75)
		diffuseColor = vec3(0.1, 0.6, 0.0);
	else if(position.z >= 3.75 && position.z < 7.5)
		diffuseColor = vec3(0.5, 0.5, 0.5);
	else if(position.z >= 7.5 && position.z <= 10.0)
		diffuseColor = vec3(1.0, 1.0, 1.0);

	//diffuseColor = vec3(0.8, 0.8, 0.8);

	interpColor = diffuseColor; //vec4(diffuseColor, 1.0) * lightIntensity * cosAngIncidence + vec4(diffuseColor * vec3(0.2, 0.2, 0.2), 1.0); 
}
