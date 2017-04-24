attribute vec4 vPosition;

uniform mat4 uMVP;

void main()
{
    gl_Position = uMVP * vPosition;
}