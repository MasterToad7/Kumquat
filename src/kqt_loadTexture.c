#include <kumquat.h>

kqt_textureHandle_t kqt_loadTexture(char* texturePath, uint32_t textureType)
{
    kqt_textureHandle_t tempTextureHandle;

    glGenTextures(1, &tempTextureHandle.memAddr);
    glBindTexture(GL_TEXTURE_2D, tempTextureHandle.memAddr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *textureBytes = stbi_load(texturePath, &tempTextureHandle.width, &tempTextureHandle.height, &nrChannels, 0);
    if (textureBytes && textureType == KQT_JPG)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tempTextureHandle.width, tempTextureHandle.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureBytes);
        glGenerateMipmap(GL_TEXTURE_2D);
    } 
    else if (textureBytes && textureType == KQT_PNG)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempTextureHandle.width, tempTextureHandle.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBytes);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    else
    {
        printf("Failed to load texture");
    }
    stbi_image_free(textureBytes);

    return tempTextureHandle;
}