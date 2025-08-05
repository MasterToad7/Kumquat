#include <kumquat.h>
#include <GLFW/glfw3.h>


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Kumquat", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    kqt_initialize(glfwGetProcAddress);
    kqt_sceneHandle_t sceneHandle = kqt_generateSceneHandle();

    kqt_textureHandle_t texture = kqt_loadTexture("image.jpg", KQT_JPG);

    kqt_framebufferHandle_t framebuffer = kqt_generateFramebuffer(KQT_USEDEFAULT, "test2.frag", 960, 540);

    kqt_setiChannel(&framebuffer, KQT_ICHANNEL0, &texture);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        kqt_renderFramebuffer(&sceneHandle, &framebuffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}