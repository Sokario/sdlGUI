//
// Created by logout on 15/02/17.
//
#ifndef SDLGUI_BUTTON_H
#define SDLGUI_BUTTON_H

#include "GUI_header.h"

class Button {

public:
    Button();
    Button(SDL_DisplayMode* computer, SDL_Renderer* renderer, const char* name);

    void assignDisplayMode(SDL_DisplayMode* computer);
    SDL_DisplayMode* getDisplayMode();
    void assignRenderer(SDL_Renderer* renderer);
    SDL_Renderer* getRenderer();

    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setName(const char* name);
    const char* getName();

    ~Button();

private:
    SDL_DisplayMode* m_computer;
    SDL_Renderer* m_renderer;

    int m_width;
    int m_height;
    const char* m_name;
};

#endif //SDLGUI_BUTTON_H
