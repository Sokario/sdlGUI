//
// Created by logout on 15/02/17.
//
#ifndef SDLGUI_BUTTON_H
#define SDLGUI_BUTTON_H

#include <unordered_map>
#include "GUI_header.h"

class Button {

public:
    Button(SDL_DisplayMode parent, SDL_Window* window, SDL_Renderer* renderer, const char* name);
    void setName(const char* name);
    const char* getName();
    void setHeight(int height);
    int getHeight();
    ~Button();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    const char* m_name;
    int m_height;
    SDL_DisplayMode m_parent;
};

#endif //SDLGUI_BUTTON_H
