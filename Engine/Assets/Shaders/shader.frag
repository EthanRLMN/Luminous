#version 450


layout (binding = 1) uniform sampler2D texSampler;


struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    
    int type;
    float intensity;
};

layout (set = 1,binding = 0) uniform LightBuffer {
    Light lights[32];
} lightsList;

layout (location = 0) in vec3 fragNormal;
layout (location = 1) in vec2 fragTexCoord;
layout (location = 2) in vec3 fragPos;

layout (location = 0) out vec4 outColor;

void main(){
    vec3 lightcolor = lightsList.lights[0].color;
	//outColor = texture(texSampler,fragTexCoord) * vec4(lightcolor,1.0f);


    //Light Calculations
    //Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightcolor;

    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightsList.lights[0].position - fragPos); 
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

    vec3 result = (ambient + diffuse);
    //outColor = texture(texSampler,fragTexCoord) * vec4(result, 1.0);

    outColor = vec4(lightsList.lights[0].position, 1.0);
}