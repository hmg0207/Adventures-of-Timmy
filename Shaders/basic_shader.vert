#version 430 core

in vec2 vPos;

void main()
{
    gl_Position = vec4( vPos.x, vPos.y, 0.0, 1.0 );
}