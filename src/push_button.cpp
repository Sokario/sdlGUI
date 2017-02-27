//
// Created by logout on 27/02/17.
//
#include "../include/push_button.h"

PushButton::PushButton() {
    Button();
}

PushButton::PushButton(SDL_DisplayMode* computer, SDL_Window *window, SDL_Renderer *renderer, const char *name) {
    PushButton();
    assignDisplayMode(computer);
    assignWindow(window);
    assignRenderer(renderer);
    setName(name);
    setHeight(getDisplayMode()->h/64);
}

PushButton::~PushButton() {

}