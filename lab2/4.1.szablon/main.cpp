#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "cos.h"
#include "obiektA.h"
#include "obiektB.h"
#include "obiektC.h"
#include "obiektD.h"
#include "shader_stuff.hpp"
//

using namespace std;

class CMesh {
public:
  // metody
  void init(vector<GLfloat> triangles, vector<GLfloat> colors) {
      // -------------------------------------------------
  // Etap (2) przeslanie danych wierzcholków do OpenGL
  // -------------------------------------------------
  glGenVertexArrays(1, &idVAO);
  glBindVertexArray(idVAO);
  // Bufor na wspolrzedne wierzcholkow
  glGenBuffers(1, &idVBO_coord);
  glBindBuffer(GL_ARRAY_BUFFER, idVBO_coord);
  glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(float),
               triangles.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);

  // Bufor na kolory wierzcholkow
  glGenBuffers(1, &idVBO_color);
  glBindBuffer(GL_ARRAY_BUFFER, idVBO_color);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(1);

  // Wylaczenie aktualnego VAO
  glBindVertexArray(0);

  }

  void draw(int currentNumOfTriangles) {
    glBindVertexArray(idVAO);
    glDrawArrays(GL_TRIANGLES, 0, currentNumOfTriangles * 3);
    glBindVertexArray(0);
  }

  // skladowe
  GLuint idVAO;       // tablic wierzcholkow
  GLuint idVBO_coord; // bufora na wspolrzedne
  GLuint idVBO_color;

};

// ---------------------------------------------------
// Identyfikatory obiektow OpenGL
  GLuint idVAO;       // tablic wierzcholkow
  GLuint idVBO_coord; // bufora na wspolrzedne
  GLuint idVBO_color;

GLuint idProgram;   // programu

// Liczba wierzcholkow
constexpr int numTriangles = 2;

// Wspolrzedne wierzchokow
GLfloat vertices[numTriangles * 3 * 2] = {-0.8, -0.8, 0.0, -0.8, -0.4, 0.0,

                                          0.0,  0.0,  0.8, 0.0,  0.4,  0.8};

// Kolory wierzcholkow
GLfloat colors[numTriangles * 3 * 3];
// {
// 	1.0, 0.0, 0.0,
// 	0.0, 1.0, 0.0,
// 	0.0, 0.0, 1.0,

// 	0.0, 0.0, 1.0,
// 	0.0, 1.0, 0.0,
// 	1.0, 0.0, 0.0
// }

// Obecne wspolrzedne wierzcholka
vector<GLfloat> currentColors;
vector<GLfloat> currentVertecies;
int currentNumOfTriangles;

// ---------------------------------------------------
// Funkcja renderujaca
void DisplayScene() {
  // ---------------------------
  // Etap (5) rendering
  // ---------------------------
  glClear(GL_COLOR_BUFFER_BIT);

  // Wlaczenie potoku
  glUseProgram(idProgram);

  // Renderowanie obiektu
  
  // Wylaczanie potoku
  glUseProgram(0);

  glutSwapBuffers();
}

// ---------------------------------------------------
// Funkcja inicjalizujaca
void Initialize() {

  // ---------------------------------------
  // Etap (3) stworzenie potoku graficznego
  // ---------------------------------------
  idProgram = glCreateProgram();

  glAttachShader(idProgram, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
  glAttachShader(idProgram, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

  LinkAndValidateProgram(idProgram);

  // -----------------------------------------
  // Etap (4) ustawienie maszyny stanow OpenGL
  // -----------------------------------------

  // ustawienie koloru czyszczenia ramki koloru
  glClearColor(0.9f, 0.9f, 0.9f, 0.9f);
}

// ---------------------------------------------------
// Funkcja wywolywana podczas zmiany rozdzielczosci ekranu
void Reshape(int width, int height) { glViewport(0, 0, width, height); }

// ---------------------------------------------------
// Funkcja wywolywana podczas wcisniecia klawisza ASCII
void Keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 27: // ESC

    // opuszczamy glowna petle
    glutLeaveMainLoop();
    break;

  case ' ': // Space
    cout << "Nacisnales SPACJE!\n";

    // ponowne renderowanie
    glutPostRedisplay();
    break;
  case '1':

    cout << "Obiekt A!\n";
    currentVertecies.clear();
    for (GLfloat ver : verticesA) {
      currentVertecies.push_back(ver);
    }

    currentNumOfTriangles = numTrianglesA;

    glBindBuffer(GL_ARRAY_BUFFER, idVBO_coord);
    glBufferData(GL_ARRAY_BUFFER, currentVertecies.size() * sizeof(float),
                 currentVertecies.data(), GL_STATIC_DRAW);

    for (int i{0}; i < numVerticesA; i++) {
      srand(time(0)); // seed value
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
    }
    glBindBuffer(GL_ARRAY_BUFFER, idVBO_color);
    glBufferData(GL_ARRAY_BUFFER, currentColors.size() * sizeof(float),
                 currentColors.data(), GL_STATIC_DRAW);

    glutPostRedisplay();

    break;
  case '2':
    srand(time(0)); // seed value

    cout << "Obiekt B!\n";
    currentVertecies.clear();
    for (GLfloat ver : verticesB) {
      currentVertecies.push_back(ver);
    }
    currentNumOfTriangles = numTrianglesB;

    glBindBuffer(GL_ARRAY_BUFFER, idVBO_coord);
    glBufferData(GL_ARRAY_BUFFER, currentVertecies.size() * sizeof(float),
                 currentVertecies.data(), GL_STATIC_DRAW);
    for (int i{0}; i < numVerticesB; i++) {
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
    }
    glBindBuffer(GL_ARRAY_BUFFER, idVBO_color);
    glBufferData(GL_ARRAY_BUFFER, currentColors.size() * sizeof(float),
                 currentColors.data(), GL_STATIC_DRAW);

    glutPostRedisplay();

    break;
  case '3':
    srand(time(0)); // seed value

    cout << "Obiekt C!\n";
    currentVertecies.clear();
    for (GLfloat ver : verticesC) {
      currentVertecies.push_back(ver);
    }
    currentNumOfTriangles = numTrianglesC;

    glBindBuffer(GL_ARRAY_BUFFER, idVBO_coord);
    glBufferData(GL_ARRAY_BUFFER, currentVertecies.size() * sizeof(float),
                 currentVertecies.data(), GL_STATIC_DRAW);
    for (int i{0}; i < numVerticesC; i++) {
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
    }
    glBindBuffer(GL_ARRAY_BUFFER, idVBO_color);
    glBufferData(GL_ARRAY_BUFFER, currentColors.size() * sizeof(float),
                 currentColors.data(), GL_STATIC_DRAW);

    glutPostRedisplay();

    break;
  case '4':
    srand(time(0)); // seed value

    cout << "Obiekt D!\n";
    currentVertecies.clear();
    for (GLfloat ver : verticesD) {
      currentVertecies.push_back(ver);
    }
    currentNumOfTriangles = numTrianglesD;

    glBindBuffer(GL_ARRAY_BUFFER, idVBO_coord);
    glBufferData(GL_ARRAY_BUFFER, currentVertecies.size() * sizeof(float),
                 currentVertecies.data(), GL_STATIC_DRAW);
    for (int i{0}; i < numVerticesD; i++) {
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
    }
    glBindBuffer(GL_ARRAY_BUFFER, idVBO_color);
    glBufferData(GL_ARRAY_BUFFER, currentColors.size() * sizeof(float),
                 currentColors.data(), GL_STATIC_DRAW);

    glutPostRedisplay();

    break;
  case '5':
    srand(time(0)); // seed value

    cout << "Obiekt Cos!\n";
    currentVertecies.clear();
    for (GLfloat ver : verticesCos) {
      currentVertecies.push_back(ver);
    }
    currentNumOfTriangles = numTrianglesCos;

    glBindBuffer(GL_ARRAY_BUFFER, idVBO_coord);
    glBufferData(GL_ARRAY_BUFFER, currentVertecies.size() * sizeof(float),
                 currentVertecies.data(), GL_STATIC_DRAW);
    for (int i{0}; i < numVerticesCos; i++) {
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
      currentColors.push_back((GLfloat)rand() / RAND_MAX);
    }
    glBindBuffer(GL_ARRAY_BUFFER, idVBO_color);
    glBufferData(GL_ARRAY_BUFFER, currentColors.size() * sizeof(float),
                 currentColors.data(), GL_STATIC_DRAW);

    glutPostRedisplay();

    break;
  }
}

// ---------------------------------------------------
int main(int argc, char *argv[]) {
  // -----------------------------------------------
  // Etap (1) utworzynie kontektu i okna aplikacji
  // -----------------------------------------------
  currentNumOfTriangles = numTrianglesA;
  currentVertecies.clear();
  for (GLfloat ver : verticesA) {
    cout << ver << endl;

    currentVertecies.push_back(ver);
  }
  cout << currentVertecies.data() << endl;

  // GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitContextVersion(3, 2);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Szablon programu w OpenGL");
  glutDisplayFunc(DisplayScene);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);

  // GLEW
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    cout << "GLEW Error\n";
    exit(1);
  }

  // OpenGL
  if (!GLEW_VERSION_3_2) {
    cout << "Brak OpenGL 3.2!\n";
    exit(1);
  }

  // Inicjalizacja
  Initialize();

  // Glowna petla rysujaca
  glutMainLoop();

  // Cleaning
  glDeleteProgram(idProgram);
  glDeleteVertexArrays(1, &idVAO);

  return 0;
}
