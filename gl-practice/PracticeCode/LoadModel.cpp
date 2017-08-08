#include "LoadModel.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"

#include "../SceneManager.h"
#include "../Utils/TextureLoader.h"

#include "../Utils/Mesh.h"
#include "../Utils/Model.h"

#include <sstream>
#include <iostream>


int loadModel(GLFWwindow* window)
{

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    
    
    int win_width,win_height;
    glfwGetWindowSize(window,&win_width,&win_height);
    
    
    // build and compile shaders
    // -------------------------
    Shader* shader = new Shader("LoadModel/shader1.vsh", "LoadModel/shader1.fsh");
    
    // load models
    // -----------
    Model* modelObj = new Model("../../gl-practice/_models/nanosuit/nanosuit.obj");
    
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    bindCameraToWindow(window, camera);

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // render loop
    // -----------
    while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        // -----
        processInput(window);
        processInput(window, camera, deltaTime);
        
        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // don't forget to enable shader before setting uniforms
        shader->use();
        
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)win_width / (float)win_height, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        
        // render the loaded model
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        shader->setMat4("model", model);
        modelObj->Draw(*shader);
        
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
	unbindCamera(window);

    delete shader;
    delete modelObj;
    delete camera;
    
    return 0;
}
