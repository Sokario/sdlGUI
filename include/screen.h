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
    Screen();
    Screen(const char* name, int width = 640, int height = 480);

    void assignWindow(SDL_Window* window);
    SDL_Window* getWindow();
    void assignRenderer(SDL_Renderer* renderer);
    SDL_Renderer* getRenderer();
    int getWindowId();

    Widget* addWidget(const char* name, int posX = 0, int posY = 0);
    bool delWidget(Widget* widget);

    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setName(const char* name);
    const char* getName();
    void setPitch(int pitch);
    int getPitch();
    void setQuitButton(int x, int y);
    bool getQuitButton();

    void setTitleRect(int width, int height, int posX, int posY);
    SDL_Rect* getTitleRect();
    void setQuitRect(int width, int height, int posX, int posY);
    SDL_Rect* getQuitRect();
    void drawDisplay();
    void updateDisplay();
    void updateTitle();

    void callBackEvent(Widget* widget);
    void computeEvent(SDL_Event event);

    ~Screen();

private:
    SDL_DisplayMode* m_computer;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::vector <Widget*> m_widget;

    int m_width;
    int m_height;
    const char* m_name;
    int m_pitch;
    bool m_quitButton;

    SDL_Rect m_title;
    SDL_Surface* m_surfaceBack;
    SDL_Texture* m_textureBack;
    SDL_Surface* m_surfaceName;
    SDL_Texture* m_textureName;
    SDL_Rect m_rectName;

    SDL_Rect m_quit;
    SDL_Surface* m_surfaceQuit;
    SDL_Texture* m_textureQuit;
    SDL_Rect m_rectQuit;
};

#endif //SDLGUI_SCREEN_H
