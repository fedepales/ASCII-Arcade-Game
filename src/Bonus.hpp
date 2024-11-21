#ifndef BONUS_HPP_
#define BONUS_HPP_

class Livello;
class Livello_Bonus;
class Personaggio;
class Nemico;

struct bonus_item{
        int item;
        int axisY;
        int axisX;
        bool picked;
        bonus_item* next;
};
typedef bonus_item* blist;
struct level_bns{
    level_bns* prev;
    level_bns* next;
    blist bns_roaster;
};
typedef level_bns* lv_blist;

class Bonus{ 
    private:
        void List_Bonus(blist);   
    protected:
        int bns_quantity;
        int level;
        lv_blist lv_bns_list;
    public:
        Bonus();
        void Generate_Bns_List();
        void Add_Bns(WINDOW*,blist);
        void Add_Bns_To_Level(WINDOW*);
        void Is_Picked(Personaggio*);
        void Next_Bns_List();
        void Prev_Bns_List();
        void Buff(Personaggio*);
        void SetBnsQuantity(int);
        void ResetBnsQuantity();
        blist List_Curr_Bns();
};

#endif