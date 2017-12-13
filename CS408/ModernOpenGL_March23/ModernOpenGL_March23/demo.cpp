#include <iostream>

#include "gl3w.h"

// Unix
#if defined(unix) || defined(__unix) || defined(__unix__)
#include <GL/freeglut.h>

// Mac OSX
#elif defined(__APPLE__) || defined(__MACH__)
#include "freeglut.h"

// Windows
#elif defined(_WIN32) || defined(__WIN32__)
#include "freeglut.h"
#endif

#include <cmath> // we need this for M_PI





#define ATTRIB_POINT 0

void display(void);
void keyfunc(unsigned char, int, int);
void reshape (int w, int h);
void init(void);
void terminate(void);
void idle(void);

// Global variables 

struct graphics_context
{
  GLuint program;
  GLint uniform_angle;
  GLuint vbo_point;
  GLuint elementbuffer;
  GLuint vao_point;
  GLfloat angle;
  GLfloat lastframe;
} context;


const GLuint TRIANGLE_VERTEX_COUNT = 3; 
const GLfloat TRIANGLE[ TRIANGLE_VERTEX_COUNT * 3 ] = {
  // x,    y,    z
  -1.0f,  1.0f, 0.f, // 1st vertex
  -1.0f, -1.0f, 0.f, // 2nd vertex
   1.0f,  1.0f, 0.f   // 3rd vertex
};

const GLuint TRIANGLE_INDICES[ 3 ] = { 0, 1, 2 };


/* Shader sources */
const GLchar* vertex_shader =
  "#version 130\n"
  "in vec3 point;\n"
  "uniform float angle;\n"
  "void main() {\n"
  "    mat3 rotate = mat3(cos(angle), -sin(angle), 0,\n"
  "                       sin(angle), cos(angle),  0,\n"
  "                         0,            0,       1 );\n"
  "    gl_Position = vec4(0.75 * rotate * point, 1.0);\n"
  "}\n";

const GLchar* fragment_shader =
  "#version 130\n"
  "out vec4 color;\n"
  "void main() {\n"
  "    color = vec4(1, 0.15, 0.15, 0);\n"
  "}\n";

static GLuint compile_shader(GLenum type, const GLchar *source)
{
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  GLint param;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
  if (!param) {
    GLchar log[4096];
    glGetShaderInfoLog(shader, sizeof(log), NULL, log);
    fprintf(stderr, "error: %s: %s\n",
	    type == GL_FRAGMENT_SHADER ? "frag" : "vert", (char *) log);
    exit(EXIT_FAILURE);
  }
  return shader;
}

static GLuint link_program(GLuint vert, GLuint frag)
{
  GLuint program = glCreateProgram();
  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);
  GLint param;
  glGetProgramiv(program, GL_LINK_STATUS, &param);
  if (!param) {
    GLchar log[4096];
    glGetProgramInfoLog(program, sizeof(log), NULL, log);
    fprintf(stderr, "error: link: %s\n", (char *) log);
    exit(EXIT_FAILURE);
  }
  return program;
}


// set some OpenGL state variables
void init()
{
  /* Compile and link OpenGL program */
  GLuint vert = compile_shader(GL_VERTEX_SHADER, vertex_shader);
  GLuint frag = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
  context.program = link_program(vert, frag);
  context.uniform_angle = glGetUniformLocation(context.program, "angle");
  
  // delete shaders, opengl will keep them around since it knows they are being used by the program
  glDeleteShader(frag);
  glDeleteShader(vert);
  
  /* Prepare vertex buffer object (VBO) for vertex positions*/
  glGenBuffers(1, &context.vbo_point);             // generate a buffer and return its ID
  glBindBuffer(GL_ARRAY_BUFFER, context.vbo_point);// make the new buffer current
  {
    glBufferData(GL_ARRAY_BUFFER, sizeof(TRIANGLE), TRIANGLE, GL_STATIC_DRAW); // allocate memory and fill with data
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);                // unbind the buffer so that we don't accidentally modify it


  // HERE YOU MIGHT WANT MORE BUFFERS WITH OTHER VERTEX DATA
  //
  //


  // IF YOU WANT TO DO INDEXED DRAWING THIS IS WHERE YOU'D CREATE AN ELEMENT_BUFFER
  glGenBuffers(1, &context.elementbuffer); // generate a buffer and return its ID
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context.elementbuffer);
  {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TRIANGLE_INDICES), TRIANGLE_INDICES, GL_STATIC_DRAW); // make the new buffer current
  }
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                // unbind the buffer so that we don't accidentally modify it
  
  

  
  /* Prepare vertrex array object (VAO) */
  glGenVertexArrays(1, &context.vao_point); // generate a VAO
  glBindVertexArray(context.vao_point);     // make it the current VAO
  {
    glBindBuffer(GL_ARRAY_BUFFER, context.vbo_point);  // Bind the vertex position buffer
    glVertexAttribPointer(ATTRIB_POINT, 3, GL_FLOAT, GL_FALSE, 0, 0); // inform opengl of what data can be found in this buffer
    glEnableVertexAttribArray(ATTRIB_POINT);                          // enable fetching data from this buffer
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context.elementbuffer);  
  }
  glBindVertexArray(0);                              // unbind the VAO

  glBindBuffer(GL_ARRAY_BUFFER, 0);                  // unbind the buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  // lets set the clear color here 
  glClearColor(0.15, 0.15, 0.15, 1);

}


// destroy any objects we have created
void terminate()
{
  /* Delete vertex buffer object (VBO) */
  glDeleteBuffers(1, &context.vbo_point);
  
  /* Delete vertrex array object (VAO) */
  glDeleteVertexArrays(1, &context.vao_point);
  
  /* Delete the program we were using to draw */
  glDeleteProgram(context.program);

  std::cout << "Bye bye\n";
}

void reshape(int w, int h)
{
  glViewport (0, 0, w, h);
  
  glutPostRedisplay();
}


void idle(void)
{
  /* Physics */     
  float now = glutGet(GLUT_ELAPSED_TIME);
  float frame_time = now - context.lastframe;
  
  context.angle += 0.001 * frame_time;
  
  while ( context.angle > 2 * M_PI )
    context.angle -= 2 * M_PI;
  
  context.lastframe = now;
}


// main draw function, gets called over and over, as fast as possible
void display(void)
{
  // Clear the back buffer ( we have now an empty canvas )
  glClear(GL_COLOR_BUFFER_BIT);

  // activate the program that we want to use to draw
  glUseProgram(context.program);

  // Upload any information needed by our program
  glUniform1f(context.uniform_angle, context.angle);

  // Bind the VAO that holds the description of all the input needed to draw our object 
  glBindVertexArray(context.vao_point);
  {
    // dispatch drawing command
    glDrawElements( GL_TRIANGLES,      // mode ( we want to draw triangles )
		    3,                 // count ( using count vertices )
		    GL_UNSIGNED_INT,   // type ( the elemnts we are using are unsigned integers )
		    (void*)0           // element array buffer offset ( start pulling elements from 0 bytes into the buffer )
		    );
  }
  glBindVertexArray(0); // deactivate
  
  glUseProgram(0); // deactivate
      
  // swap back buffer
  glutSwapBuffers(); // swap the drawing buffers 

  // instruct glut to redisplay since we have drawn a new frame
  glutPostRedisplay();
}


void keyfunc(unsigned char k, int x, int y)
{
  switch (k)
    {
    case 27:
      // escape key
      terminate(); // clean up 
      exit(0);         // exit program
      break;
      
    case ' ':
      // do something when space bar has been pressed
      break;
    }
}





int main(int argc, char **argv)
{  
  // initialize the glut system
  glutInit(&argc, argv);
  glutInitWindowSize(1024, 768);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  
  // Create a window 
  glutCreateWindow("OpenGL program with shaders");
  
  /* Initialize gl3w (this will load all the gl functions)*/
  if ( gl3wInit() )
    {
      std::cerr << "gl3w: failed to initialize\n";
      exit(EXIT_FAILURE);
    }
  
  std::cout << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
  
  
  //// NOW WE ARE READY TO DO STUFF //// 

  
  
  // initialize our simulation and create opengl buffers
  init();
  
  // set callback functions.
  // display is the function that gets called automatically as fast as possible.
  glutDisplayFunc(display);

  // keyfunc is invoked if the user hits a keyboard key.
  glutKeyboardFunc(keyfunc);

  // called whenever the geometry of the window has changed ( size, position, etc. )
  glutReshapeFunc(reshape);

  // idle is called when there is nothing else left to do
  glutIdleFunc(idle);

  
  // start the main glut loop, no code runs after this
  glutMainLoop();
  
  return 1;
}


