in vec4 vPosition;

uniform mat4 uMVP;

void main()
{
    fPosition = uMVP * vPosition;
}