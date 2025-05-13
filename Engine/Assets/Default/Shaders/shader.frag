#version 460

layout (binding = 1) uniform sampler2D texSampler;

layout (set = 1 ,binding = 0) uniform sampler2D texSampler2;


layout (location = 0) in vec3 fragPos;
layout (location = 1) in vec3 fragNormal;
layout (location = 2) in vec2 fragTexCoord;
layout (location = 3) in vec3 viewPos;
layout (location = 4) flat in int debugCollide;

layout (location = 0) out vec4 outColor;


struct Light {
    vec3 padding;
    vec3 position;
    vec3 direction;
    vec3 color;
    

    int type;
    float intensity;
    float ambientStrength;
    float specularStrength;
    int count;
} light;

layout (binding = 2) uniform LightBuffer {
    Light lights[32];
} lightsList;


vec3 CalculateDirectional(Light a_light)
{
    vec3 lightcolor = a_light.color;

    float ambientStrength = a_light.ambientStrength;
    vec3 ambient = ambientStrength * lightcolor;
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(-a_light.direction);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

    float specularStrength = a_light.specularStrength;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightcolor;  

    vec3 result = (ambient + diffuse + specular) * a_light.intensity;
    return result;
}

vec3 CalculatePointLight (Light a_light)
{

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;  

    float dist = length(a_light.position - fragPos);
    float attenuation = 1.0 / (constant + linear * dist + quadratic * (dist * dist));    

    vec3 lightcolor = a_light.color;

    float ambientStrength = a_light.ambientStrength;
    vec3 ambient = ambientStrength * lightcolor;
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir =  normalize(a_light.position - fragPos); 
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

    float specularStrength = a_light.specularStrength;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightcolor;  

    
    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation; 

    vec3 result = (ambient + diffuse + specular) * a_light.intensity;
    return result;
}


void main(){


    vec3 final = vec3(0.0);
    
    for(int i = 0; i < lightsList.lights[0].count; i++)
    {
        if (lightsList.lights[i].type == 0)
        {
            final += CalculateDirectional(lightsList.lights[i]);
        }
        else if (lightsList.lights[i].type == 1)
        {
            final += CalculatePointLight(lightsList.lights[i]);
        }
    }
    vec3 result = final;
    outColor = texture(texSampler2,fragTexCoord) * vec4(result, 1.0);
    if (debugCollide == 1)
    {
        outColor = texture(texSampler2,fragTexCoord);
    }


}