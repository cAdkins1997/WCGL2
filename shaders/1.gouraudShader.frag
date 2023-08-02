#version 400
out vec4 FragColor;

in vec3 lightColor;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main() {
    FragColor = vec4(lightColor, 1.0) * vec4(texture(texture_diffuse1, TexCoords));
}