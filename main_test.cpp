//
// Created by logout on 07/02/17.
//
#include <SDL_video.h>
#include "include/sdlGUI.h"

int main() {

    SDL_Event event;
    bool done = false;

    if (SDL_Init(SDL_SUBSYTEM_MASK) < 0) {
        SDL_Log("Init SDL error!");
        return -1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Init TTF error!");
        return -1;
    }

    SDL_DisplayMode current;
    if (SDL_GetDesktopDisplayMode(0, &current)) {
        SDL_Log("Desktop Display error!");
        return -1;
    }

    Screen window("Main Window", current.w, current.h);

    Widget* widget0 = window.addWidget("Widget 0");
    Section* section0_1 = widget0->addSection("Section 1");
    section0_1->addButton("Button 1");
    section0_1->addButton("Button 2");
    section0_1->addButton("Button 3");

    Widget* widget1 = window.addWidget("Widget 1", -window.getWidth()/4, -window.getHeight()/4);
    widget1->setName("Modification 1");
    Section* section1_1 = widget1->addSection("Section 1");
    Section* section1_2 = widget1->addSection("Section 2");
    Section* section1_3 = widget1->addSection("Section 3");
    section1_1->addButton("Button 1");
    section1_1->addButton("Button 2");
    section1_1->addButton("Button 3");
    section1_2->addButton("Button 1");
    section1_2->addButton("Button 2");
    section1_3->addButton("Button 1");
    section1_3->addButton("Button 2");
    section1_3->addButton("Button 3");
    section1_3->addButton("Button 4");
    section1_3->addButton("Button 5");

    Widget* widget2 = window.addWidget("Widget 2", window.getWidth()/4, window.getHeight()/4);

    widget0->updateWidget();
    widget1->updateWidget();
    widget2->updateWidget();

//    std::cout << widget1_1->getTitleRect()->h << std::endl;

//    SDL_EventState(SDL_WINDOWEVENT, SDL_IGNORE);
//    SDL_SetEventFilter(filterEvent, NULL);

    int cpt = 0;
    while (!done) {
        while (SDL_PollEvent(&event)) {

            //window.computeEvent(event);
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    printf("quit\n");
                    done = true;
                }
            }
        }
        //std::cout << "Ittération: " << cpt++ << std::endl;
        window.updateDisplay();
        SDL_Delay(1);
    }
    SDL_Quit();
}