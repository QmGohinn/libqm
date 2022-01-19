#include <asm-generic/ioctl.h>

#define type 'k'

#define PLAY_TONE _IOW(type, 1, int)
#define PLAY_STOP _IOW(type, 2, int)
