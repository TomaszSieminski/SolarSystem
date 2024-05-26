#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;  // Pozycja fragmentu
in vec3 Normal;   // Norma fragmentu

uniform sampler2D texture1;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main() {
    // Wektory oœwietlenia
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    // Sk³adnik ambient
    vec3 ambient = light.ambient * 2.0 * texture(texture1, TexCoord).rgb; // Zwiêkszamy ambient dla s³oñca

    // Sk³adnik diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * 2.0 * diff * texture(texture1, TexCoord).rgb; // Zwiêkszamy diffuse dla s³oñca

    // Sk³adnik specular
    vec3 viewDir = normalize(-FragPos);  // Przyjmijmy, ¿e obserwator jest w (0,0,0)
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = 0.0;
    if (diff > 0.0) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    }
    vec3 specular = light.specular * 2.0 * spec * texture(texture1, TexCoord).rgb; // Zwiêkszamy specular dla s³oñca

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
