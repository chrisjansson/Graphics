#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

smooth out vec4 interpColor;

uniform mat4 cameraToClipMatrix;

uniform vec4 lightPosition;
uniform vec4 lightIntensity;

uniform mat4 modelToCameraMatrix;
uniform mat3 normalModelToCameraMatrix;

vec3 diffuseColor;

void main()
{
	vec4 cameraPosition = (modelToCameraMatrix * vec4(position, 1.0));
	gl_Position = cameraToClipMatrix * cameraPosition;

	vec3 normCamSpace = normalize(normalModelToCameraMatrix * normal);
	
	vec3 realDirection = (normalize(lightPosition - cameraPosition)).xyz;

	float cosAngIncidence = dot(normCamSpace, realDirection);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	vec4 lightToVertex = normalize(cameraPosition - lightPosition);

	vec4 spotDirectionInCameraSpace = normalize(modelToCameraMatrix * vec4(0.0, 0.0, -1.0, 0.0));
	float spotEffect = dot(lightToVertex, spotDirectionInCameraSpace);

	if(spotEffect < 0.75) 
	{
		cosAngIncidence = 0.0;
	}
		
	diffuseColor.x = (position.x + 64) / 128;
	diffuseColor.y = (position.y + 64) / 128;
	diffuseColor.z = 1.0; //(position.z + 10) / 20;
	//diffuseColor = vec3(1.0, 1.0, 1.0);
	
	interpColor = vec4(diffuseColor, 1.0) * lightIntensity * cosAngIncidence + vec4(diffuseColor * vec3(0.2, 0.2, 0.2), 1.0); 
}
