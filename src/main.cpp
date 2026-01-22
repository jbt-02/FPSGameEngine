#include "config.h"
#include <vector>
#include <glm/glm/glm.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f/2.0;
float lastY = 600.0f/2.0;
float fov = 45.0f;

float deltaTime = 0.0;
float lastFrame = 0.0f;

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

     // Set callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set initial viewport
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
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

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Bind texture to unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float) fbWidth / (float) fbHeight, 0.1f, 100.0f);

         //Use shader program
        glUseProgram(shaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));

        //Bind VAO (contains VBO + attribute setup)
        glBindVertexArray(VAO);

        for(unsigned int i = 0; i < 10; i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float x = sin(glfwGetTime() + i);
            glm::vec3 axis = glm::normalize(glm::vec3(x, 1.0f, 0.0f));

            model = glm::rotate(model, (float)glfwGetTime(), axis);

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}