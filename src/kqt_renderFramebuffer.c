#include <kumquat.h>

void kqt_renderFramebuffer(kqt_sceneHandle_t* sceneHandle, kqt_framebufferHandle_t* framebufferHandle)
{
    // Bind necessary buffers and textures
    glUseProgram(framebufferHandle->shaderProgram);
    if (framebufferHandle->FBOType == KQT_GENERATENEW)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle->FBO);
        glBindTexture(GL_TEXTURE_2D, framebufferHandle->FBOTexture.memAddr);
        glBindRenderbuffer(GL_RENDERBUFFER, framebufferHandle->RBO);
    }
    glBindVertexArray(*sceneHandle);

    for (int i=0; i<4; i++)
    {
        if (framebufferHandle->iChannel[i].memAddr != NULL)
        {
            glActiveTexture(GL_TEXTURE1+i);
            glBindTexture(GL_TEXTURE_2D, framebufferHandle->iChannel[i].memAddr);
            char iChannelNUM[] = {'i', 'C', 'h', 'a', 'n', 'n', 'e', 'l', 48+i, '\0'};
            glUniform1i(glGetUniformLocation(framebufferHandle->shaderProgram, iChannelNUM), 1+i);
        }
    }

    // Clear and draw scene
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_QUADS, 0, 4);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}