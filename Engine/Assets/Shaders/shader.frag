#version 450

layout (binding = 1) uniform sampler2D texSampler;


struct Light {
    vec3 padding;
    vec3 position;
    vec3 direction;
    vec3 color;
    

    int type;
    float intensity;
    float ambientStrength;
    float specularStrength;
} light;

layout (binding = 2) uniform LightBuffer {
    Light lights[32];
} lightsList;




layout (location = 0) in vec3 fragPos;
layout (location = 1) in vec3 fragNormal;
layout (location = 2) in vec2 fragTexCoord;
layout (location = 3) in vec3 viewPos;

layout (location = 0) out vec4 outColor;

void main(){


    //Light Calculations
    //Ambient
    
    vec3 lightcolor = lightsList.lights[0].color;

    float ambientStrength = lightsList.lights[0].ambientStrength;
    vec3 ambient = ambientStrength * lightcolor;
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(-lightsList.lights[0].direction); 
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;


    //Specular
    float specularStrength = lightsList.lights[0].specularStrength;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightcolor;  

    vec3 result = (ambient + diffuse + specular) * lightsList.lights[0].intensity;
    outColor = texture(texSampler,fragTexCoord) * vec4(result, 1.0);

}