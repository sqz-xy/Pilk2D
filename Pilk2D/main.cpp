/* Resources
 * - https://learnopengl.com/Getting-started/Hello-Window
 */

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad.h"
#include "glfw3.h"
#include "stb_image.h"
#include "irrKlang.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <filesystem>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

 /**
  * \brief Prototype for viewport adjusting
  * \param window The current window
  * \param width width of the window
  * \param height height of the window
  */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
 * \brief Prototype for input processing
 * \param window The current window
 */
void processInput(GLFWwindow* window);

/**
 * \brief Loads a shader file
 * \param pFileName The name of the shader file to load
 * \param pShaderSource A reference The source code of the shader
 * \return A bool representing if the operation was successful
 */
bool LoadShader(const char* pFileName, std::string& pShaderSource)
{
    pShaderSource.clear();
    std::ifstream shader(pFileName);

    if (shader)
    {
        char ch;
        while (shader.get(ch))
        {
            pShaderSource += ch;
        }
        return true;
    }
    return false;
}

/**
 * \brief Compiles a shader
 * \param pShaderType The type of shader
 * \param pFileName The shaders file name
 * \param pShaderBuffer The shaders buffer
 * \param pSuccess The success status
 * \param pInfoLog The info log
 * \return Boolean value representing if the operation was successful
 */
bool compile_shader(const GLenum& pShaderType, const char* pFileName, unsigned int* pShaderBuffer, int* pSuccess, char* pInfoLog)
{
    std::string shaderSourceString;
    const char* shaderSource;

    if (!LoadShader(pFileName, shaderSourceString))
    {
        std::cout << pShaderType << " File not loaded" << std::endl;
        return false;
    }

    shaderSource = shaderSourceString.c_str();
    *pShaderBuffer = glCreateShader(pShaderType);
    glShaderSource(*pShaderBuffer, 1, &shaderSource, NULL);
    glCompileShader(*pShaderBuffer);

    glGetShaderiv(*pShaderBuffer, GL_COMPILE_STATUS, pSuccess);
    if (!pSuccess)
    {
        glGetShaderInfoLog(*pShaderBuffer, 512, NULL, pInfoLog);
        std::cout << pShaderType << " shader compilation error" << std::endl;
        return false;
    }
    return true;
}

/**
 * \brief Creates a shader program
 * \param pVertexShader - The vertex shader handle
 * \param pFragmentShader - The fragment shader handle
 * \param pShaderProgram - The shader program handle
 * \return A bool representing if the operation was successful
 */
bool create_shader_program(unsigned int* pVertexShader, unsigned int* pFragmentShader, unsigned int* pShaderProgram)
{
    int success;
    char infoLog[512];

    compile_shader(GL_VERTEX_SHADER, "resources/shaders/VertexShader.vert", pVertexShader, &success, infoLog);
    compile_shader(GL_FRAGMENT_SHADER, "resources/shaders/FragmentShader.frag", pFragmentShader, &success, infoLog);

    *pShaderProgram = glCreateProgram();

    glAttachShader(*pShaderProgram, *pVertexShader);
    glAttachShader(*pShaderProgram, *pFragmentShader);
    glLinkProgram(*pShaderProgram);

    glGetProgramiv(*pShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(*pShaderProgram, 512, NULL, infoLog);
        std::cout << "Shader program attachment error" << std::endl;
        return false;
    }
    return true;
}

/**
 * \brief The main program
 * \return exit code
 */
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Set the window as the main context of the current thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD as it manages opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport dimensions
    glViewport(0, 0, 800, 600);

    // Resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float colour[4] = { 1.0f, 0.5f, 0.2f, 1.0f };
    float vertices[] = {
        // positions          // normals          // texture coords
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    // Creates a shader program
    unsigned int vertexShader, fragmentShader, shaderProgram;
    if (!create_shader_program(&vertexShader, &fragmentShader, &shaderProgram)) return -1;

    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("resources/textures/capsule.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    

    // ImGUI Init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Proj
    float aspect = (float)width / height;
    glm::mat4 proj = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 1.0f, -1.0f);
    
    // Model
    glm::mat4 identity(1.0f);
    glm::vec3 pos(0.1f, 0.1f, 1.0f);
    glm::mat4 trans = glm::translate(identity, pos);

    // View
    glm::vec3 camPos(0.0f, 0.0f, 1.0f);
    glm::vec3 target = camPos;
    camPos.z = 0;

    glm::mat4 view = glm::lookAt(camPos, target, glm::vec3(0, 1, 0));

    // Simple update loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ImGui frame init
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Input processing
        processInput(window);

        // Rendering commands here
        // ...

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glUseProgram(shaderProgram);

        // Modify shader uniforms

        glUniform1i(glGetUniformLocation(shaderProgram, "uDiffuse"), 0);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uModel"), 1, GL_FALSE, &(trans)[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uProjection"), 1, GL_FALSE, &(proj)[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uView"), 1, GL_FALSE, &(view)[0][0]);
        glUniform4f(glGetUniformLocation(shaderProgram, "uColour"), colour[0], colour[1], colour[2], colour[3]);

        // Translate
        //pos.x += 0.01f;
        //trans = glm::translate(identity, pos);

        // MoveCam
        camPos.x += 1.0f;
        target = camPos;
        camPos.z = 0;

        glm::mat4 view = glm::lookAt(camPos, target, glm::vec3(0, 1, 0));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // UI drawing
        ImGui::Begin("ImGui Test");
        ImGui::Text("Goo goo ga ga");
        ImGui::ColorEdit4("Colour", colour);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Clear Buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Delete Shaders
    glDeleteProgram(shaderProgram);

    // Delete all resources
    glfwTerminate();
    return 0;
}

/**
 * \brief Function for viewport adjusting
 * \param window The current window
 * \param width width of the window
 * \param height height of the window
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * \brief Function for input processing
 * \param window The current window
 */
void processInput(GLFWwindow* window)
{
    // Exit if escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}