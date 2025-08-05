#include <kumquat.h>

const char* vertShaderSource =  "#version 460 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "layout (location = 1) in vec2 tPos;\n"
                                "out vec2 texCoords;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                "   texCoords = vec2(tPos.x, tPos.y);\n"
                                "}\0";

kqt_framebufferHandle_t kqt_generateFramebuffer(uint32_t FBOType, char *fragShaderPath, uint32_t screenWidth, uint32_t screenHeight)
{
    kqt_framebufferHandle_t tempFramebuffer;

    // Load fragment shader
    FILE *fragShaderFilePointer;
    fragShaderFilePointer = fopen(fragShaderPath, "rb");
    fseek(fragShaderFilePointer, 0, SEEK_END);
    long fragShaderSize = ftell(fragShaderFilePointer);
    rewind(fragShaderFilePointer);
    char* fragShaderSource = malloc(fragShaderSize+1);
    if(fragShaderFilePointer != NULL)
    {
        fread(fragShaderSource, 1, fragShaderSize, fragShaderFilePointer);
        fragShaderSource[fragShaderSize] = '\0';
    } else 
    {
        printf("Cannot open file\n");
    }
    fclose(fragShaderFilePointer);

    // Generate vertex shader
    uint32_t vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertShaderSource, NULL);
    glCompileShader(vertShader);

    // Generate fragment shader
    uint32_t fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);
    free(fragShaderSource);

    // Generate shader program
    tempFramebuffer.shaderProgram = glCreateProgram();
    glAttachShader(tempFramebuffer.shaderProgram, vertShader);
    glAttachShader(tempFramebuffer.shaderProgram, fragShader);
    glLinkProgram(tempFramebuffer.shaderProgram);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    if (FBOType == KQT_GENERATENEW)
    {
        // Generate framebuffer
        glGenFramebuffers(1, &tempFramebuffer.FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, tempFramebuffer.FBO);

        // Generate framebuffer texture
        tempFramebuffer.FBOTexture.width = screenWidth;
        tempFramebuffer.FBOTexture.height = screenHeight;
        glGenTextures(1, &tempFramebuffer.FBOTexture);
        glBindTexture(GL_TEXTURE_2D, tempFramebuffer.FBOTexture.memAddr);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tempFramebuffer.FBOTexture.memAddr, 0);

        // Generate render buffer Object
        glGenRenderbuffers(1, &tempFramebuffer.RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, tempFramebuffer.RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, tempFramebuffer.RBO);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    } 
    tempFramebuffer.FBOType = FBOType;

    kqt_textureHandle_t nullTextureHandle = {NULL};

    tempFramebuffer.iChannel[0] = nullTextureHandle;
    tempFramebuffer.iChannel[1] = nullTextureHandle;
    tempFramebuffer.iChannel[2] = nullTextureHandle;
    tempFramebuffer.iChannel[3] = nullTextureHandle;

    return tempFramebuffer;
}