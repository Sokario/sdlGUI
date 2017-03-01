//
// Created by logout on 09/02/17.
//
#ifndef SDLGUI_SECTION_H
#define SDLGUI_SECTION_H

#include <unordered_map>
#include "GUI_header.h"
#include "button.h"
#include "push_button.h"

class Section {

public:
    Section(SDL_DisplayMode* computer, SDL_Renderer* renderer, SDL_Rect* section, const char* name, int id);
    void setName(const char* name);
    const char* getName();
    void setId(int id);
    int getId();
    void setHeight(int height);
    int getHeight();
    void setOffset(int offset);
    int getOffset();
    void setSectionRect(SDL_Rect* section);
    SDL_Rect* getSectionRect();
    Button* addButton(const char* name);
    void delButton();
    PushButton* addPushButton(const char* name);
    void delPushButton();

    void drawDisplay(SDL_Surface* background);
    void updateDisplay();
    ~Section();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    const char* m_name;
    int m_id;
    int m_height;
    std::unordered_map <int, Button*> m_button;
    int m_offsetWindow;
    int m_offsetSection;
    SDL_Rect m_section;
    SDL_DisplayMode* m_computer;
};

#endif //SDLGUI_SECTION_H
