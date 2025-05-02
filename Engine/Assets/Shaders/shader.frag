#version 450

layout (binding = 1) uniform sampler2D texSampler;


struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    
    int type;
    float intensity;
};

layout (binding = 2) uniform LightBuffer {
    Light lights[32];
    int lightCount;
} lightsList;

layout (location = 0) in vec3 fragColor;
layout (location = 1) in vec2 fragTexCoord;

layout (location = 0) out vec4 outColor;

void main(){
	outColor = texture(texSampler,fragTexCoord);
}