//
// Created by logout on 27/02/17.
//
#ifndef SDLGUI_PUSH_BUTTON_H
#define SDLGUI_PUSH_BUTTON_H

#include "GUI_header.h"
#include "button.h"

class PushButton :public Button {

public:
    PushButton();
    PushButton(SDL_DisplayMode* computer, SDL_Renderer* renderer, const char* name);

    ~PushButton();

private:

};

#endif //SDLGUI_PUSH_BUTTON_H
