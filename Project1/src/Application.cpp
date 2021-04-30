#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>

#include <fstream>
#include <string> /*for getLine()*/

/*ifstream = input file stream
This data type represents the input file stream and is used to read information from files.
The size_t type is meant to specify the size of something so it's natural to use it, for example, getting the length of a string and then processing each character:

for (size_t i = 0, max = strlen (str); i < max; i++)
    doSomethingWith (str[i]);
You do have to watch out for boundary conditions of course, since it's an unsigned type. The boundary at the top end is not usually that important since the maximum 
is usually large (though it is possible to get there). Most people just use an int for that sort of thing because they rarely have structures or arrays that get big
enough to exceed the capacity of that int.
The find() method will be return the string::npos if it doesn't find the special string. So you should always use the following statement to check the find() result:
string::size_type index = str.find("value");
if (string::npos != index)
{
   // Do something.
}
string::npos is a constant (probably -1) representing a non-position. It's returned by method find when the pattern was not found.

*/


static std::string ParseShader(const std::string& filepath, unsigned int type) {
    std::ifstream streamFile(filepath);

    std::string shaders_line;

    unsigned int type_to_add;

    std::string vertex_shader;

    std::string fragment_shader;

    while (getline(streamFile, shaders_line)) {
        // Output the text from the file
        if (shaders_line.find("#shader vertex") != std::string::npos) {
            type_to_add = GL_VERTEX_SHADER;

        }
        else if(shaders_line.find("#shader fragment") != std::string::npos) {
            type_to_add = GL_FRAGMENT_SHADER;
        }
        else {
            if (type_to_add == GL_VERTEX_SHADER) {
                vertex_shader += shaders_line + "\n";
            }
            else if (type_to_add == GL_FRAGMENT_SHADER) {
                fragment_shader += shaders_line + "\n";
            }
        }
    }

    if (type == GL_VERTEX_SHADER) {
        return vertex_shader;
    }
    else if(type == GL_FRAGMENT_SHADER) {
        return fragment_shader;
    }
}



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

In C the strings are basically array of characters. In C++ the std::string is an advancement of that array. 
There are some additional features with the traditional character array. The null terminated strings are basically 
a sequence of characters, and the last element is one null character (denoted by ‘\0’). When we write some string 
using double quotes (“…”), then it is converted into null terminated strings by the compiler.
my_string = "This is a sam\0ple text"; //check the \0
cout << my_string; prints => This is a sam
c_str() Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) 
representing the current value of the basic_string object.
Objects can also be pointed to by pointers: Once declared, a class becomes a valid type, so it can be used as the 
type pointed to by a pointer. For example:


Rectangle * prect;


is a pointer to an object of class Rectangle
*/
static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    return id;
}


static unsigned int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
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


    unsigned int shader = CreateShader(ParseShader("resources/shaders/Basic.shader", GL_VERTEX_SHADER), ParseShader("resources/shaders/Basic.shader", GL_FRAGMENT_SHADER));
    std::cout << ParseShader("resources/shaders/Basic.shader", GL_FRAGMENT_SHADER) << std::endl;
    glUseProgram(shader);

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
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}