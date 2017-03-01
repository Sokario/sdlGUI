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
    setOffsetSection(0);
    setWidth(section->w);
    setHeight(0);
}

void Section::assignDisplayMode(SDL_DisplayMode* computer) {
    m_computer = computer;
}

SDL_DisplayMode* Section::getDisplayMode() {
    return m_computer;
}

void Section::assignRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

SDL_Renderer* Section::getRenderer() {
    return m_renderer;
}

void Section::setId(int id) {
    m_id = id;
}

int Section::getId() {
    return m_id;
}

Button* Section::addButton(const char* name) {
    Button* button = new Button(m_computer, m_renderer, name);
    m_button.emplace((int) m_button.size(), button);
    return button;
}

void Section::delButton() {

}

PushButton* Section::addPushButton(const char* name) {
    PushButton* button = new PushButton(m_computer, m_renderer, name);
    m_button.emplace((int) m_button.size(), button);
    return button;
}

void Section::delPushButton() {

}

void Section::setWidth(int width) {
    m_width = width;
    m_section.w = m_width;
}

int Section::getWidth() {
    return m_width;
}

void Section::setHeight(int height) {
    m_height = height;
}

int Section::getHeight() {
    return m_height;
}

void Section::setName(const char* name) {
    m_name = name;
}

const char* Section::getName() {
    return m_name;
}

void Section::setOffsetWindow(int offset) {
    m_offsetWindow = offset;
}

int Section::getOffsetWindow() {
    return m_offsetWindow;
}

void Section::setOffsetSection(int offset) {
    m_offsetSection = offset;
}

int Section::getOffsetSection() {
    return m_offsetSection;
}

void Section::setSectionRect(SDL_Rect *section) {
    m_section.w = m_width;
    m_section.h = m_height;
    m_section.x = section->x;
    m_section.y = m_offsetWindow;
}

SDL_Rect* Section::getSectionRect() {
    return &m_section;
}

void Section::updateSectionRect() {
    m_section.h = m_height;
    m_section.y = m_offsetWindow + m_offsetSection;
}

void Section::drawDisplay(SDL_Surface *background) {
    updateDisplay();
    SDL_FillRect(background, &m_section, SDL_MapRGBA(background->format, 0, 100*m_id, 0, 255));
}

void Section::updateDisplay() {
    int height = 0;
    for (int it = 0; it < m_button.size(); it++) {
        height += m_button[it]->getHeight();
    }
    setHeight(height);
    updateSectionRect();
}

Section::~Section() {

}