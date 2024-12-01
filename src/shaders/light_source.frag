#version 330

in vec2 fragPos; // Position of the fragment, passed from vertex shader
out vec4 fragColor;

uniform vec2 center; // Center of the circle (in normalized device coordinates)
uniform float outerRadius; // Outer radius of the ring
uniform float innerRadius; // Inner radius of the ring
uniform vec3 color;
uniform float aspectRatio;

void main() {
    vec2 adjustedPos = vec2(fragPos.x * aspectRatio, fragPos.y);
    vec2 adjustedCenter = vec2(center.x * aspectRatio, center.y);

    float dist = length(adjustedPos - adjustedCenter);

    // Discard fragments outside the circle
    if (dist >= outerRadius) {
        discard;
    }

    float alpha = smoothstep(innerRadius, outerRadius, dist);
    float aplha_inv = (1.0 - alpha);

    fragColor = vec4(color[0], color[1], color[2], aplha_inv);
}