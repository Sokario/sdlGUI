//
// Created by logout on 07/02/17.
//
#include <SDL_video.h>
#include "../include/screen.h"
#include "../include/sdlGUI.h"

Screen::Screen(const char* name, int width, int height) {
    setWidth(width);
    setHeight(height);
    setName(name);
    m_quitButton = false;
    m_computer = new SDL_DisplayMode;
    if (SDL_WasInit(SDL_SUBSYTEM_MASK)) {
        SDL_GetDesktopDisplayMode(0, m_computer);
        m_pitch = m_computer->w/512;
        setTitleRect(m_width, m_computer->h/32, 0, 0);
        setQuitRect(m_title.h/2 + m_title.h/8, m_title.h/2 + m_title.h/8, m_width - (m_title.h/2 + m_title.h/8) - (m_title.h - (m_title.h/2 + m_title.h/8))/2, (m_title.h - (m_title.h/2 + m_title.h/8))/2);
        m_window = SDL_CreateWindow(m_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(m_renderer, 40, 40, 40, 255);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);

        //m_surfaceBack = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
        //m_textureBack = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
        m_surfaceBack = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
        m_textureBack = SDL_CreateTextureFromSurface(m_renderer, m_surfaceBack);
        m_surfaceQuit = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
        m_textureQuit = SDL_CreateTextureFromSurface(m_renderer, m_surfaceQuit);
        m_surfaceName = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0, 0, 0, 0);
        m_textureName = SDL_CreateTextureFromSurface(m_renderer, m_surfaceName);
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

void Screen::setQuitRect(int width, int height, int posX, int posY) {
    m_quit.w = width;
    m_quit.h = height;
    m_quit.x = posX;
    m_quit.y = posY;
}

SDL_Rect* Screen::getQuitRect() {
    return &m_quit;
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
    SDL_RenderClear(m_renderer);

    for (int it = 0; it < m_widget.size(); it++) {
        m_widget[it]->drawDisplay();
    }

    SDL_UpdateTexture(m_textureBack, NULL, m_surfaceBack->pixels, m_surfaceBack->pitch);
    SDL_RenderCopy(m_renderer, m_textureBack, NULL, NULL);
    SDL_RenderCopy(m_renderer, m_textureQuit, NULL, &m_rectQuit);
    SDL_RenderCopy(m_renderer, m_textureName, NULL, &m_rectName);

    SDL_RenderPresent(m_renderer);
}

void Screen::updateDisplay() {
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_renderer, 40, 40, 40, 255);
    SDL_RenderClear(m_renderer);

    SDL_FillRect(m_surfaceBack, NULL, SDL_MapRGBA(m_surfaceBack->format, 0, 0, 0, 0));

    Uint8 value = 0;
    SDL_Rect m_shader;
    for (int i = m_pitch; i >= 0; i--) {
        m_shader.w = m_title.w;
        m_shader.h = i;
        m_shader.x = 0;
        m_shader.y = m_title.h;
        value += 120 / m_pitch;
        SDL_FillRect(m_surfaceBack, &m_shader, SDL_MapRGBA(m_surfaceBack->format, 40, 40, 40, value));
    }

    SDL_FillRect(m_surfaceBack, &m_title, SDL_MapRGBA(m_surfaceBack->format, 255, 255, 255, 255));
    if (m_quitButton)
        SDL_FillRect(m_surfaceBack, &m_quit, SDL_MapRGBA(m_surfaceBack->format, 255, 0, 0, 255));

    m_rectQuit.w = m_quit.w / 2;
    m_rectQuit.h = m_quit.h / 2;
    m_rectQuit.x = m_quit.x + m_quit.w / 2 - m_rectQuit.w / 2;
    m_rectQuit.y = m_quit.y + m_quit.h / 2 - m_rectQuit.h / 2;
    SDL_FreeSurface(m_surfaceQuit);
    m_surfaceQuit = SDL_LoadBMP("../../resources/icon/close.bmp");
    SDL_SetColorKey(m_surfaceQuit, SDL_TRUE, SDL_MapRGBA(m_surfaceQuit->format, 0, 255, 0, 0));

    if (m_quitButton) {
        for (int x = 0; x < m_surfaceQuit->w; x++) {
            for (int y = 0; y < m_surfaceQuit->h; y++) {
                Uint8* target = (Uint8*) m_surfaceQuit->pixels + y*m_surfaceQuit->pitch + x*m_surfaceQuit->format->BytesPerPixel;
                Uint32* pixel = (Uint32*) target;
                Uint8 r, g, b;
                SDL_GetRGB(*pixel, m_surfaceQuit->format, &r, &g, &b);
                if ((r <= 0 ) && (g <= 0 ) && (b <= 0 )) {
                    *pixel = SDL_MapRGBA(m_surfaceQuit->format, 255, 255, 255, 255);
                }
            }
        }
    }

    SDL_DestroyTexture(m_textureQuit);
    m_textureQuit = SDL_CreateTextureFromSurface(m_renderer, m_surfaceQuit);

    drawDisplay();
    for (int it = 0; it < m_widget.size(); it++) {
        m_widget[it]->updateDisplay();
    }

    updateRenderer();
}

/*
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
}*/

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

SDL_Renderer* Screen::getRenderer() {
    return m_renderer;
}

void Screen::isOnQuit(int x, int y) {
    m_quitButton = (x >= m_quit.x) && (x <= m_quit.x + m_quit.w) && (y >= m_quit.y) && (y <= m_quit.y + m_quit.h);
}

void Screen::callBackEvent(Widget *widget) {
//    std::cout << "Widget: " << widget->getName() << " | Error code: " << widget->getErrorCode() << std::endl;
    switch(widget->getCallBackCode()){
        case 0:
            SDL_Log("Nothing code from %s", widget->getName());
            break;
        case 1:
            SDL_Log("Display code from %s", widget->getName());
            break;

        default:
            SDL_Log("Error Unknown code from %s", widget->getName());
            break;
    }
}

void Screen::computeEvent(SDL_Event event) {
    if (event.window.windowID == getWindowId()) {
        isOnQuit(event.button.x, event.button.y);
        Widget* widget;
        int indice = 0, cpt = 0;
        for (int it = 0; it < m_widget.size(); it++) {
            if (m_widget[it]->getFocus(event.button.x, event.button.y)) {
                if (cpt == 0) {
                    widget = m_widget[it];
                    indice = it;
                } else if (!widget->isMoving()) {
                    widget = m_widget[it];
                    indice = it;
                }
                cpt++;
            }
        }

        if (cpt > 0) {
            widget->eventWatch(event);
            callBackEvent(widget);
            m_widget.erase(m_widget.begin() + indice);
            m_widget.push_back(widget);
        }

        if ((event.button.button == SDL_BUTTON_LEFT) && (event.button.state == SDL_PRESSED) && m_quitButton) {
            SDL_Event sdl_event;
            sdl_event.type = SDL_KEYDOWN;
            sdl_event.key.keysym.sym = SDLK_ESCAPE;
            SDL_PushEvent(&sdl_event);
        }
    }
}

Widget* Screen::addWidget(const char* name, int posX, int posY) {
    int w = 0, h = 0, x = 0, y = 0;
    SDL_GetWindowSize(m_window, &w, &h);
    SDL_GetWindowPosition(m_window, &x, &y);
    Widget* widget = new Widget(name, m_computer, m_renderer, x + w/2 - (m_width/4 - m_width/16)/2 + posX, y + h/2 - m_height/16 + posY, (int) m_widget.size());
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