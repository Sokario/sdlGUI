//
// Created by logout on 15/02/17.
//
#include "../include/button.h"

Button::Button(SDL_DisplayMode parent, SDL_Window* window, SDL_Renderer* renderer, const char *name) {
    m_parent = parent;
    m_window = window;
    m_renderer = renderer;
    setName(name);
    setHeight(m_parent.h/64);
}

void Button::setName(const char *name) {
    m_name = name;
}

const char* Button::getName() {
    return m_name;
}

void Button::setHeight(int height) {
    m_height = height;
}

int Button::getHeight() {
    return m_height;
}

Button::~Button() {

}
