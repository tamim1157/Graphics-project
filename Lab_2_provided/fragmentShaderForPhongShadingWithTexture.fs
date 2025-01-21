#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float inner_circle;
    float outer_circle;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    //bool on;
};


#define NR_POINT_LIGHTS 2
#define NR_SPOT_LIGHTS 1

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform bool ambientLight = true;
uniform bool diffuseLight = true;
uniform bool specularLight = true;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform Material material;
uniform bool directionLightOn = true;
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;
uniform bool spotLightOn = false;

// function prototypes
vec3 CalcPointLight(Material material, PointLight light, vec3 N, vec3 fragPos, vec3 V);
vec3 CalcDirectionalLight(Material material, DirectionalLight light, vec3 N, vec3 V);
vec3 CalcSpotLight(Material material, SpotLight light, vec3 N, vec3 fragPos, vec3 V);

void main()
{
    // properties
    vec3 N = normalize(Normal);
    vec3 V = normalize(viewPos - FragPos);
    
    vec3 result;
    // point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(material, pointLights[i], N, FragPos, V);
     
    if(directionLightOn) {
        result += CalcDirectionalLight(material, directionalLight, N, V);
    }

    //for(int i = 0; i < NR_SPOT_LIGHTS; i++)
    //    result += CalcSpotLight(material, spotLights[i], N, FragPos, V);
    
    if(spotLightOn){
        result += CalcSpotLight(material, spotLight, N, FragPos, V);
    }

    FragColor = vec4(result, 1.0);
}

// calculates the color when using a point light.
vec3 CalcPointLight(Material material, PointLight light, vec3 N, vec3 fragPos, vec3 V)
{
    vec3 L = normalize(light.position - fragPos);
    vec3 R = reflect(-L, N);
    
    // attenuation
    float d = length(light.position - fragPos);
    float attenuation = 1.0 / (light.k_c + light.k_l * d + light.k_q * (d * d));
    
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
    vec3 diffuse = vec3(texture(material.diffuse, TexCoords)) * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = vec3(texture(material.specular, TexCoords)) * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}
vec3 CalcDirectionalLight(Material material, DirectionalLight light, vec3 N, vec3 V)
{
    vec3 L = normalize(-light.direction);
    vec3 R = reflect(-L, N);
        
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
    vec3 diffuse = vec3(texture(material.diffuse, TexCoords)) * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = vec3(texture(material.specular, TexCoords)) * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;
    
    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(Material material, SpotLight light, vec3 N, vec3 fragPos, vec3 V)
{
    vec3 L = normalize(light.position - fragPos);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = vec3(texture(material.diffuse, TexCoords));
    vec3 K_D =  vec3(texture(material.diffuse, TexCoords));
    vec3 K_S = vec3(texture(material.specular, TexCoords));
    
    // attenuation
    float d = length(light.position - fragPos);
    float attenuation = 1.0 / (light.k_c + light.k_l * d + light.k_q * (d * d));

    float cos_alpha = dot(L, normalize(-light.direction));
    float cos_theta = light.inner_circle- light.outer_circle;
    

    float intensity = clamp((cos_alpha-light.outer_circle)/cos_theta, 0.0, 1.0);   
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular);
}