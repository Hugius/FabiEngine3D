#version 330 core
#extension GL_ARB_explicit_uniform_location : require

void main()
{
	gl_FragDepth = gl_FragCoord.z;
}