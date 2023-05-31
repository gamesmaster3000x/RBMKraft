#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 oColor;\n"
"void main()\n"
"{\n"
"oColor = aColor;\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 oColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(oColor, 1.0f);\n"
"}\0";


float vertices[] = {
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, //BR
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, //BL
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, //TL
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f//TR
};

unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(void)
{
    fprintf(stdout, "Initialising GLFW...\n");
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialise GLFW, exiting...\n");
        return -1;
    }
    fprintf(stdout, "Sucessfully initialised GLFW.\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "ColorSquare", NULL, NULL);
    glfwMakeContextCurrent(window);

    fprintf(stdout, "Initialising GLAD...\n");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        fprintf(stderr, "Failed to initialise GLAD, exiting...\n");
        glfwTerminate();
        return -1;
    }
    fprintf(stdout, "Sucessfully initialised GLAD.\n");

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    {
        int success;
        char infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            fprintf(stderr, infoLog);
            fprintf(stderr, "\n");
            glfwTerminate();
            return -1;
        }
        else 
        {
            fprintf(stdout, "Sucessfully compiled vertex shader.\n");
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            fprintf(stderr, infoLog);
            fprintf(stderr, "\n");
            glfwTerminate();
            return -1;
        }
        else
        {
            fprintf(stdout, "Sucessfully compiled fragment shader 1.\n");
        }
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, 800, 600);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float lastFrameTime = 0;

    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
