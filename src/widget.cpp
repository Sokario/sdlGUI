//
// Created by logout on 08/02/17.
//
#include "../include/widget.h"
#include <iostream>

Widget::Widget(const char* name, SDL_DisplayMode computer, SDL_Renderer* renderer, int posX, int posY, int id) {
    m_computer = computer;
    m_renderer = renderer;
    setWidth(m_computer.w/4 - m_computer.w/16);
    setHeight(m_computer.h/64 + m_computer.h/128);
    setPosX(posX);
    setPosY(posY);
    setMouseX(0);
    setMouseY(0);
    setName(name);
    m_movable = true;
    m_widgetChanged = true;
    setTitleRect(m_width, m_height, m_posX, m_posY);
    setQuitRect(m_height/2 + m_height/8, m_height/2 + m_height/8, m_posX + m_width - m_height/2 - m_height/8 - (m_height - (m_height/2 + m_height/8))/2, m_posY + (m_height - (m_height/2 + m_height/8))/2);
    setWidgetRect(m_width, m_height, m_posX, m_posY);
    setId(id);

    m_surfaceName = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0, 0, 0, 0);
    m_headerName = SDL_CreateTextureFromSurface(m_renderer, m_surfaceName);
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
    setPosX(m_posX + moveX - m_mouseX);
    setPosY(m_posY + moveY - m_mouseY);
    //setMouseX(moveX);
    //setMouseY(moveY);
    //SDL_SetWindowPosition(m_window, m_posX, m_posY);
    setWidgetRect(m_widget.w, m_widget.h, m_posX, m_posY);
    setTitleRect(m_title.w, m_title.h, m_posX, m_posY);
    setQuitRect(m_quit.w, m_quit.h, m_quit.x + moveX - m_mouseX, m_quit.y + moveY - m_mouseY);

    //std::cout << "Move X: " << m_mouseX << " | Move Y: " << m_mouseY << std::endl;
    //std::cout << "Mouse X: " << m_mouseX << " | Mouse Y: " << m_mouseY << std::endl;
}

void Widget::updateRenderer() {
    SDL_RenderCopy(m_renderer, m_headerTitle, NULL, NULL);
    SDL_RenderCopy(m_renderer, m_headerName, NULL, &m_rectName);
    for (int it = 0; it < m_section.size(); it++) {
        m_section[it]->updateRenderer();
    }
}

void Widget::copyText() {
    SDL_RenderCopy(m_renderer, m_headerName, NULL, &m_rectName);
}

void Widget::drawDisplay(SDL_Surface* background) {
    SDL_FillRect(background, &m_title, SDL_MapRGBA(background->format, 20, 80, 160, 255));
    SDL_FillRect(background, &m_quit, SDL_MapRGBA(background->format, 255, 255, 255, 255));
    for (int it = 0; it < m_section.size(); it++) {
        m_section[it]->drawDisplay(background);
    }

    SDL_Color white = {0, 0, 0, 0};
    m_rectName.w = m_title.w/64;
    m_rectName.h = m_title.h - m_title.h/4;
    m_rectName.x = m_title.x + m_rectName.w;
    m_rectName.y = m_title.y - m_rectName.h/16;

    TTF_Font* roboto = TTF_OpenFont("../../resources/Roboto-Regular.ttf", m_rectName.h);
    SDL_FreeSurface(m_surfaceName);
    m_surfaceName = TTF_RenderText_Blended(roboto, m_name, white);
    SDL_DestroyTexture(m_headerName);
    m_headerName = SDL_CreateTextureFromSurface(m_renderer, m_surfaceName);
    SDL_QueryTexture(m_headerName, NULL, NULL, &m_rectName.w, &m_rectName.h);
    TTF_CloseFont(roboto);

//    SDL_RenderCopy(m_renderer, m_headerName, NULL, &m_rectName);

//    SDL_RenderPresent(m_renderer);

/*
    SDL_SetRenderDrawColor(m_renderer, 20, 80, 160, 255);
    SDL_RenderFillRect(m_renderer, &m_title);
//    Uint8 val = 0;
//    for (int i = m_height/2 - (m_height/4 + m_height/16); i >= 0; i--) {
//        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, val);
//        SDL_RenderDrawLine(m_renderer, 0, m_title.h - i, m_title.w, m_title.h - i);
//        val += 4 * m_title.h / (m_height / 2 - (m_height / 4 + m_height / 16));
//    }

//    if (m_quitB)
//        SDL_SetRenderDrawColor(m_renderer, 240, 20, 0, 255);
//    else
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &m_quit);

    SDL_SetRenderDrawColor(m_renderer, 20, 20, 20, 255);
    SDL_RenderDrawLine(m_renderer, m_quit.x + m_quit.w/4, m_quit.y + m_quit.h/4, m_quit.x + m_quit.w - m_quit.w/4, m_quit.y + m_quit.h - m_quit.h/4);
    SDL_RenderDrawLine(m_renderer, m_quit.x + m_quit.w - m_quit.w/4, m_quit.y + m_quit.h/4, m_quit.x + m_quit.w/4, m_quit.y + m_quit.h - m_quit.h/4);

    SDL_Rect title;
    SDL_Color white = {255, 255, 255, 0};
    title.w = m_title.w/64;
    title.h = m_title.h - m_title.h/4 - m_title.h/8;
    title.x = m_title.x + title.w;
    title.y = m_title.y + title.h/4 - title.h/8;

    TTF_Font* roboto = TTF_OpenFont("../../resources/Roboto-Regular.ttf", title.h);
    SDL_Surface* surface = TTF_RenderText_Blended(roboto, m_name, white);
    SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_QueryTexture(message, NULL, NULL, &title.w, &title.h);
    SDL_RenderCopy(m_renderer, message, NULL, &title);

    SDL_RenderPresent(m_renderer);*/
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
}

void Widget::setCallBackCode(int error) {
    m_callback = error;
}

int Widget::getCallBackCode() {
    return m_callback;
}

bool Widget::getFocus(int x, int y) {
    return (x >= m_widget.x) && (x <= m_widget.x + m_widget.w) && (y >= m_widget.y) && (y <= m_widget.y + m_widget.h + m_height);
}

void Widget::eventWatch(SDL_Event event) {
    int x = 0, y = 0;
    setCallBackCode(0);
//    checkTitle(event.button.x, event.button.y);
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        setMouseX(event.button.x);
        setMouseY(event.button.y);
    } else if (event.type == SDL_MOUSEMOTION) {
        if (m_movable) {
            x = event.motion.x;
            y = event.motion.y;
            if (SDL_GetMouseState(0, 0) & SDL_BUTTON_LMASK) {
                updateWidgetPosition(x, y);
                //SDL_CaptureMouse(SDL_TRUE);
                setCallBackCode(1);
            }
        }
        if (!(SDL_GetMouseState(0, 0) & SDL_BUTTON_LMASK))
            SDL_CaptureMouse(SDL_FALSE);
    }
    std::cout << getName() << std::endl;
}