#version 460

layout(push_constant) uniform UBO_Constant {
	mat4 model;
	mat4 view;
	mat4 proj;
} uboConstant;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inColor;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec3 fragColor;

layout(location = 4) out vec3 viewPos;

void main() {
	gl_Position = uboConstant.proj * uboConstant.view * uboConstant.model * vec4(inPosition, 1.0);
	fragPos = vec3(uboConstant.model * vec4(inPosition, 1.0));
	fragNormal = mat3(uboConstant.model) * inNormal;
	fragTexCoord = inTexCoord;
	fragColor = inColor;

	mat4 invView = inverse(uboConstant.view);
	viewPos = vec3(invView[3]);
}