#include "AdvancedLighting.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"


// 点光源照地板 使用Phong
int floorPhong(GLFWwindow* window)
{
    
    // 深度检测 开启
    glEnable(GL_DEPTH_TEST);
    
    int win_width,win_height;
    glfwGetWindowSize(window,&win_width,&win_height);
    
    
    Shader* shader = new Shader("AdvancedLighting/shader1.vsh","AdvancedLighting/shader1.fsh");
    
    float planeVertices[] = {
        // positions            // normals         // texcoords
        10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
        
        10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
        10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };
    
    
    
    // bind VAO VBO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    
    
    // load texture
    glActiveTexture(GL_TEXTURE0);
    unsigned int texturePlane = TextureLoader::loadTexture("wood.png");
    
    
    
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bindCameraToWindow(window, camera);
    
    
    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
    
    shader->use();
    shader->setInt("floorTexture", 0);
    
    
    while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        
        // 输入
        processInput(window);
        processInput(window, camera, deltaTime);
        
        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        
        shader->use();
        glm::mat4 model;
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        
        
        shader->setVec3("viewPos", camera->Position);
        shader->setVec3("lightPos", lightPos);
        
        // floor
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texturePlane);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        
        
        glBindVertexArray(0);
        
        
        // 检查并调用事件，交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    
    
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    
    unbindCamera(window);
    
    delete shader;
    delete camera;
    
    return 0;
}

// 点光源照地板 使用Blinn-Phong
int floorBlinnPhong(GLFWwindow* window)
{
    
    // 深度检测 开启
    glEnable(GL_DEPTH_TEST);
    
    int win_width,win_height;
    glfwGetWindowSize(window,&win_width,&win_height);
    
    
    Shader* shader = new Shader("AdvancedLighting/shader2.vsh","AdvancedLighting/shader2.fsh");
    
    float planeVertices[] = {
        // positions            // normals         // texcoords
        10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
        
        10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
        10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };
    
    
    
    // bind VAO VBO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    
    
    // load texture
    glActiveTexture(GL_TEXTURE0);
    unsigned int texturePlane = TextureLoader::loadTexture("wood.png");
    
    
    
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bindCameraToWindow(window, camera);
    
    
    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
    
    shader->use();
    shader->setInt("floorTexture", 0);
    
    
    while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        
        // 输入
        processInput(window);
        processInput(window, camera, deltaTime);
        
        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        
        shader->use();
        glm::mat4 model;
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        
        
        shader->setVec3("viewPos", camera->Position);
        shader->setVec3("lightPos", lightPos);
        
        // floor
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texturePlane);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        
        
        glBindVertexArray(0);
        
        
        // 检查并调用事件，交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    
    
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    
    unbindCamera(window);
    
    delete shader;
    delete camera;
    
    return 0;
}
