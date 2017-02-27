//
// Created by logout on 15/02/17.
//
#ifndef SDLGUI_BUTTON_H
#define SDLGUI_BUTTON_H

#include "GUI_header.h"

class Button {

public:
    Button();
    Button(SDL_DisplayMode* computer, SDL_Window* window, SDL_Renderer* renderer, const char* name);

    void assignDisplayMode(SDL_DisplayMode* parent);
    SDL_DisplayMode* getDisplayMode();
    void assignWindow(SDL_Window* window);
    SDL_Window* getWindow();
    void assignRenderer(SDL_Renderer* renderer);
    SDL_Renderer* getRenderer();

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
    SDL_DisplayMode* m_computer;
};

#endif //SDLGUI_BUTTON_H
