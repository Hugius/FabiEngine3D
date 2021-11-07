#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Process fragment
void main()
{
	gl_FragDepth = gl_FragCoord.z;
}