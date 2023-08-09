#version 400
out vec4 FragColor;

struct Material {
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 5
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform bool flashLightOn;

vec3 CalcDirLightGooch(DirLight light, vec3 normal, vec3 viewDir, vec3 warm, vec3 cool, float alpha, float beta);
vec3 CalcSpotLightGooch(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 warm, vec3 cool, float alpha, float beta);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLightGooch(dirLight, norm, viewDir, vec3(0.5f, 0.2f, 0.1f), vec3(0.05f, 0.05f, 0.9f), 1.0f, 1.0f);
    result += CalcSpotLightGooch(spotLight, norm, FragPos, viewDir, vec3(0.5f, 0.2f, 0.1f), vec3(0.05f, 0.05f, 0.9f), 1.0f, 1.0f);
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLightGooch(DirLight light, vec3 normal, vec3 viewDir, vec3 warm, vec3 cool, float alpha, float beta)
{
    vec3 albedo = vec3(texture(texture_diffuse1, TexCoords));
    
    vec3 lightDir = normalize(-light.direction);

    float gooch = (1.0f + dot(normal, lightDir) / 2.0f);
    
    vec3 kCool = cool + alpha * (albedo);
    vec3 kWarm = warm + beta * (albedo);
    
    vec3 diff = (gooch * kWarm) + ((1 - gooch) * kCool);
    
    vec3 halfWay = normalize(lightDir + FragPos);
    float spec = pow(max(dot(normal, halfWay), 0.0), material.shininess);

    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    return (diffuse + specular);
}

vec3 CalcSpotLightGooch(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 warm, vec3 cool, float alpha, float beta)
{
    if (flashLightOn) {
        vec3 albedo = vec3(texture(texture_diffuse1, TexCoords));

        vec3 lightDir = normalize(light.position - fragPos);

        float gooch = (1.0f + dot(normal, lightDir) / 2.0f);

        vec3 kCool = cool + alpha * (albedo * 0.1f);
        vec3 kWarm = warm + beta * (albedo * 0.5f);

        vec3 diff = (gooch * kWarm) + ((1 - gooch) * kCool);

        vec3 halfWay = normalize(lightDir + FragPos);
        float spec = pow(max(dot(normal, halfWay), 0.0), material.shininess);

        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        vec3 diffuse = light.diffuse * diff;
        vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        return (diffuse + specular);
    }
}