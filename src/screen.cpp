//
// Created by logout on 07/02/17.
//
#include <SDL_video.h>
#include "../include/screen.h"

Screen::Screen(const char* name, int width, int height) {
    setWidth(width);
    setHeight(height);
    setName(name);
    if (SDL_WasInit(SDL_SUBSYTEM_MASK)) {
        SDL_GetDesktopDisplayMode(0, &m_parent);
        setTitleRect(m_parent.w, m_parent.h/32, 0, 0);
        m_window = SDL_CreateWindow(m_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(m_renderer, 40, 40, 40, 255);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);

        m_background = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0, 0, 0, 0);
        m_surfaceName = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0, 0, 0, 0);
        m_textureName = SDL_CreateTextureFromSurface(m_renderer, m_background);
        updateDisplay();
    }
    else {
        SDL_Log("SDL was not initialize!");
        exit(-1);
    }
}

void Screen::setWidth(int width) {
    m_width = width;
}

int Screen::getWidth() {
    return m_width;
}

void Screen::setHeight(int height) {
    m_height = height;
}

int Screen::getHeight() {
    return m_height;
}

void Screen::setTitleRect(int width, int height, int posX, int posY) {
    m_title.w = width;
    m_title.h = height;
    m_title.x = posX;
    m_title.y = posY;
}

SDL_Rect* Screen::getTitleRect() {
    return &m_title;
}

void Screen::setName(const char* name) {
    m_name = name;
}
const char* Screen::getName() {
    return m_name;
}

int Screen::getWindowId() {
    return SDL_GetWindowID(m_window);
}

void Screen::updateRenderer() {
    SDL_DestroyTexture(m_textureBack);
    m_textureBack = SDL_CreateTextureFromSurface(m_renderer, m_background);
    SDL_RenderCopy(m_renderer, m_textureBack, NULL, NULL);
    SDL_RenderCopy(m_renderer, m_textureName, NULL, &m_rectName);
    for (int it = 0; it < m_widget.size(); it++) {
        m_widget[it]->copyText();
    }
    SDL_RenderPresent(m_renderer);
}

void Screen::updateDisplay() {
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    SDL_FreeSurface(m_background);
    m_background = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_FillRect(m_background, NULL, SDL_MapRGBA(m_background->format, 255, 255, 255, 255));
    SDL_FillRect(m_background, &m_title, SDL_MapRGBA(m_background->format, 255, 255, 255, 255));
    drawDisplay();
    for (int it = 0; it < m_widget.size(); it++) {
        m_widget[it]->drawDisplay(m_background);
    }
    updateRenderer();
}

void Screen::drawDisplay() {
    SDL_Color white = {0, 0, 0, 0};
    m_rectName.w = m_title.w/64;
    m_rectName.h = m_title.h - m_title.h/4;
    m_rectName.x = m_rectName.w/4;
    m_rectName.y = m_title.y - m_rectName.y/2;

    TTF_Font* roboto = TTF_OpenFont("../../resources/Roboto-Bold.ttf", m_rectName.h);
    SDL_FreeSurface(m_surfaceName);
    m_surfaceName = TTF_RenderText_Blended(roboto, m_name, white);
    SDL_DestroyTexture(m_textureName);
    m_textureName = SDL_CreateTextureFromSurface(m_renderer, m_surfaceName);
    SDL_QueryTexture(m_textureName, NULL, NULL, &m_rectName.w, &m_rectName.h);
    TTF_CloseFont(roboto);
}

void Screen::callBackEvent(Widget *widget) {
//    std::cout << "Widget: " << widget->getName() << " | Error code: " << widget->getErrorCode() << std::endl;
    switch(widget->getCallBackCode()){
        case 0:
            std::cout << "No error: " << widget->getName() << std::endl;
            break;
        case 1:
            std::cout << "Display code: " << widget->getName() << std::endl;
            break;

        default:
            std::cout << "Error Unknown code from " << widget->getName() << " : " << widget->getCallBackCode() << std::endl;
            break;
    }
}

void Screen::computeEvent(SDL_Event event) {
    if (event.window.windowID == getWindowId()) {
        for (int it = 0; it < m_widget.size(); it++)
            if (m_widget[it]->getFocus(event.button.x, event.button.y)) {
                m_widget[it]->eventWatch(event);
                callBackEvent(m_widget[it]);
            }
    }
}

Widget* Screen::addWidget(const char* name, int posX, int posY) {
    int w = 0, h = 0, x = 0, y = 0;
    SDL_GetWindowSize(m_window, &w, &h);
    SDL_GetWindowPosition(m_window, &x, &y);
    Widget* widget = new Widget(name, m_parent, m_renderer, x + w/2 - (m_width/4 - m_width/16)/2 + posX, y + h/2 - m_height/16 + posY, (int) m_widget.size());
    m_widget.push_back(widget);

    return widget;
}
/*
bool Screen::delWidget(Widget *widget) {
    std::unordered_map<int, Widget*>::const_iterator widget_it = m_widget.find(widget->getWindowId());
    widget->~Widget();
    m_widget.erase(widget_it);
    std::cout << "Deleting widget... Number widget remaning: " << m_widget.size() << std::endl;
    return true;
}*/

Screen::~Screen() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}