//
// Created by logout on 07/02/17.
//
#ifndef SDLGUI_SCREEN_H
#define SDLGUI_SCREEN_H

#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include "sdlGUI.h"
#include "widget.h"

class Screen {

public:
    Screen(const char* name, int width = 640, int height = 480);
    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setTitleRect(int width, int height, int posX, int posY);
    SDL_Rect* getTitleRect();
    void setName(const char* name);
    const char* getName();
    int getWindowId();
    void drawDisplay();
    void updateRenderer();
    void updateDisplay();
    void callBackEvent(Widget* widget);
    void computeEvent(SDL_Event event);
    Widget* addWidget(const char* name, int posX = 0, int posY = 0);
    bool delWidget(Widget* widget);
    ~Screen();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Rect m_title;
    std::vector <Widget*> m_widget;

    int m_width;
    int m_height;
    const char* m_name;

    SDL_Surface* m_background;
    SDL_Texture* m_textureBack;
    SDL_Surface* m_surfaceName;
    SDL_Texture* m_textureName;
    SDL_Rect m_rectName;

    SDL_DisplayMode m_parent;
};

#endif //SDLGUI_SCREEN_H
