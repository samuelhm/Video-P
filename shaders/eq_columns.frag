#version 300 es
precision mediump float;

in vec2 texcoord;
uniform sampler2D tex;
uniform float u_a0;
uniform float u_a1;
uniform float u_a2;
uniform float u_a3;
uniform float u_a4;
uniform float u_a5;
uniform float u_a6;
uniform float u_a7;
uniform float u_a8;
uniform float u_a9;
uniform float u_a10;
uniform float u_a11;
uniform float u_a12;
uniform float u_a13;
uniform float u_a14;
uniform float u_a15;
out vec4 fragColor;

void main(void) {
    float colW = 1.0 / 16.0;
    int band = int(floor(texcoord.x / colW));
    if (band < 0) band = 0;
    if (band > 15) band = 15;

    float posInCol = (texcoord.x - float(band) * colW) / colW;
    if (posInCol < 0.1 || posInCol > 0.9) {
        fragColor = texture(tex, texcoord);
        return;
    }

    float a;
    if      (band == 0)  a = u_a0;
    else if (band == 1)  a = u_a1;
    else if (band == 2)  a = u_a2;
    else if (band == 3)  a = u_a3;
    else if (band == 4)  a = u_a4;
    else if (band == 5)  a = u_a5;
    else if (band == 6)  a = u_a6;
    else if (band == 7)  a = u_a7;
    else if (band == 8)  a = u_a8;
    else if (band == 9)  a = u_a9;
    else if (band ==10)  a = u_a10;
    else if (band ==11)  a = u_a11;
    else if (band ==12)  a = u_a12;
    else if (band ==13)  a = u_a13;
    else if (band ==14)  a = u_a14;
    else                 a = u_a15;

    float amplitude = clamp(a, 0.0, 1.0);
    amplitude = max(amplitude, 0.2);
    float yb = 1.0 - texcoord.y;

    if (yb < amplitude) {
        fragColor = vec4(0.0, 1.0, 1.0, 1.0);
    } else {
        fragColor = texture(tex, texcoord);
    }
}
