#include "SimpleTransform.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include <math.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "../Utils/Shader.h"
#include "../Utils/GLMethod.h"

#include "../Utils/TextureLoader.h"

int rotate2D()
{
    
    GLFWwindow* window = createWindow();
    if(nullptr == window)
    {
        return -1;
    }
        
    
    // TEXTURE !!!
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = TextureLoader::loadTexture("doge.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    TextureLoader::freeData(data);
    
    
    
    // SHADER
    Shader* shader = new Shader("SimpleTransform/shader1.vsh","SimpleTransform/shader1.fsh");

    
    
    // VERTICES:
    // x, y, z, s, t
    float vertices[] = {
        -0.5, 0.5, 0.0f, 0.0f, 0.0f, // left top
        0.5, 0.5, 0.0f,  1.0f, 0.0f, // right top
        -0.5, -0.5, 0.0f,  0.0f, 1.0f, // left down
        0.5, -0.5, 0.0f,  1.0f, 1.0f // right down
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };
    
    
    
    // bind VAO VBO EBO
    unsigned int VBO, VAO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    
    
    
    
    
    
    
    // 渲染循环
    while(!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);
        
        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        
        unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
        glm::mat4 transform;
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        
        
        
        
        // draw triangle
        shader->use();
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        // 检查并调用事件，交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    delete shader;
    
    glfwTerminate();  
    return 0; 
    
}
