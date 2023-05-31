// Vertex shader
#version 330 core

// Dane pobrane z VAO
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec3 inColor;


// Predefiniowane dane wejsciowe
// nie odkomentowujemy!
/*
in int gl_VertexID;
in int gl_InstanceID;
*/

// Dane wyjsciowe (kolejny etap potoku)
// out vec4 gl_Position;

out vec3 fragColor;

void main()
{

	// zmienna typu vec4
	vec4 newPosition = inPosition;

	// finalna pozycja wierzcholka
	gl_Position = newPosition;

	// kolor wierzcholka przekazany
	// do shadera fragmentow
	fragColor = inColor;

}
