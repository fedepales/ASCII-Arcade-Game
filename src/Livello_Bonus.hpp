#ifndef LIVELLO_BONUS_HPP_
#define LIVELLO_BONUS_HPP_
#include "Bonus.hpp"

class Livello;
class Bonus;
class Personaggio;
class Nemico;

class Livello_Bonus:public Livello{
    private:
        void Bonus_InBox(blist);
    public:
        Livello_Bonus();
        void NewLevel(Personaggio,Livello*,Bonus*);
        void TurnOffNem(Nemico);
        void TurnOnNem(Nemico);
};
#endif