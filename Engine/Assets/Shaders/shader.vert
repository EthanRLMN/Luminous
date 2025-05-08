#version 460

layout(push_constant) uniform UBO_Constant {
	mat4 model;
	mat4 view;
	mat4 proj;
} uboConstant;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 viewPos;

void main() {
	gl_Position = uboConstant.proj * uboConstant.view * uboConstant.model * vec4(inPosition, 1.0);
	fragPos = vec3(uboConstant.model * vec4(inPosition, 1.0));
	fragNormal = mat3(uboConstant.model) * inNormal;
	fragTexCoord = inTexCoord;

	mat4 invView = inverse(uboConstant.view);
	viewPos = vec3(invView[3]);
}