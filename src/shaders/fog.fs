#version 330

in vec3 fragNormal;

in vec4 position;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

out vec4 finalColor;

void main() {
    vec3 lightDir = normalize(vec3(1.0, 2.0, 3.0));

    vec3 normal = normalize(fragNormal);

    float NdotL = dot(normal, lightDir);
    float light = (NdotL + 1.0) / 2.0;

    float clampedColor = (light) / 2.0 + 0.25;

    finalColor = vec4(vec3(clampedColor), 1.0);
}
