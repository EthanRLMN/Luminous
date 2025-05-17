#version 450

layout(location = 0) out vec3 vTexCoord;

layout(set = 0, binding = 0) uniform UBO {
    mat4 view;
    mat4 projection;
} ubo;

layout(location = 0) in vec3 inPosition;

void main() {
    // Remove translation from view matrix
    mat4 viewNoTranslation = mat4(mat3(ubo.view));
    vec4 pos = ubo.projection * viewNoTranslation * vec4(inPosition, 1.0);

    gl_Position = pos.xyww; // Trick to push to the far plane
    vTexCoord = inPosition;
}