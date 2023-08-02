#version 400 core
out vec4 FragColor;

uniform vec3 lightColours;

void main()
{
    FragColor = vec4(lightColours, 1.0); // set all 4 vector values to 1.0
}