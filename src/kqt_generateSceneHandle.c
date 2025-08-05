#include <kumquat.h>

kqt_sceneHandle_t kqt_generateSceneHandle()
{
    kqt_sceneHandle_t tempSceneHandle;

    // Define scene quad
    float vertices[] = 
    {
        -1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,     1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,     1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,     0.0f, 1.0f
    };  

    // Generate vertex array
    glGenVertexArrays(1, &tempSceneHandle); 
    uint32_t VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(tempSceneHandle);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return tempSceneHandle;
}