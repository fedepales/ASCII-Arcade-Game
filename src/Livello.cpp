#include "Inclusion.hpp"
using namespace std;

Livello::Livello(){
    initscr();
    curs_set(0);
    noecho();
    getmaxyx(stdscr,height,width);
    level = 1;
    list = NULL;
}

void Livello::ListLevel(WINDOW* w){
    if(level==1){
        list = new Level_List();
        list->prev = NULL;
        list->next = NULL;
        list->current_level = w;
    }
    else{
        ptlist h = list;
        list->next = new Level_List();
        list->next->current_level = w;
        list->next->prev = h;
        list->next->next = NULL;
        GoNext();
    }
    keypad(list->current_level,true);
}

void Livello::GoNext(){
    WINDOW* R = newwin(height-4,width-8,2,4);
    list = list->next;
    overwrite(list->current_level,R);
    wrefresh(R);
}

void Livello::GoBack(){
    WINDOW* R = newwin(height-4,width-8,2,4);
    list = list->prev;
    overwrite(list->current_level,R);
    wrefresh(R);
}

void Livello::AddCharacter(chtype c,int old_y, int old_x, int y, int x){
    if(old_y!=0 && old_x!=0) mvwaddch(list->current_level,old_y,old_x,' ');
    mvwaddch(list->current_level,y,x,c);
    wrefresh(list->current_level);
} 

void Livello::NewLevel(Personaggio p){
    int rows,cols;
    WINDOW* w = newwin(rows = height-4,cols = width-8,2,4);
    nodelay(w,true);
    ListLevel(w); 
    Current_Win()->isBonus = false;
    wborder(w,0,0,0,0,0,0,0,0);
    mvwvline(w,1,HUDLINE,0,rows-2);
    mvwaddch(w,0,HUDLINE,acs_map[(char)ACS_TTEE]);
    mvwaddch(w,rows-1,HUDLINE,acs_map[(char)ACS_BTEE]);
    mvwvline(w,2,HUDLINE-3,0,rows-3);
    mvwvline(w,2,3,0,rows-3);
    mvwaddstr(w,4,HUDLINE+3,"LIVELLO ");
    wprintw(w,"%d", level);
    mvwaddstr(w,10,HUDLINE+3,"PUNTEGGIO:");
    mvwaddstr(w,16,HUDLINE+3,"VITA:");
    mvwaddstr(w,22,HUDLINE+3,"ATTACCO:");
    mvwaddstr(w,28,HUDLINE+3,"DIFESA:");
    mvwhline(w,3,4,'-',HUDLINE-7);
    Update_Pts(p);
    Update_Health(p);
    Update_Atk(p);
    Update_Def(p);
    if(level==1){
        mvwaddch(w,rows-2,HUDLINE-3,acs_map[(char)ACS_SBBS]);
        mvwhline(w,rows-2,3,0,HUDLINE-6);
        mvwaddch(w,rows-2,3,acs_map[(char)ACS_SSBB]);
    }
    else mvwhline(w,BOTTOM_BORDER+1,4,'-',HUDLINE-7);    
    level++;
}

void Livello::Setup_Level(Bonus* b, Nemico* n){
    b->Generate_Bns_List();
    b->Add_Bns_To_Level(list->current_level);
    n->PiuNemici();
    n->createListNemici();
    n->Potenzia();
    n->printListNemici(list->current_level);
    wrefresh(list->current_level);
}

void Livello::Update_Pts(Personaggio p){
    wmove(list->current_level,10,HUDLINE+14);
    wprintw(list->current_level,"%d",p.punti());
    wrefresh(list->current_level);
}

void Livello::Update_Health(Personaggio p){
    wmove(list->current_level,16,HUDLINE+9);
    wprintw(list->current_level,"%2d",p.life());
    wrefresh(list->current_level);
}

void Livello::Update_Atk(Personaggio p){
    wmove(list->current_level,22,HUDLINE+12);
    wprintw(list->current_level,"%.2f",p.atk());
    wrefresh(list->current_level);
}

void Livello::Update_Def(Personaggio p){
    wmove(list->current_level,28,HUDLINE+11);
    wprintw(list->current_level,"%.2f",p.def());
    wrefresh(list->current_level);
}

int Livello::LevelNum(){return level;}
int Livello::GetMove(){return wgetch(list->current_level);}
ptlist Livello::Current_Win(){return list;}
