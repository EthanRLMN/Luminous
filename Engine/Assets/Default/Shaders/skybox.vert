#version 460

layout(push_constant) uniform UBO_Constant {
    mat4 view;
    mat4 proj;
} uboConstant;

layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec3 fragTexCoord;

void main() {
    // Supprimer la translation de la vue pour que la skybox soit fixe par rapport à la caméra
    mat4 view = mat4(mat3(uboConstant.view)); 

    vec4 pos = uboConstant.proj * view * vec4(inPosition, 1.0);
    gl_Position = pos.xyww; // Trick pour mettre la skybox en arrière-plan
    fragTexCoord = inPosition;
}