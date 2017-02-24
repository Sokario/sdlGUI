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
    void setQuitRect(int width, int height, int posX, int posY);
    SDL_Rect* getQuitRect();
    void setName(const char* name);
    const char* getName();
    int getWindowId();
    void drawDisplay();
    void updateRenderer();
    void updateDisplay();

    void isOnQuit(int x, int y);
    void callBackEvent(Widget* widget);
    void computeEvent(SDL_Event event);
    Widget* addWidget(const char* name, int posX = 0, int posY = 0);
    bool delWidget(Widget* widget);
    ~Screen();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Rect m_title;
    SDL_Rect m_quit;
    std::vector <Widget*> m_widget;

    int m_width;
    int m_height;
    bool m_escape;
    const char* m_name;
    int m_pitch;

    SDL_Surface* m_surfaceBack;
    SDL_Texture* m_textureBack;
    SDL_Surface* m_surfaceName;
    SDL_Texture* m_textureName;
    SDL_Rect m_rectName;

    SDL_DisplayMode m_parent;

    SDL_Surface* m_surfaceQuit;
    SDL_Texture* m_textureQuit;
    SDL_Rect m_rectQuit;
    bool m_quitButton;
};

#endif //SDLGUI_SCREEN_H
