#ifndef KUMQUAT_H
#define KUMQUAT_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define KQT_USEDEFAULT 5783260
#define KQT_GENERATENEW 5783261

#define KQT_ICHANNEL0 5784260
#define KQT_ICHANNEL1 5784261
#define KQT_ICHANNEL2 5784262
#define KQT_ICHANNEL3 5784263

#define KQT_PNG 578764
#define KQT_JPG 578574

typedef void (*kqt_glProc_t)(void);

typedef uint32_t kqt_sceneHandle_t;

typedef struct kqt_textureHandle_t
{
    uint32_t memAddr;
    uint32_t width;
    uint32_t height;
} kqt_textureHandle_t;

typedef struct kqt_framebufferHandle_t
{
    uint32_t FBO;
    uint32_t RBO;
    kqt_textureHandle_t FBOTexture;
    uint32_t FBOType;
    uint32_t shaderProgram;
    kqt_textureHandle_t iChannel[4];
} kqt_framebufferHandle_t;

// Makes sure Kumquat is linked properly
void kqt_sanityCheck();

// Initializes GLAD
void kqt_initialize(kqt_glProc_t glProcAddress);

// Generate a handle for the scene
kqt_sceneHandle_t kqt_generateSceneHandle();

// Generate a framebuffer and a handle for the framebuffer
kqt_framebufferHandle_t kqt_generateFramebuffer(uint32_t FBOType, char* fragShaderPath, uint32_t screenWidth, uint32_t screenHeight);

// Bind texture to iChannel
void kqt_setiChannel(kqt_framebufferHandle_t* framebufferHandle, uint32_t iChannelID, kqt_textureHandle_t* texture);

// Run the main shader
void kqt_renderFramebuffer(kqt_sceneHandle_t* sceneHandle, kqt_framebufferHandle_t* framebufferHandle);

// Load texture
kqt_textureHandle_t kqt_loadTexture(char* texturePath, uint32_t textureType);

#endif