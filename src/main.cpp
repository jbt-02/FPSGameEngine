#include "config.h"
#include <iostream>
#include <vector>
#include <glm/glm/glm.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow *window);

const char* vertexShaderSource = R"(
#version 330 core

//Input var from vertex buffer (location = 0)
layout (location = 0) in vec3 aPos;

uniform mat4 transform;

void main(){
    //gl_pos is a built in output var
    //it must be a vec4 (x, y, z, w)
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

//Output color of the fragment
out vec4 FragColor;

void main(){
    //RGBA color (orange)
    FragColor = vec4(1.0,0.5,0.2,1.0); 
}
)";

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "FPS Game Engine", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLAD - THIS IS REQUIRED */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f, 
    };

    /*
    
    
    unsigned int indices[] = {
        0,1,3, //first triangle
        1,2,3 //second triangle
    };
    
    */
    unsigned int VAO, VBO, EBO;

    //generate object IDS
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
   // glGenBuffers(1,&EBO);

    //Bind VAO first (it will store config)
    glBindVertexArray(VAO);

    //Bind VBO as the active array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Copy vertex data into GPU memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //Element Buffer Object
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Tell OPENGL how to read vertex Data
    //Attribute location, Num of values per vertex (x,y,z), type of each val, normalize?, stride (dist between vertices), offset in buffer
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), (void*)0);

    // Enable vertex attribute
    glEnableVertexAttribArray(0);

    //unbind VAO
    glBindVertexArray(0);

    //Compile Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Link Shaders into program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        /* Render here */
        glClearColor(0.7f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Use shader program
        glUseProgram(shaderProgram);



        //Bind VAO (contains VBO + attribute setup)
        glBindVertexArray(VAO);

        //Draw Triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}