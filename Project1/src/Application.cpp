#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>

/*By declaring a function member as static, you make it independent of any 
particular object of the class. A static member function can be called even 
if no objects of the class exist and the static functions are accessed using 
only the class name and the scope resolution operator ::.*/
/*The function signature:

void add2(int &data)
is the pass-by-reference facility in C++. It's a way to allow the function to 
change the value passed in and have that change reflected back to the caller. 
In C, upon which C++ was originally based, all paramaters are pass-by-value, 
meaning the functions get a local copy which, if changed, does not affect the original value passed in.*/
/*Type& = It means you're passing the variable by reference.

In fact, in a declaration of a type, it means reference, just like:

int x = 42;
int& y = x;
declares a reference to x, called y.
the &before a var means returns the memory adress
*/
static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
}


static int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGL Cube", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << stderr, "Error: %s\n", glewGetErrorString(err);
    }

    /*DEFINE BUFFER*/
    /*Front face of cube*/
    float positions[] = {
        0.0f,0.0f,0.0f,
        0.1f,0.0f,0.0f,
        0.1f,0.1f,0.0f,
        0.1f,0.1f,0.0f,
        0.0f,0.1f,0.0f,
        0.0f,0.0f,0.0f
    };
    unsigned int buffer_location; /*id of generated buffer; when & we are passing the memory adress of the buffer_location int*/
    glGenBuffers(1, &buffer_location);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_location); /*Selecting in openGL is binding*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    /*attribs = 0 is the index of the attrib if I had uv then that would be index 1
    size 3 is the component count in this case 3 dimensions
    typeof data 
    if they are normalized or not, since they are floats they are already in the place we want them to be
    stride = amount of bytes between each vertex
    */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}