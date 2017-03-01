//
// Created by logout on 15/02/17.
//
#include "../include/button.h"

Button::Button() {
    m_computer = NULL;
    m_renderer = NULL;
    setWidth(0);
    setHeight(0);
    setName("NULL");
}

Button::Button(SDL_DisplayMode* computer, SDL_Renderer* renderer, const char *name) {
    Button();
    assignDisplayMode(computer);
    assignRenderer(renderer);
    setWidth(20);
    setHeight(10);
    setName(name);
}

void Button::assignDisplayMode(SDL_DisplayMode* computer) {
    m_computer = computer;
}

SDL_DisplayMode* Button::getDisplayMode() {
    return m_computer;
}

void Button::assignRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

SDL_Renderer* Button::getRenderer() {
    return m_renderer;
}

void Button::setWidth(int width) {
    m_width = width;
}

int Button::getWidth() {
    return m_width;
}

void Button::setHeight(int height) {
    m_height = height;
}

int Button::getHeight() {
    return m_height;
}

void Button::setName(const char *name) {
    m_name = name;
}

const char* Button::getName() {
    return m_name;
}

Button::~Button() {

}
