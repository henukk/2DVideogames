#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 modelview;
uniform vec2 texCoordDispl;

out vec2 fragTexCoord;

void main() {
    fragTexCoord = texCoord + texCoordDispl;
    gl_Position = projection * modelview * vec4(position, 0.0, 1.0);
}
