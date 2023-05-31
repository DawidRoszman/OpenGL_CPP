// Fragment shader
#version 330 core


// Predefiniowane dane wejsciowe
/*
in  vec4 gl_FragCoord;
in  int  gl_PrimitiveID;
*/

// Dane wejsciowe
in vec3 fragColor;

// Dane wyjsciowe
out vec4 outColor;


void main()
{
	outColor = vec4(fragColor, 1.0);
}
