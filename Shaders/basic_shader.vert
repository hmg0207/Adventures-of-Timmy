#version 430 core

in vec2 vPos;
in vec4 vCol;

out vec4 fCol;

void main()
{
    gl_Position = vec4( vPos, 0.0, 1.0 );
    fCol = vCol;
}