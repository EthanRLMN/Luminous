#version 450


layout (binding = 1) uniform sampler2D texSampler;






/*
layout (binding = 2) uniform LightBuffer {
    Light lights[32];
} lightsList;*/

layout (binding = 2) uniform Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    
    int type;
    float intensity;
} lighttt;



layout (location = 0) in vec3 fragNormal;
layout (location = 1) in vec2 fragTexCoord;
layout (location = 2) in vec3 fragPos;

layout (location = 0) out vec4 outColor;

void main(){
    //vec3 lightcolor = lightsList.lights[0].color;
	//outColor = texture(texSampler,fragTexCoord);

    /*
    //Light Calculations
    //Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightcolor;
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightsList.lights[0].position - fragPos); 
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

    vec3 result = (ambient + diffuse);
    //outColor = texture(texSampler,fragTexCoord) * vec4(result, 1.0);*/

   vec3 coltest = vec3(1.0,1.0,1.0) * 0.0;
   //outColor = lightsList.lights[0].position;
   outColor = vec4(lighttt.direction,1.0);
}