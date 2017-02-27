//
// Created by logout on 15/02/17.
//
#include "../include/button.h"

Button::Button() {
    m_parent = NULL;
    m_window = NULL;
    m_renderer = NULL;
    setName("NULL");
    setHeight(0);
}

Button::Button(SDL_DisplayMode parent, SDL_Window* window, SDL_Renderer* renderer, const char *name) {
    Button();
    assignParent(parent);
    assignWindow(window);
    assignRenderer(renderer);
    setName(name);
    setHeight(m_parent.h/64);
}

void Button::assignParent(SDL_DisplayMode parent) {
    m_parent = parent;
}

SDL_DisplayMode Button::getParent() {
    return m_parent;
}

void Button::assignWindow(SDL_Window* window) {
    m_window = window;
}

SDL_Window* Button::getWindow() {
    return m_window;
}

void Button::assignRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

SDL_Renderer* Button::getRenderer() {
    return m_renderer;
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
