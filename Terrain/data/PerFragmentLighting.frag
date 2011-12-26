#version 330

smooth in vec3 interpColor;
smooth in vec4 cameraSpacePosition;
smooth in vec3 vertexNormal;

out vec4 outputColor;

uniform vec4 lightPosition;
uniform vec4 lightIntensity;

uniform mat3 normalModelToCameraMatrix;
uniform mat4 modelToCameraMatrix;

void main()
{
	vec3 normCamSpace = normalize(normalModelToCameraMatrix * vertexNormal);
	
	vec3 realDirection = (normalize(lightPosition - cameraSpacePosition)).xyz;

	float cosAngIncidence = dot(normCamSpace, realDirection);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	vec4 lightToVertex = normalize(cameraSpacePosition - lightPosition);

	vec4 spotDirectionInCameraSpace = normalize(modelToCameraMatrix * vec4(0.0, 0.0, -1.0, 0.0));
	float spotEffect = dot(lightToVertex, spotDirectionInCameraSpace);

	if(spotEffect < 0.75) 
	{
		cosAngIncidence = 0.0;
	}

	outputColor = (vec4(interpColor, 1.0) * lightIntensity * cosAngIncidence) + vec4(interpColor, 1.0) * vec4(0.2, 0.2, 0.2, 0.2);
}
