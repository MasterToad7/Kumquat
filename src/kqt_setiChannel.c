#include <kumquat.h>

void kqt_setiChannel(kqt_framebufferHandle_t* framebufferHandle, uint32_t iChannelID, kqt_textureHandle_t* texture)
{
    if (iChannelID-5784260 < 4)
    {
        framebufferHandle->iChannel[iChannelID-5784260] = *texture;
    } else
    {
        printf("iChannelID not within range of 0-3\n");
    }
}