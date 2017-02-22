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
    Widget(const char* name, SDL_DisplayMode computer, SDL_Renderer* renderer, int posX, int posY, int id);
    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setPosX(int posX);
    int getPosX();
    void setPosY(int posY);
    int getPosY();
    void setMouseX(int posX);
    int getMouseX();
    void setMouseY(int posY);
    int getMouseY();
    void setTitleRect(int width, int height, int posX, int posY);
    SDL_Rect* getTitleRect();
    void setQuitRect(int width, int height, int posX, int posY);
    SDL_Rect* getQuitRect();
    void setWidgetRect(int width, int height, int posX, int posY);
    SDL_Rect* getWidgetRect();

    void setName(const char* name);
    const char* getName();
    void setId(int id);
    int getId();
    ~Widget();

    void hideWidget();
    void showWidget();
    Section* addSection(const char* name);
    bool delSection(Section* section);

    void checkTitle(int x, int y);
    void updateWidgetPosition(int x, int y);
    void updateRenderer();
    void copyText();
    void drawDisplay(SDL_Surface* background);
    void clearWidget();
    void drawWidget();
    void updateWidget();

    void setCallBackCode(int error);
    int getCallBackCode();
    bool getFocus(int x, int y);
    void eventWatch(SDL_Event event);

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_title;
    SDL_Rect m_quit;
    SDL_Rect m_widget;
    int m_width;
    int m_height;
    int m_posX;
    int m_posY;
    int m_mouseX;
    int m_mouseY;
    const char* m_name;
    bool m_movable;
    std::unordered_map <int, Section*> m_section;
    SDL_DisplayMode m_computer;
    int m_id;
    int m_callback;
    bool m_widgetChanged;

    SDL_Texture* m_headerTitle;
    SDL_Surface* m_surfaceName;
    SDL_Texture* m_headerName;
    SDL_Texture* m_headerQuit;
    SDL_Rect m_rectName;
    SDL_Rect m_rectQuit;
};

#endif //SDLGUI_WIDGET_H
