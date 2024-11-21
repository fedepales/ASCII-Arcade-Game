#include "Inclusion.hpp"
using namespace std;

//BONUS --> 0: VITA, 1: DIFESA, 2: ATTACCO, 3: PUNTEGGIO

Bonus::Bonus(){
    srand(time(NULL));
    bns_quantity = (RIGHT_BORDER/12);
    lv_bns_list = NULL;
    level = 1;
}

void Bonus::Generate_Bns_List(){
    blist bns_list = new bonus_item(); 
    blist head = bns_list;
    int r;
    while(bns_quantity>1){ 
        r = rand()%8;   
        bns_list->axisY = rand()%(BONUS_BBORDER-BONUS_UBORDER+1) + BONUS_UBORDER;
        bns_list->axisX = rand()%(BONUS_RBORDER-BONUS_LBORDER+1) + BONUS_LBORDER;
        bns_list->item = r;
        bns_list->picked = false;
        bns_list->next = new bonus_item();
        bns_list = bns_list->next;
        bns_quantity--;
    }
    r = rand()%8;
    bns_list->axisY = rand()%(BONUS_BBORDER-BONUS_UBORDER+1) + BONUS_UBORDER;
    bns_list->axisX = rand()%(BONUS_RBORDER-BONUS_LBORDER+1) + BONUS_LBORDER;
    bns_list->item = r;
    bns_list->picked = false;
    bns_list->next = NULL;
    bns_quantity = (RIGHT_BORDER/15);
    bns_list = head;
    List_Bonus(bns_list);
}

void Bonus::Is_Picked(Personaggio *p){
    blist head = lv_bns_list->bns_roaster;
    while(lv_bns_list->bns_roaster!=NULL){
        if((lv_bns_list->bns_roaster->axisY == p->coordinata_y()) && 
           (lv_bns_list->bns_roaster->axisX == p->coordinata_x()) && !lv_bns_list->bns_roaster->picked){
            lv_bns_list->bns_roaster->picked = true;
            Buff(p);
            lv_bns_list->bns_roaster = head;
        }
        lv_bns_list->bns_roaster = lv_bns_list->bns_roaster->next;
    }
    lv_bns_list->bns_roaster = head;
}

void Bonus::Buff(Personaggio* p){ 
    switch(lv_bns_list->bns_roaster->item){
        case 0: p->aggiorna_vita(15);
        break;
        case 1: p->aggiorna_def();
        break;
        case 2: p->aggiorna_atk();
        break;
        default: p->aggiorna_punteggio();
    }   
}

void Bonus::Add_Bns(WINDOW* w,blist bl){
    wmove(w,bl->axisY,bl->axisX);
    switch(bl->item){
        case 0: waddch(w,43);
        break;
        case 1: waddch(w,acs_map[45]);
        break;
        case 2: waddch(w,164);
        break;
        default: waddch(w,165);
    }
}

void Bonus::Add_Bns_To_Level(WINDOW* w){
    blist head = lv_bns_list->bns_roaster;
    while(lv_bns_list->bns_roaster!=NULL){
        Add_Bns(w,lv_bns_list->bns_roaster);
        lv_bns_list->bns_roaster = lv_bns_list->bns_roaster->next;
    }
    lv_bns_list->bns_roaster = head;
}

void Bonus::List_Bonus(blist l){
    if(level==1){
        lv_bns_list = new level_bns();
        lv_bns_list->bns_roaster = new bonus_item();
        lv_bns_list->bns_roaster = l;
        lv_bns_list->next = NULL;
        lv_bns_list->prev = NULL;
    }
    else{
        lv_blist h = lv_bns_list;
        lv_bns_list->next = new level_bns();
        lv_bns_list->next->bns_roaster = new bonus_item();
        lv_bns_list->next->bns_roaster = l;
        lv_bns_list->next->next = NULL;
        lv_bns_list->next->prev = h;
        lv_bns_list = lv_bns_list->next;
    }
    level++;
}

void Bonus::SetBnsQuantity(int bq){
    bns_quantity = bq;
    if(bns_quantity>72) bns_quantity = 72;
}
void Bonus::ResetBnsQuantity(){bns_quantity = RIGHT_BORDER/12;}
void Bonus::Next_Bns_List(){lv_bns_list = lv_bns_list->next;}
void Bonus::Prev_Bns_List(){lv_bns_list = lv_bns_list->prev;}
blist Bonus::List_Curr_Bns(){return lv_bns_list->bns_roaster;}
