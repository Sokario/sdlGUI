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
    Section();
    Section(SDL_DisplayMode* computer, SDL_Renderer* renderer, SDL_Rect* section, const char* name, int id);

    void assignDisplayMode(SDL_DisplayMode* computer);
    SDL_DisplayMode* getDisplayMode();
    void assignRenderer(SDL_Renderer* renderer);
    SDL_Renderer* getRenderer();
    void setId(int id);
    int getId();

    Button* addButton(const char* name);
    void delButton();
    PushButton* addPushButton(const char* name);
    void delPushButton();

    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setName(const char* name);
    const char* getName();
    void setOffsetWindow(int offset);
    int getOffsetWindow();
    void setOffsetSection(int offset);
    int getOffsetSection();

    void setSectionRect(SDL_Rect* section);
    SDL_Rect* getSectionRect();
    void updateSectionRect();
    void drawDisplay(SDL_Surface* background);
    void updateDisplay();

    ~Section();

private:
    SDL_DisplayMode* m_computer;
    SDL_Renderer* m_renderer;
    int m_id;
    std::unordered_map <int, Button*> m_button;

    int m_width;
    int m_height;
    const char* m_name;
    int m_offsetWindow;
    int m_offsetSection;

    SDL_Rect m_section;
};

#endif //SDLGUI_SECTION_H
