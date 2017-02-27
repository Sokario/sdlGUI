//
// Created by logout on 15/02/17.
//
#include "../include/button.h"

Button::Button() {
    m_computer = NULL;
    m_window = NULL;
    m_renderer = NULL;
    setName("NULL");
    setHeight(0);
}

Button::Button(SDL_DisplayMode* computer, SDL_Window* window, SDL_Renderer* renderer, const char *name) {
    Button();
    assignDisplayMode(computer);
    assignWindow(window);
    assignRenderer(renderer);
    setName(name);
    setHeight(m_computer->h/64);
}

void Button::assignDisplayMode(SDL_DisplayMode* computer) {
    m_computer = computer;
}

SDL_DisplayMode* Button::getDisplayMode() {
    return m_computer;
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
