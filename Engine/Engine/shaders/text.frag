#version 330 core

in vec2 fragTexCoord;

uniform sampler2D tex;
uniform vec4 color;

out vec4 outColor;

void main() {
    vec4 texColor = texture(tex, fragTexCoord);
    outColor = texColor * color;
}
