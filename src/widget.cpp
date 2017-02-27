//
// Created by logout on 08/02/17.
//
#include "../include/widget.h"
#include <iostream>

Widget::Widget(const char* name, SDL_DisplayMode computer, SDL_Renderer* renderer, int posX, int posY, int id) {
    m_computer = computer;
    m_renderer = renderer;
    m_pitch = m_computer.w/512;
    m_quitButton = false;
    setWidth(m_computer.w/4 - m_computer.w/16);
    setHeight(m_computer.h/64 + m_computer.h/128);
    setPosX(posX);
    setPosY(posY);
    setMouseX(posX);
    setMouseY(posY);
    setName(name);
    m_moving = false;
    m_widgetChanged = true;
    setWidgetRect(m_width + 2*m_pitch, m_height + 2*m_pitch, m_posX - m_pitch, m_posY - m_pitch);
    setTitleRect(m_width, m_height, m_pitch, m_pitch);
    setQuitRect(m_height/2 + m_height/8, m_height/2 + m_height/8, m_pitch + m_width - m_height/2 - m_height/8 - (m_height - (m_height/2 + m_height/8))/2, m_pitch + (m_height - (m_height/2 + m_height/8))/2);
    setId(id);

    m_surfaceBack = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    m_textureBack = SDL_CreateTextureFromSurface(m_renderer, m_surfaceBack);
    m_surfaceQuit = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    m_textureQuit = SDL_CreateTextureFromSurface(m_renderer, m_surfaceQuit);
    m_surfaceName = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0, 0, 0, 0);
    m_textureName = SDL_CreateTextureFromSurface(m_renderer, m_surfaceName);
/*    if (SDL_WasInit(SDL_SUBSYTEM_MASK)) {
        m_window = SDL_CreateWindow(m_name, m_posX, m_posY, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        clearWidget();
    } else {
        SDL_Log("SDL was not initialize!");
        exit(-1);
    }*/
}

void Widget::setWidth(int width) {
    m_width = width;
}

int Widget::getWidth() {
    return m_width;
}

void Widget::setHeight(int height) {
    m_height = height;
}

int Widget::getHeight() {
    return m_height;
}

void Widget::setPosX(int posX) {
    m_posX = posX;
}

int Widget::getPosX() {
    return m_posX;
}

void Widget::setPosY(int posY) {
    m_posY = posY;
}

int Widget::getPosY() {
    return m_posY;
}

void Widget::setMouseX(int posX) {
    m_mouseX = posX;
}

int Widget::getMouseX() {
    return m_mouseX;
}

void Widget::setMouseY(int posY) {
    m_mouseY = posY;
}

int Widget::getMouseY() {
    return m_mouseY;
}

void Widget::setTitleRect(int width, int height, int posX, int posY) {
    m_title.w = width;
    m_title.h = height;
    m_title.x = posX;
    m_title.y = posY;
}

SDL_Rect* Widget::getTitleRect() {
    return &m_title;
}

void Widget::setQuitRect(int width, int height, int posX, int posY) {
    m_quit.w = width;
    m_quit.h = height;
    m_quit.x = posX;
    m_quit.y = posY;
}

SDL_Rect* Widget::getQuitRect() {
    return &m_quit;
}

void Widget::setWidgetRect(int width, int height, int posX, int posY) {
    m_widget.w = width;
    m_widget.h = height;
    m_widget.x = posX;
    m_widget.y = posY;
}

SDL_Rect* Widget::getWidgetRect() {
    return &m_widget;
}

void Widget::setName(const char* name) {
    m_name = name;
}

const char* Widget::getName() {
    return m_name;
}

void Widget::setId(int id) {
    m_id = id;
}

int Widget::getId() {
    return m_id;
}

Widget::~Widget() {}

Section* Widget::addSection(const char *name) {
    Section* section = new Section(m_computer, m_renderer, &m_title, name, (int) m_section.size());
    m_section.emplace(section->getId(), section);
    m_widgetChanged = true;
    return section;
}
/*
bool Widget::delSection(Section *section) {
    std::unordered_map<int, Section*> new_section;
    for (int i = 0; i < m_section.size(); i++) {
        if (i != section->getId()) {
            m_section[i]->setId((int) new_section.size());
            new_section.emplace(m_section[i]->getId(), m_section[i]);
        }
    }
    m_section.swap(new_section);
    section->~Section();
    int height = (int) m_section.size() * 120;
    setHeight(height);
    SDL_SetWindowSize(m_window, m_width, m_height);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
    drawHeader();
    return true;
}

void Widget::checkTitle(int x, int y) {
    //std::cout << "Mouse X: " << x << " | Mouse Y: " << y << std::endl;
    if ((x >= 0) && (x <= m_title.w) && (y >= 0) && (y <= m_title.h))
        m_titleM = true;
    else
        m_titleM = false;
    if ((x >= m_quit.x) && (x <= m_quit.x + m_quit.w) && (y >= m_quit.y) && (y <= m_quit.y + m_quit.h)) {
        m_quitB = true;
        //std::cout << "Mouse OK" << std::endl;
    }
    else
        m_quitB = false;
}*/

void Widget::updateWidgetPosition(int moveX, int moveY) {
    //std::cout << "Delta X: " << moveX - m_mouseX << " | Delta Y: " << moveY - m_mouseY << std::endl;
    int x = moveX - m_mouseX, y = moveY - m_mouseY;
//    int x = moveX, y = moveY;

    setPosX(m_posX + x);
    setPosY(m_posY + y);
    setMouseX(moveX);
    setMouseY(moveY);
    //SDL_SetWindowPosition(m_window, m_posX, m_posY);
    setWidgetRect(m_widget.w, m_widget.h, m_posX, m_posY);
    /*setTitleRect(m_title.w, m_title.h, m_posX, m_posY);
    setQuitRect(m_quit.w, m_quit.h, m_quit.x + x, m_quit.y + y);
    for (int it = 0; it < m_section.size(); it++) {
        m_section[it]->updateSectionPosition(x, y);
    }*/

    //std::cout << "Move X: " << m_mouseX << " | Move Y: " << m_mouseY << std::endl;
    //std::cout << "Mouse X: " << m_mouseX << " | Mouse Y: " << m_mouseY << std::endl;
}

void Widget::updateRenderer() {
    SDL_RenderCopy(m_renderer, m_headerTitle, NULL, NULL);
    SDL_RenderCopy(m_renderer, m_textureName, NULL, &m_rectName);
    for (int it = 0; it < m_section.size(); it++) {
        m_section[it]->updateRenderer();
    }
}

void Widget::drawDisplay() {
    SDL_RenderCopy(m_renderer, m_textureBack, NULL, &m_widget);
    SDL_RenderCopy(m_renderer, m_textureQuit, NULL, &m_rectQuit);
    SDL_RenderCopy(m_renderer, m_textureName, NULL, &m_rectName);
}

void Widget::updateDisplay() {
    SDL_FreeSurface(m_surfaceBack);
    m_surfaceBack = SDL_CreateRGBSurface(0, m_width + 2*m_pitch, m_height + 2*m_pitch, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    Uint8 value = 0;
    SDL_Rect m_shader;
    for (int i = 0; i < m_pitch; i++) {
        m_shader.w = m_widget.w - 2*i;
        m_shader.h = m_widget.h - 2*i;
        m_shader.x = i;
        m_shader.y = i;
        value += 120/m_pitch;
        SDL_FillRect(m_surfaceBack, &m_shader, SDL_MapRGBA(m_surfaceBack->format, 40, 40, 40, value));
    }

    SDL_FillRect(m_surfaceBack, &m_title, SDL_MapRGBA(m_surfaceBack->format, 20, 80, 160, 255));
    if (m_quitButton)
        SDL_FillRect(m_surfaceBack, &m_quit, SDL_MapRGBA(m_surfaceBack->format, 255, 255, 255, 255));

    for (int it = 0; it < m_section.size(); it++) {
        m_section[it]->drawDisplay(m_surfaceBack);
    }

    SDL_DestroyTexture(m_textureBack);
    m_textureBack = SDL_CreateTextureFromSurface(m_renderer, m_surfaceBack);

    m_rectQuit.w = m_quit.w/2;
    m_rectQuit.h = m_quit.h/2;
    m_rectQuit.x = m_widget.x + m_quit.x + m_quit.w/2 - m_rectQuit.w/2;
    m_rectQuit.y = m_widget.y + m_quit.y + m_quit.h/2 - m_rectQuit.h/2;
    SDL_FreeSurface(m_surfaceQuit);
    m_surfaceQuit = SDL_LoadBMP("../../resources/icon/close.bmp");
    SDL_SetColorKey(m_surfaceQuit, SDL_TRUE, SDL_MapRGBA(m_surfaceQuit->format, 0, 255, 0, 0));
    SDL_DestroyTexture(m_textureQuit);
    m_textureQuit = SDL_CreateTextureFromSurface(m_renderer, m_surfaceQuit);

    SDL_Color white = {255, 255, 255, 255};
    m_rectName.w = m_title.w/64;
    m_rectName.h = m_title.h - m_title.h/4;
    m_rectName.x = m_widget.x + m_title.x + m_rectName.w;
    m_rectName.y = m_widget.y + m_title.y - m_rectName.h/16;
    TTF_Font* roboto = TTF_OpenFont("../../resources/Roboto-Regular.ttf", m_rectName.h);
    SDL_FreeSurface(m_surfaceName);
    m_surfaceName = TTF_RenderText_Blended(roboto, m_name, white);
    SDL_DestroyTexture(m_textureName);
    m_textureName = SDL_CreateTextureFromSurface(m_renderer, m_surfaceName);
    SDL_QueryTexture(m_textureName, NULL, NULL, &m_rectName.w, &m_rectName.h);
    TTF_CloseFont(roboto);
}
/*
void Widget::clearWidget() {
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    setWidgetRect(m_width, m_height, m_widget.x, m_widget.y);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}*/

void Widget::drawWidget() {
    if (m_widgetChanged) {
        updateWidget();
        m_widgetChanged = false;
    }
    for (int it = 0; it < m_section.size(); it++)
        m_section[it]->drawSection();
}

void Widget::updateWidget() {
    int height = m_title.h;
    std::cout << "---- " << getName() << ": Pitch =  " << m_pitch << std::endl;
    for (int it = 0; it < m_section.size(); it++) {
        m_section[it]->updateSection();
        height += m_section[it]->getHeight();
        std::cout << "------------- " << getName() << ": Section = " << m_section[it]->getId() << " on " << m_section.size() << " -> H = " << m_section[it]->getHeight() << std::endl;
        if (it == 0)
            m_section[it]->setOffset(0);
        else
            m_section[it]->setOffset(m_section[it-1]->getHeight() + m_section[it-1]->getOffset());
    }
    setHeight(height);
    m_widget.h = m_height + 2*m_pitch;
}

bool Widget::isMoving() {
    return m_moving;
}

void Widget::isOnQuit(int x, int y) {
    m_quitButton = (x >= m_quit.x) && (x <= m_quit.x + m_quit.w) && (y >= m_quit.y) && (y <= m_quit.y + m_quit.h);
}

void Widget::setCallBackCode(int error) {
    m_callback = error;
}

int Widget::getCallBackCode() {
    return m_callback;
}

bool Widget::getFocus(int x, int y) {
    return (x >= m_widget.x) && (x <= m_widget.x + m_widget.w) && (y >= m_widget.y) && (y <= m_widget.y + m_widget.h);
}

void Widget::eventWatch(SDL_Event event) {
    int x = 0, y = 0;
    setCallBackCode(0);
    isOnQuit(event.button.x - m_widget.x, event.button.y - m_widget.y);
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        setMouseX(event.button.x);
        setMouseY(event.button.y);
    } else if (event.type == SDL_MOUSEMOTION) {
        x = event.motion.x;
        y = event.motion.y;
        if (SDL_GetMouseState(0, 0) & SDL_BUTTON_LMASK) {
            m_moving = true;
            updateWidgetPosition(x, y);
            setCallBackCode(1);
        } else {
            m_moving = false;
        }
    }
    std::cout << getName() << std::endl;
}