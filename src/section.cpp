//
// Created by logout on 09/02/17.
//
#include "../include/section.h"
#include <iostream>

Section::Section(SDL_DisplayMode* computer, SDL_Renderer* renderer, SDL_Rect* section, const char* name, int id) {
    m_computer = computer;
    m_renderer = renderer;
    m_offsetWindow = section->y + section->h;
    setName(name);
    setId(id);
    setSectionRect(section);
    setOffset(0);
    setHeight(0);
}

void Section::setName(const char* name) {
    m_name = name;
}

const char* Section::getName() {
    return m_name;
}

void Section::setId(int id) {
    m_id = id;
}

int Section::getId() {
    return m_id;
}

void Section::setHeight(int height) {
    m_height = height;
    m_section.h = m_height;
}

int Section::getHeight() {
    return m_height;
}

void Section::setOffset(int offset) {
    m_offsetSection = offset;
    m_section.y = m_offsetWindow + m_offsetSection;
}

int Section::getOffset() {
    return m_offsetSection;
}

void Section::setSectionRect(SDL_Rect *section) {
    m_section.w = section->w;
    m_section.h = 0;
    m_section.x = section->x;
    m_section.y = m_offsetWindow;
}

SDL_Rect* Section::getSectionRect() {
    return &m_section;
}

Button* Section::addButton(const char* name) {
    Button* button = new Button(m_computer, m_window, m_renderer, name);
    m_button.emplace((int) m_button.size(), button);
    return button;
}

void Section::delButton() {

}

PushButton* Section::addPushButton(const char* name) {
    PushButton* button = new PushButton(m_computer, m_window, m_renderer, name);
    m_button.emplace((int) m_button.size(), button);
    return button;
}

void Section::delPushButton() {

}

void Section::drawDisplay(SDL_Surface *background) {
    updateDisplay();
    SDL_FillRect(background, &m_section, SDL_MapRGBA(background->format, 255, 255, 255, 255));
}

void Section::updateDisplay() {
    updateSection();
}

void Section::drawSection() {

    updateSection();
    SDL_Surface* windowSurface;
    windowSurface = SDL_CreateRGBSurface(0, m_computer->w, m_computer->h, 32, 0, 0, 0, 0);
    SDL_FillRect(windowSurface, &m_section, SDL_MapRGBA(windowSurface->format, 20, 80, 160, 255));
    m_sectionTitle = SDL_CreateTextureFromSurface(m_renderer, windowSurface);

//    SDL_Surface* surface;
//    SDL_Color white = {0, 0, 0, 0};
//    m_rectName.w = m_section.w/64;
//    m_rectName.h = m_section.h - m_section.h/4;
//    m_rectName.x = m_section.x + m_rectName.w;
//    m_rectName.y = m_section.y;

//    TTF_Font* roboto = TTF_OpenFont("../../resources/Roboto-Regular.ttf", m_rectName.h);
//    surface = TTF_RenderText_Blended(roboto, m_name, white);
//    m_sectionName = SDL_CreateTextureFromSurface(m_renderer, surface);
//    SDL_QueryTexture(m_sectionName, NULL, NULL, &m_rectName.w, &m_rectName.h);
    SDL_RenderCopy(m_renderer, m_sectionTitle, NULL, NULL);
//    SDL_RenderCopy(m_renderer, m_sectionName, NULL, &m_rectName);
    SDL_FreeSurface(windowSurface);
    SDL_DestroyTexture(m_sectionTitle);

//    SDL_RenderPresent(m_renderer);

/*    updateSection();
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &m_section);

    SDL_Rect section;
    section.w = m_section.w/64;
    section.h = m_section.h - m_section.h/4;
    section.x = m_section.x + section.w;
    section.y = m_section.y;

    SDL_Color black = {0, 0, 0, 0};
    TTF_Font* roboto = TTF_OpenFont("../../resources/Roboto-Regular.ttf", section.h);
    SDL_Surface* surface = TTF_RenderText_Blended(roboto, m_name, black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_QueryTexture(message, NULL, NULL, &section.w, &section.h);
    SDL_RenderCopy(m_renderer, message, NULL, &section);

    SDL_RenderPresent(m_renderer);*/
}

void Section::updateSectionPosition(int x, int y) {
    m_section.w = m_section.w;
    m_section.h = m_section.h;
    m_section.x = m_section.x + x;
    m_section.y = m_section.y + y;
}

void Section::updateRenderer() {

}

void Section::updateSection() {
    int height = 0;
    for (int it = 0; it < m_button.size(); it++) {
        height += m_button[it]->getHeight();
    }
    setHeight(height);
}

Section::~Section() {

}