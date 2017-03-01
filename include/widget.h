//
// Created by logout on 08/02/17.
//
#ifndef SDLGUI_WIDGET_H
#define SDLGUI_WIDGET_H

#include <unordered_map>

#include "GUI_header.h"
#include "section.h"

class Widget {

public:
    Widget();
    Widget(const char* name, SDL_DisplayMode* computer, SDL_Renderer* renderer, int posX, int posY, int id);

    void assignDisplayMode(SDL_DisplayMode* computer);
    SDL_DisplayMode* getDisplayMode();
    void assignRenderer(SDL_Renderer* renderer);
    SDL_Renderer* getRenderer();
    void setId(int id);
    int getId();

    Section* addSection(const char* name);
    bool delSection(Section* section);

    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setName(const char* name);
    const char* getName();
    void setPitch(int pitch);
    int getPitch();
    void setPosX(int posX);
    int getPosX();
    void setPosY(int posY);
    int getPosY();
    void setMouseX(int posX);
    int getMouseX();
    void setMouseY(int posY);
    int getMouseY();
    void setMoving(bool moving);
    bool getMoving();
    void setQuitButton(int x, int y);
    bool getQuitButton();
    void setCallBackCode(int error);
    int getCallBackCode();

    void setWidgetRect(int width, int height, int posX, int posY);
    SDL_Rect* getWidgetRect();
    void setTitleRect(int width, int height, int posX, int posY);
    SDL_Rect* getTitleRect();
    void setQuitRect(int width, int height, int posX, int posY);
    SDL_Rect* getQuitRect();
    void drawDisplay();
    void updateDisplay();
    void updateWidget();

    bool getFocus(int x, int y);
    void updateWidgetPosition(int x, int y);
    void eventWatch(SDL_Event event);

    ~Widget();

private:
    SDL_DisplayMode* m_computer;
    SDL_Renderer* m_renderer;
    int m_id;
    std::unordered_map <int, Section*> m_section;

    int m_width;
    int m_height;
    const char* m_name;
    int m_pitch;
    int m_posX;
    int m_posY;
    int m_mouseX;
    int m_mouseY;
    bool m_moving;
    bool m_quitButton;
    int m_callback;

    SDL_Rect m_widget;
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

#endif //SDLGUI_WIDGET_H
