#ifndef LIVELLO_HPP_
#define LIVELLO_HPP_

class Livello_Bonus;
class Bonus;
class Personaggio;
class Nemico;

struct Level_List{
    bool isBonus;
    WINDOW* current_level;
    Level_List* next;
    Level_List* prev;
};
typedef Level_List* ptlist;

class Livello{
    private:
        ptlist list;
    protected:
        int height;
        int width;
        int level;
        void ListLevel(WINDOW*);
    public:
        Livello();
        void GoNext();
        void GoBack();
        void AddCharacter(chtype,int,int,int,int);
        void NewLevel(Personaggio);
        void Update_Pts(Personaggio);
        void Update_Health(Personaggio);
        void Update_Atk(Personaggio);
        void Update_Def(Personaggio);
        void Setup_Level(Bonus*,Nemico*);
        int LevelNum();
        int GetMove();
        ptlist Current_Win();
};

#endif 