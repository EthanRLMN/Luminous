#version 460


// Texture loading
layout (set = 1, binding = 0) uniform sampler2D texSampler2;


// Vertex Input
layout (location = 0) in vec3 fragPos;
layout (location = 1) in vec2 fragTexCoord;
layout (location = 2) in vec3 fragNormal;
layout (location = 3) in vec3 fragColor;
layout (location = 4) in vec3 viewPos;


// Output
layout (location = 0) out vec4 outColor;


// Light Struct
struct Light {
    vec3 position;
    float _pad0;

    vec3 direction;
    float _pad1;

    vec3 color;
    float _pad2;

    int type;
    float intensity;
    float ambientStrength;
    float specularStrength;

    int count;
    int _pad3;
    int _pad4;
    int _pad5;
};


layout (std430, set = 0, binding = 2) readonly buffer LightBuffer
{
    Light lights[];
} lightList;


vec3 ComputeLight(vec3 a_lightColor, vec3 a_lightDir, float a_intensity, float a_ambientStrength, float a_specularStrength)
{
    vec3 l_norm = normalize(fragNormal);
    vec3 l_viewDir = normalize(viewPos - fragPos);
    vec3 l_reflectDir = reflect(-a_lightDir, l_norm);

    float l_diff = max(dot(l_norm, a_lightDir), 0.0);
    float l_spec = pow(max(dot(l_viewDir, l_reflectDir), 0.0f), 32.0);

    vec3 l_ambient  = a_ambientStrength * a_lightColor;
    vec3 l_diffuse  = l_diff * a_lightColor;
    vec3 l_specular = a_specularStrength * l_spec * a_lightColor;

    return (l_ambient + l_diffuse + l_specular) * a_intensity;
}


vec3 CalculateDirectional(Light a_light)
{
    vec3 l_lightDir = normalize(-a_light.direction);
    return ComputeLight(a_light.color, l_lightDir, a_light.intensity, a_light.ambientStrength, a_light.specularStrength);
}

vec3 CalculatePointLight(Light a_light)
{
    vec3 l_lightDir = normalize(a_light.position - fragPos);
    float l_distance = length(a_light.position - fragPos);

    float l_constant = 1.0f;
    float l_linear = 0.09f;
    float l_quadratic = 0.032f;

    float attenuation = 1.0f / (l_constant + l_linear * l_distance + l_quadratic * l_distance * l_distance);
    return ComputeLight(a_light.color, l_lightDir, a_light.intensity * attenuation, a_light.ambientStrength, a_light.specularStrength);
}


void main()
{
    vec3 l_lighting = vec3(0.0);
    
    for (int i = 0; i < lightList.lights[0].count; ++i)
    {
        Light l_light = lightList.lights[i];

        if (l_light.type == 0)
            l_lighting += CalculateDirectional(l_light);
        else if (l_light.type == 1)
            l_lighting += CalculatePointLight(l_light);
    }

    vec4 l_texColor = texture(texSampler2, fragTexCoord);
    outColor = l_texColor * vec4(fragColor * l_lighting, 1.0);
}