#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "shader_stuff.h"

using namespace std;


// ---------------------------------------
// Identyfikatory obiektow OpenGL

GLuint idProgram;	// programu
GLuint idVAO;		// tablic wierzcholkow
GLuint idVBO_coord; // bufora na wspolrzedne

// ---------------------------------------
// 1. Definiowanie nowego wektora (pustego)
vector<float> points;
int numOfPoints;

// Wspolrzedne wierzchokow
GLfloat triangles[2*3*2] =
{
	-0.8f, -0.8f,
	 0.0f, -0.8f,
	-0.4f,  0.0f,

	 0.0f,  0.0f,
	 0.8f,  0.0f,
	 0.4f,  0.8f
};

// ---------------------------------------
void DisplayScene()
{
	// ---------------------------
	// Etap (5) rendering
	// ---------------------------
	glClear( GL_COLOR_BUFFER_BIT );


	// Wlaczenie potoku
	glUseProgram( idProgram );


		// Generowanie obiektow na ekranie
		glBindVertexArray( idVAO );
		glDrawArrays( GL_TRIANGLES, 0, points.size()/2 );
		glBindVertexArray( 0 );


	// Wylaczanie
	glUseProgram( 0 );


	glutSwapBuffers();
}

// ---------------------------------------
void Initialize()
{
  // 2. Uzupe¿naianie naszego wektora punktów
  int numOfTrianges;
  cout<<"Podaj liczbe trojkatow: ";
  cin >> numOfTrianges;

  numOfPoints = numOfTrianges*3;
  for(int i{0}; i < numOfPoints; i++){
    // points[i] = (rand()/static_cast<float>(RAND_MAX)*2.0) -1.0;
    float x = ((rand()/static_cast<float>(RAND_MAX)*2.0) -1.0);
    float y = ((rand()/static_cast<float>(RAND_MAX)*2.0) -1.0);
    points.push_back(x);
    points.push_back(y);
  }

	// -------------------------------------------------
	// Etap (2) przeslanie danych wierzcholków do OpenGL
	// -------------------------------------------------
	glGenVertexArrays( 1, &idVAO );
	glBindVertexArray( idVAO );

	// Bufor na wspolrzedne wierzcholkow
	glGenBuffers( 1, &idVBO_coord );
	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coord );
	glBufferData( GL_ARRAY_BUFFER, points.size()*sizeof(float), points.data(), GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );

	glBindVertexArray( 0 );


	// ---------------------------------------
	// Etap (3) stworzenie potoku graficznego
	// ---------------------------------------
	idProgram = glCreateProgram();

	glAttachShader( idProgram, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
	glAttachShader( idProgram, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

	LinkAndValidateProgram( idProgram );



	// -----------------------------------------
	// Etap (4) ustawienie maszyny stanow OpenGL
	// -----------------------------------------

	// ustawienie koloru czyszczenia ramki koloru
	glClearColor( 0.9f, 0.9f, 0.9f, 0.9f );

}

// ---------------------------------------
// Funkcja wywolywana podczas zmiany rozdzielczosci ekranu
void Reshape( int width, int height )
{
	glViewport( 0, 0, width, height );

  points.clear();
  for(int i{0}; i < numOfPoints; i++){
    // points[i] = (rand()/static_cast<float>(RAND_MAX)*2.0) -1.0;
    float x = ((rand()/static_cast<float>(RAND_MAX)*2.0) -1.0);
    float y = ((rand()/static_cast<float>(RAND_MAX)*2.0) -1.0);
    points.push_back(x);
    points.push_back(y);
  }

	// Bufor na wspolrzedne wierzcholkow
	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coord );
	glBufferData( GL_ARRAY_BUFFER, points.size()*sizeof(float), points.data(), GL_STATIC_DRAW );

}



// ---------------------------------------------------
// Funkcja wywolywana podczas wcisniecia klawisza ASCII
void Keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
		case 27:	// ESC key
			// opuszczamy glowna petle
			glutLeaveMainLoop();
			break;

		case ' ':	// Space key
			printf("SPACE!\n");
			// ponowne renderowanie
			glutPostRedisplay();
			break;
    }
}


// ---------------------------------------------------
int main( int argc, char *argv[] )
{
	// -----------------------------------------------
	// Etap (1) utworzynie kontektu i okna aplikacji
	// -----------------------------------------------

	// GLUT
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( "Szablon programu w OpenGL" );
	glutDisplayFunc( DisplayScene );
	glutReshapeFunc( Reshape );
	glutKeyboardFunc( Keyboard );


	// GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		printf("GLEW Error\n");
		exit(1);
	}

	// OpenGL
	if( !GLEW_VERSION_3_2 )
	{
		printf("Brak OpenGL 3.2!\n");
		exit(1);
	}

	// Inicjalizacja
	Initialize();



	glutMainLoop();


	// Cleaning
	glDeleteProgram( idProgram );
	glDeleteVertexArrays( 1, &idVBO_coord );
	glDeleteVertexArrays( 1, &idVAO );

	return 0;
}
