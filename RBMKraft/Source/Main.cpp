#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <Shaders/ShaderLoader.h>
#include <Textures/stb_image.h>

float vertices[] = { //(X, Y, Z), (R, G, B), (UVX, UVY) 
    0.5f,  -0.5f, 0.0f,    0.0f, 0.0f, 0.0f,    1.0f, 1.0f,//BR
    -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,//BL
    -0.5f, 0.5f,  0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f,//TL
    0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f //TR
};

unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};


static GLFWwindow* window;


unsigned int loadMesh()
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    return VAO;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput() 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int init()
{
    fprintf(stdout, "Initialising GLFW...\n");
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialise GLFW, exiting...\n");
        return 0;
    }
    fprintf(stdout, "Sucessfully initialised GLFW.\n");

    window = glfwCreateWindow(800, 800, "RBMKraft", NULL, NULL);
    glfwMakeContextCurrent(window);

    fprintf(stdout, "Initialising GLAD...\n");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialise GLAD, exiting...\n");
        return 0;
    }
    fprintf(stdout, "Sucessfully initialised GLAD.\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return 1;
}

int main(void)
{
    if (!init())
    {
        glfwTerminate();
        return -1;
    }

    unsigned int vertexShader;
    unsigned int fragmentShader;
    vertexShader = ShaderLoader::LoadShader(GL_VERTEX_SHADER, "Assets/Shaders/VertexShaders/StraightThroughRGB.shader");
    fragmentShader = ShaderLoader::LoadShader(GL_FRAGMENT_SHADER, "Assets/Shaders/FragmentShaders/CustomVertColor.shader");

    ShaderProgram shaderProgram = *(new ShaderProgram(new unsigned int[6] {vertexShader, fragmentShader, 0, 0, 0, 0}));
    shaderProgram.LinkProgram();

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO = loadMesh();


    int width, height, nrChannels;
    unsigned char* data = stbi_load("Assets/Textures/Blocks/Test.png", &width, &height, &nrChannels, 0);

    if (!data)
    {
        fprintf(stderr, "Failed to read image file.\n"); 
        glfwTerminate();
        return -1;
    }
    else
    {
        fprintf(stdout, "Successfully read image file.\n");
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    glViewport(0, 0, 800, 800);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) 
    {
        processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
