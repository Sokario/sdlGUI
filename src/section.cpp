//
// Created by logout on 09/02/17.
//
#include "../include/section.h"

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
    int height = 0;
    for (int it = 0; it < m_button.size(); it++) {
        height += m_button[it]->getHeight();
    }
    setHeight(height);
}

Section::~Section() {

}