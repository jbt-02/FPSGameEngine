#include "config.h"
#include <vector>
#include <glm/glm/glm.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow *window);

const char* vertexShaderSource = R"(
#version 330 core

//Input var from vertex buffer (location = 0)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord; //Texture coordinate

out vec2 TexCoord; //Output to frag shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture1;

void main(){
    //RGBA color (orange)
    //FragColor = vec4(1.0,0.5,0.2,1.0); 
    FragColor = texture(texture1, TexCoord);
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

    glEnable(GL_DEPTH_TEST);

       float vertices[] = {
        // positions          // tex coords
        -0.5f,-0.5f,-0.5f,   0.0f,0.0f,
         0.5f,-0.5f,-0.5f,   1.0f,0.0f,
         0.5f, 0.5f,-0.5f,   1.0f,1.0f,
         0.5f, 0.5f,-0.5f,   1.0f,1.0f,
        -0.5f, 0.5f,-0.5f,   0.0f,1.0f,
        -0.5f,-0.5f,-0.5f,   0.0f,0.0f,

        -0.5f,-0.5f,0.5f,    0.0f,0.0f,
         0.5f,-0.5f,0.5f,    1.0f,0.0f,
         0.5f, 0.5f,0.5f,    1.0f,1.0f,
         0.5f, 0.5f,0.5f,    1.0f,1.0f,
        -0.5f, 0.5f,0.5f,    0.0f,1.0f,
        -0.5f,-0.5f,0.5f,    0.0f,0.0f,

        -0.5f,0.5f,0.5f,     1.0f,0.0f,
        -0.5f,0.5f,-0.5f,    1.0f,1.0f,
        -0.5f,-0.5f,-0.5f,   0.0f,1.0f,
        -0.5f,-0.5f,-0.5f,   0.0f,1.0f,
        -0.5f,-0.5f,0.5f,    0.0f,0.0f,
        -0.5f,0.5f,0.5f,     1.0f,0.0f,

         0.5f,0.5f,0.5f,     1.0f,0.0f,
         0.5f,0.5f,-0.5f,    1.0f,1.0f,
         0.5f,-0.5f,-0.5f,   0.0f,1.0f,
         0.5f,-0.5f,-0.5f,   0.0f,1.0f,
         0.5f,-0.5f,0.5f,    0.0f,0.0f,
         0.5f,0.5f,0.5f,     1.0f,0.0f,

        -0.5f,-0.5f,-0.5f,   0.0f,1.0f,
         0.5f,-0.5f,-0.5f,   1.0f,1.0f,
         0.5f,-0.5f,0.5f,    1.0f,0.0f,
         0.5f,-0.5f,0.5f,    1.0f,0.0f,
        -0.5f,-0.5f,0.5f,    0.0f,0.0f,
        -0.5f,-0.5f,-0.5f,   0.0f,1.0f,

        -0.5f,0.5f,-0.5f,    0.0f,1.0f,
         0.5f,0.5f,-0.5f,    1.0f,1.0f,
         0.5f,0.5f,0.5f,     1.0f,0.0f,
         0.5f,0.5f,0.5f,     1.0f,0.0f,
        -0.5f,0.5f,0.5f,     0.0f,0.0f,
        -0.5f,0.5f,-0.5f,    0.0f,1.0f
    };

    /*unsigned int indices[] = {
        0,1,3,
        1,2,3 
    };*/

    unsigned int VAO, VBO, EBO;

    //generate object IDS
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1,&EBO);

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
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5 * sizeof(float), (void*)0);

    // Enable vertex attribute
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //unbind VAO
    //glBindVertexArray(0);

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

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;

    unsigned char* data = stbi_load("src/container.jpg", &width, &height, &nrChannels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glUseProgram(shaderProgram);
    glUniform1i( glGetUniformLocation(shaderProgram, "texture1"), 0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Bind texture to unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f,1.0f,0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

         //Use shader program
        glUseProgram(shaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));

        //Bind VAO (contains VBO + attribute setup)
        glBindVertexArray(VAO);

        //Draw
        glDrawArrays(GL_TRIANGLES, 0, 36);

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