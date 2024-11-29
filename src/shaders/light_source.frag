#version 330

in vec2 val;  // Input from vertex shader
out vec4 fragColor;  // Output color to fragment shader

void main() {
    float R = 1.0;
    float R2 = 0.5;
    float dist = sqrt(dot(val, val));

    if (dist >= R || dist <= R2) {
        discard;
    }

    float sm = smoothstep(R, R-0.01, dist);
    float sm2 = smoothstep(R2, R2+0.01, dist);

    float alpha = sm * sm2;
    fragColor = vec4(0.0, 0.0, 1.0, alpha);
}