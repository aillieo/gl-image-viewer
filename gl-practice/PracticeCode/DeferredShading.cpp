#include "DeferredShading.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"
#include "../Utils/Model.h"

#include "../SceneManager.h"

// 展示 G-buffer
int showGBuffer(GLFWwindow* window)
{
    // 深度检测 开启
    glEnable(GL_DEPTH_TEST);
    
    
    int win_width,win_height;
    glfwGetWindowSize(window,&win_width,&win_height);
    
    
    Shader* shader = new Shader("DeferredShading/shader1.vsh","DeferredShading/shader1.fsh");
    Shader* shaderScreen= new Shader("DeferredShading/shader2.vsh","DeferredShading/shader2.fsh");
    
    
    
    Model* modelObj = new Model("nanosuit/nanosuit.obj");
    std::vector<glm::vec3> objectPositions;
    objectPositions.push_back(glm::vec3(-3.0,  -3.0, -3.0));
    objectPositions.push_back(glm::vec3( 0.0,  -3.0, -3.0));
    objectPositions.push_back(glm::vec3( 3.0,  -3.0, -3.0));
    objectPositions.push_back(glm::vec3(-3.0,  -3.0,  0.0));
    objectPositions.push_back(glm::vec3( 0.0,  -3.0,  0.0));
    objectPositions.push_back(glm::vec3( 3.0,  -3.0,  0.0));
    objectPositions.push_back(glm::vec3(-3.0,  -3.0,  3.0));
    objectPositions.push_back(glm::vec3( 0.0,  -3.0,  3.0));
    objectPositions.push_back(glm::vec3( 3.0,  -3.0,  3.0));
    
    
    
    float quadVertices[] = {
        // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        0.0f, -1.0f,  1.0f, 0.0f,
        
        -1.0f,  0.0f,  0.0f, 1.0f,
        0.0f, -1.0f,  1.0f, 0.0f,
        0.0f,  0.0f,  1.0f, 1.0f,
        
        // -----
        
        0.0f,  0.0f,  0.0f, 1.0f,
        0.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        
        0.0f,  0.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  0.0f,  1.0f, 1.0f,
        
        // -----
        
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 0.0f,  1.0f, 0.0f,
        
        -1.0f,  1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,
        0.0f,  1.0f,  1.0f, 1.0f,
        
        // -----
        
        0.0f,  1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f,  1.0f, 0.0f,
        
        0.0f,  1.0f,  0.0f, 1.0f,
        1.0f, 0.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f,
        
    };
    
    
    
    // bind VAO VBO
    unsigned int VBOscreen[4], VAOscreen[4];
    glGenVertexArrays(4, VAOscreen);
    glGenBuffers(4, VBOscreen);
    
    for(int i = 0 ; i < 4 ; i ++)
    {
        glBindVertexArray(VAOscreen[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOscreen[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices)/4, quadVertices + i * 24, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    
    shader->use();
    shaderScreen->use();
    shaderScreen->setInt("scene", 0);

    
    
    //=========================================
    
    // configure g-buffer framebuffer
    // ------------------------------
    unsigned int gBuffer;
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    unsigned int gPosition, gNormal, gAlbedoSpec;
    // position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, win_width, win_height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, win_width, win_height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, win_width, win_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);
    // create and attach depth buffer (renderbuffer)
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, win_width, win_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    //=========================================
    
    
    
    
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bindCameraToWindow(window, camera);
    
    
    while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        
        // 输入
        processInput(window);
        processInput(window, camera, deltaTime);
        
        
        
        // frame buffer binding
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
        
        glEnable(GL_DEPTH_TEST);
        
        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // geometry pass
        
        shader->use();
        glm::mat4 model;
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        for (unsigned int i = 0; i < objectPositions.size(); i++)
        {
            model = glm::mat4();
            model = glm::translate(model, objectPositions[i]);
            model = glm::scale(model, glm::vec3(0.25f));
            shader->setMat4("model", model);
            modelObj->Draw(*shader);
        }
        
        
        
        // frame buffer binding
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        
        
        // ===================================================
        
        glDisable(GL_DEPTH_TEST);

        // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
        // --------------------------------------------------------------------------------------------------------------------------
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderScreen->use();
        glActiveTexture(GL_TEXTURE0);
        
        // 反射
        shaderScreen->setInt("channels", 3);
        glBindVertexArray(VAOscreen[0]);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // 镜面
        shaderScreen->setInt("channels", 1);
        glBindVertexArray(VAOscreen[1]);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // 位置向量
        glBindVertexArray(VAOscreen[2]);
        shaderScreen->setInt("channels", 3);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // 法线
        glBindVertexArray(VAOscreen[3]);
        shaderScreen->setInt("channels", 3);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        
        
        glBindVertexArray(0);
        
        
        // 检查并调用事件，交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    
    
    
    glDeleteVertexArrays(4, VAOscreen);
    glDeleteBuffers(4, VBOscreen);
    
    
    unbindCamera(window);
    
    delete shader;
    delete shaderScreen;
    delete camera;
    
    return 0;
    
}

// 使用延迟着色
int useDeferredShading(GLFWwindow* window)
{

	return 0;
}
