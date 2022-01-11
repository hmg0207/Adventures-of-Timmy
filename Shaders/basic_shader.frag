#version 430 core

in vec2 fPos; 
in vec4 fCol;

out vec4 colour;

uniform float timer;

void main()
{
    /*colour = fCol + vec4( 1.0 * ( cos( timer )       + 1.0 ) * 0.5,
                          1.0 * ( cos( timer + 2.0 ) + 1.0 ) * 0.5,
                          1.0 * ( sin( timer + 1.0 ) + 1.0 ) * 0.5,
                          0.0 );*/

    colour = vec4( fCol.r * ( cos( fPos.x * 3.0 + timer ) + 1.0 ) * 0.5,
                   fCol.g * ( cos( fPos.y * 9.0 + timer ) + 1.0 ) * 0.5,
                   fCol.b * ( cos( fPos.x * 0.6 + timer ) + 1.0 ) * 0.5,
                   fCol.a );                       
}

