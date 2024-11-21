#include "Inclusion.hpp"
using namespace std;

Livello_Bonus::Livello_Bonus():Livello(){}

void Livello_Bonus::Bonus_InBox(blist bl){
    int i = AWARD_UBORDER + 2; 
    int j = AWARD_LBORDER + 2; 
    while(bl!=NULL && i <= AWARD_BBORDER){
        bl->axisY = i;
        bl->axisX = j;
        j+=2;
        if(j>AWARD_RBORDER-2) {
            j = AWARD_LBORDER + 2;
            i+=2;
        }
        bl = bl->next;    
    }
}

void Livello_Bonus::NewLevel(Personaggio p,Livello* l, Bonus* b){
    l->NewLevel(p);
    WINDOW* w = l->Current_Win()->current_level;
    l->Current_Win()->isBonus = true;
    b->SetBnsQuantity(p.punti()/400);
    b->Generate_Bns_List();
    b->ResetBnsQuantity();
    blist bl = b->List_Curr_Bns();
    Bonus_InBox(bl);
    b->Add_Bns_To_Level(w);
    mvwhline(w,AWARD_UBORDER-1,AWARD_LBORDER-1,0,AWARD_RBORDER-AWARD_LBORDER+2);
    waddch(w,acs_map[(char)ACS_BSSB]);
    mvwhline(w,AWARD_BBORDER+1,AWARD_LBORDER-1,0,AWARD_RBORDER-AWARD_LBORDER+2);
    waddch(w,acs_map[(char)ACS_SSBB]);
    mvwvline(w,AWARD_UBORDER-1,AWARD_RBORDER+1,0,AWARD_BBORDER-AWARD_UBORDER+2);
    waddch(w,acs_map[(char)ACS_BBSS]);
    mvwvline(w,AWARD_UBORDER,AWARD_LBORDER-1,0,AWARD_BBORDER-AWARD_UBORDER+1);
    mvwaddch(w,AWARD_BBORDER+1,AWARD_RBORDER+1,acs_map[(char)ACS_SBBS]);
    wmove(w,AWARD_UBORDER-1,(AWARD_RBORDER+AWARD_LBORDER-2)/2);
    wprintw(w,"    ");
    wmove(w,AWARD_BBORDER+1,(AWARD_RBORDER+AWARD_LBORDER-2)/2);
    wprintw(w,"    ");
    wrefresh(w);
}

void Livello_Bonus::TurnOffNem(Nemico n){
    ptrNemici nl = n.listNemLivCurr();
    while(nl!=NULL){
        nl->ucciso = true;
        nl = nl->next;
    }
}

void Livello_Bonus::TurnOnNem(Nemico n){
    ptrNemici nl = n.listNemLivCurr();
    while(nl!=NULL){
        if(nl->vita > 0) nl->ucciso = false;
        nl = nl->next;
    }
}
