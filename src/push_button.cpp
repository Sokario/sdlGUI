//
// Created by logout on 27/02/17.
//
#include "../include/push_button.h"

PushButton::PushButton() {
    Button();
}

PushButton::PushButton(SDL_DisplayMode* computer, SDL_Renderer *renderer, const char *name) {
    PushButton();
    assignDisplayMode(computer);
    assignRenderer(renderer);
    setWidth(20);
    setHeight(getDisplayMode()->h/64);
    setName(name);
}



PushButton::~PushButton() {

}