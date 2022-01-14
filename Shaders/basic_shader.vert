#version 330 core

in vec2 v_pos;
in vec4 v_col;
in vec2 v_uv;

out vec2 f_pos;
out vec4 f_col;
out vec2 f_uv;

uniform mat4 ortho_proj_mat;

void main()
{
    gl_Position = ortho_proj_mat * vec4( v_pos, 0.0, 1.0 );
    f_pos = v_pos;
    f_col = v_col;
    f_uv  = vec2( v_uv.x, 1.0 - v_uv.y );    
}