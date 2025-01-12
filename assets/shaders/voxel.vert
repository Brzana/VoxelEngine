#version 330 core

layout(location = 0) in vec3 aPos; // position attribute
layout(location = 1) in vec2 aTex; // texture coordinates (optional)

uniform mat4 uView;      // view matrix
uniform mat4 uProj;      // projection matrix
uniform mat4 uModel;     // model matrix

out vec2 TexCoord;       // pass texture coords to fragment shader

void main()
{
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
    TexCoord = aTex;
}
