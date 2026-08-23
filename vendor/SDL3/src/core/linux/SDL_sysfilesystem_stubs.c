#include "SDL_internal.h"
#include <SDL3/SDL_filesystem.h>

char *SDL_SYS_GetCurrentDirectory(void)
{
    return NULL;
}

bool SDL_SYS_RemovePath(const char *path)
{
    (void)path;
    return false;
}

bool SDL_SYS_RenamePath(const char *oldpath, const char *newpath)
{
    (void)oldpath; (void)newpath;
    return false;
}

bool SDL_SYS_CopyFile(const char *oldpath, const char *newpath)
{
    (void)oldpath; (void)newpath;
    return false;
}

bool SDL_SYS_EnumerateDirectory(const char *path, SDL_EnumerateDirectoryCallback cb, void *userdata)
{
    (void)path; (void)cb; (void)userdata;
    return false;
}

bool SDL_SYS_CreateDirectory(const char *path)
{
    (void)path;
    return false;
}

bool SDL_SYS_GetPathInfo(const char *path, SDL_PathInfo *info)
{
    (void)path;
    if (info) {
        SDL_zerop(info);
    }
    return false;
}
