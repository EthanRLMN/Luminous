#version 450

layout (binding = 0) uniform UniformBufferObject {
	mat4 model;
	mat4 view;
	mat4 proj;
} ubo;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

layout (location = 0) out vec3 fragPos;
layout (location = 1) out vec3 fragNormal;
layout (location = 2) out vec2 fragTexCoord;
layout (location = 3) out vec3 viewPos;

void main(){
	gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition , 1.0);
	fragNormal = inNormal;
	fragTexCoord = inTexCoord;
	fragPos = vec3(ubo.model * vec4(inPosition, 1.0));
	viewPos = vec3(ubo.view[3][0],ubo.view[3][1],ubo.view[3][2]);
}