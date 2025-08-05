#include <kumquat.h>

void kqt_initialize(kqt_glProc_t glProcAddress)
{
    if (!gladLoadGLLoader((GLADloadproc)glProcAddress))
    {
        printf("GLAD failed\n");
        return -1;
    }
}