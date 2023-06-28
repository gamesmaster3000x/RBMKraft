#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <Shaders/ShaderLoader.h>
#include <Textures/stb_image.h>
#include <Profiler/Profiler.h>
#include <Meshes/Mesh.h>
#include <Meshes/ChunkMeshCtor.h>

static GLFWwindow* window;
static ShaderProgram* shaderProgram;
static int windowWidth = 800;
static int windowHeight = 600;

static int wWidth = 800;
static int wHeight = 600;

ChunkMeshCtor mesh = *new ChunkMeshCtor();
std::vector<float> vertBuf;
std::vector<unsigned int> indxBuf;

static bool fs = false;
static bool mh = true;

static double camPitch = 0;
static double camYaw = 0;
static glm::vec3 camPos = glm::vec3(0.0f);
static glm::mat4 camMatrix = glm::mat4(1.0f);

static double mouseSensitivity = 0.0025;
static double moveSpeed = 3;

static double frameTime = 0;

static Profiler fullscreenChange = *(new Profiler());
static Profiler mouseChange = *new Profiler;

static double fullscreenSwapTime = 0.5;
static double mouseSwapTime = 0.5;

unsigned int loadMesh()
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    Profiler meshCtor = *new Profiler;
    vertBuf = mesh.GetVertexData();
    indxBuf = mesh.GetIndexData();
    std::cout << "Constructed mesh in " << meshCtor.GetTotal() << " seconds\n";

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertBuf.size() * sizeof(float), vertBuf.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indxBuf.size() * sizeof(float), indxBuf.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(vertBuf.size() * sizeof(float) / 5 * 3));
    glEnableVertexAttribArray(1);

    return VAO;
}

unsigned int loadTexture()
{
    unsigned int texture;
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

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texture;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    shaderProgram->SetMat4("proj", glm::perspective(glm::radians(90.0f), (float)windowWidth / (float)windowHeight, 0.1f, 1000.0f));
    glViewport(0, 0, width, height);
}

void processInput() 
{
    if (mh) {
        double mousex, mousey;

        glfwGetCursorPos(window, &mousex, &mousey);

        if (!(camPitch + mousey * mouseSensitivity > glm::radians(90.0f)) && !(camPitch + mousey * mouseSensitivity < glm::radians(-90.0f)))
        {
            camPitch += mousey * mouseSensitivity;

        }

        camYaw += mousex * mouseSensitivity;

        glfwSetCursorPos(window, 0, 0);

        if (glfwGetKey(window, GLFW_KEY_W))
        {
            camPos += glm::normalize(glm::vec3(-camMatrix[2].x, 0.0f, camMatrix[0].x)) * (float)moveSpeed * (float)frameTime;
        }
        if (glfwGetKey(window, GLFW_KEY_S))
        {
            camPos -= glm::normalize(glm::vec3(-camMatrix[2].x, 0.0f, camMatrix[0].x)) * (float)moveSpeed * (float)frameTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A))
        {
            camPos += glm::normalize(glm::vec3(camMatrix[0].x, 0.0f, camMatrix[2].x)) * (float)moveSpeed * (float)frameTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D))
        {
            camPos -= glm::normalize(glm::vec3(camMatrix[0].x, 0.0f, camMatrix[2].x)) * (float)moveSpeed * (float)frameTime;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE))
        {
            camPos += glm::vec3(0.0f, -1.0f, 0.0f) * (float)moveSpeed * (float)frameTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        {
            camPos -= glm::vec3(0.0f, -1.0f, 0.0f) * (float)moveSpeed * (float)frameTime;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_F) && (fullscreenChange.GetLap() > fullscreenSwapTime))
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (fs)
        {
            glfwSetWindowMonitor(window, nullptr, 100, 100, wWidth, wHeight, 60);
            glfwWindowHint(GLFW_DECORATED, true);
            fs = false;
            windowWidth = wWidth;
            windowHeight = wHeight;
        }
        else
        {
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            fs = true;
            windowWidth = mode->width;
            windowHeight = mode->height;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            mh = true;
        }
        fullscreenChange.SetLap();
    }

    if (!fs) {
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && (mouseChange.GetLap() > mouseSwapTime))
        {
            if (mh)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                mh = false;
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                mh = true;
            }
            mouseChange.SetLap();
        }
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

    window = //glfwCreateWindow(windowWidth, windowHeight, "RBMKraft", NULL, NULL);
    glfwCreateWindow(windowWidth, windowHeight, "RBMKraft", nullptr, nullptr);
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

    unsigned int vertexShader;
    unsigned int fragmentShader;
    vertexShader = ShaderLoader::LoadShader(GL_VERTEX_SHADER, "Assets/Shaders/VertexShaders/VertShader.shader");
    fragmentShader = ShaderLoader::LoadShader(GL_FRAGMENT_SHADER, "Assets/Shaders/FragmentShaders/FragShader.shader");

    shaderProgram = new ShaderProgram(new unsigned int[6] {vertexShader, fragmentShader, 0, 0, 0, 0});
    shaderProgram->LinkProgram();

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);

    return 1;
}

int main(void)
{
    Profiler* profiler = new Profiler();

    if (!init())
    {
        glfwTerminate();
        return -1;
    }

    unsigned int VAO = loadMesh();
    unsigned int texture = loadTexture();

    glViewport(0, 0, windowWidth, windowHeight);
    
    glm::mat4 objPos = glm::mat4(1.0f);

    shaderProgram->Use();
    shaderProgram->SetMat4("proj", glm::perspective(glm::radians(90.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f));

    camPitch = 0;
    camYaw = 0;

    std::cout << "Initialisation completed in " << (*profiler).GetTotal() << " seconds.\n";

    while (!glfwWindowShouldClose(window)) 
    {
        profiler->SetLap();
        processInput();

        glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        objPos = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -(3.0f + 2 /** sin(glfwGetTime() * 0.5f)*/)));
        //objPos = glm::rotate(objPos, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        shaderProgram->SetMat4("objPos", objPos);

        camMatrix = glm::rotate(glm::mat4(1.0f), (float)camPitch, glm::vec3(1.0f, 0.0f, 0.0f));
        camMatrix = glm::rotate(camMatrix, (float)camYaw, glm::vec3(0.0f, 1.0f, 0.0f));
        camMatrix = glm::translate(camMatrix, camPos);
        shaderProgram->SetMat4("camPos", camMatrix);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indxBuf.size(), GL_UNSIGNED_INT, (void*)0);

        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
        frameTime = profiler->GetLap();
    }
    
    glfwTerminate();
    return 0;
}
