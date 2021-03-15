#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 acolor;
out vec3 ourColor;
out vec4 finPos;
uniform float offset;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 translate;
void main() {
    finPos = transform * vec4(apos, 1.0);
    ourColor = acolor;
    gl_Position = projection * view * translate * model * finPos;
};