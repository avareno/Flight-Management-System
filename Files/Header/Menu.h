//
// Created by avareno on 12/26/23.
//

#ifndef PROJETO_AED_MENU_H
#define PROJETO_AED_MENU_H


class Menu {
public:
    int getOption() const;

    void setOption(int option);

    Menu();
private:
    int option;

};


#endif //PROJETO_AED_MENU_H
