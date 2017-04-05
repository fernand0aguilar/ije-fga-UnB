#ifndef LTEXTURE_H
#define LTEXTURE_H

#include<iostream>
#include "sdl2core.hpp"
#include "logger.hpp"

class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile( std::string path,SDL_Renderer *gRenderer );

    void free();

    void render( int , int , SDL_Renderer* , SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif
