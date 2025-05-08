#version 460

layout (binding = 0) uniform UniformBufferObject {
	mat4 model;
	mat4 view;
	mat4 proj;
} ubo;

layout( push_constant ) uniform UBO_Constant
{
	mat4 model;
	mat4 view;
	mat4 proj;
} uboConstant;


layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

layout (location = 0) out vec3 fragPos;
layout (location = 1) out vec3 fragNormal;
layout (location = 2) out vec2 fragTexCoord;
layout (location = 3) out vec3 viewPos;

void main(){
	gl_Position = uboConstant.proj * uboConstant.view * transpose(uboConstant.model) * vec4(inPosition , 1.0);
	fragNormal = inNormal;
	fragTexCoord = inTexCoord;
	fragPos = vec3(uboConstant.model * vec4(inPosition, 1.0));
	viewPos = vec3(uboConstant.view[3][0],uboConstant.view[3][1],uboConstant.view[3][2]);
}
