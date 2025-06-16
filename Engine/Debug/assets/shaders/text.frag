#version 330 core

in vec2 fragTexCoord;

uniform sampler2D tex;
uniform vec4 color;

out vec4 outColor;

void main() {
    float alpha = texture(tex, fragTexCoord).r;
    outColor = vec4(color.rgb, color.a * alpha);
}
