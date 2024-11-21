#include "Inclusion.hpp"
using namespace std;
Nemico::Nemico() {
    srand(time(NULL));
    n_nemici=2;
    listNemLiv=NULL;
    nemLevel= 1;
}

void Nemico::createListNemici(){//crea la lista di nemici
    ptrNemici listNem = new nemici();
    ptrNemici head = listNem;
    int r,n;
    n=n_nemici;
    while (n>0){
        r = (rand()%3) + 'A'; 
        listNem->tipo = r;
        switch (listNem->tipo)
        {
        case 'A'://nemico che non si muove ma spara solo
            listNem->danno = 1;
            listNem->attacco = 0;
            listNem->difesa = 2;
            listNem->vita = 8;
            listNem->gittata=max(BONUS_BBORDER, BONUS_RBORDER);
            break;
        case 'B'://nemico che si muove ma non spara
            listNem->danno = 20;
            listNem->attacco = 1;
            listNem->difesa = 1;
            listNem->vita = 6;
            listNem->gittata=0;
            break;
        case 'C'://nemico che si muove e spara
            listNem->danno = 3;
            listNem->attacco = 1;
            listNem->difesa = 1;
            listNem->vita = 10;
            listNem->gittata=BONUS_RBORDER/7;
        }
        listNem->ucciso = false;
        listNem->yCoord = rand()%(BONUS_BBORDER-BONUS_UBORDER+1) + BONUS_UBORDER;
        listNem->xCoord = rand()%(BONUS_RBORDER-BONUS_LBORDER+1) + BONUS_LBORDER;
        listNem->sparoCoordX=listNem->xCoord;
        listNem->sparoCoordY=listNem->yCoord;
        listNem->next = new nemici();
        listNem = listNem->next;
        n--;
    }
    r = (rand()%3) + 'A'; 
    listNem->tipo = r;
    switch(listNem->tipo){
        case 'A'://nemico che non si muove ma spara solo fa sempre 1 di danno
            listNem->danno = 1;
            listNem->attacco = 0;
            listNem->difesa = 2;
            listNem->vita = 8;
            listNem->gittata=max(BONUS_BBORDER, BONUS_RBORDER);
            break;
        case 'B'://nemico che si muove ma non spara
            listNem->danno = 20;
            listNem->attacco = 1;
            listNem->difesa = 1;
            listNem->vita = 6;
            listNem->gittata=0;
            break;
        case 'C'://nemico che si muove e spara
            listNem->danno = 3;
            listNem->attacco = 1;
            listNem->difesa = 1;
            listNem->vita = 10;
            listNem->gittata=BONUS_RBORDER/7;
    }
    listNem->ucciso = false;
    listNem->yCoord = rand()%(BONUS_BBORDER-BONUS_UBORDER+1) + BONUS_UBORDER;
    listNem->xCoord = rand()%(BONUS_RBORDER-BONUS_LBORDER+1) + BONUS_LBORDER;
    listNem->sparoCoordX=listNem->xCoord;
    listNem->sparoCoordY=listNem->yCoord;
    listNem->next = NULL;
    listNem = head;
    addListToLevel(listNem);
}


void Nemico::printListNemici(WINDOW* win){//stampa la lista di nemici
    ptrNemici head = listNemLiv->currentNem;
    while(head!=NULL){
        if(head->ucciso==false){
            mvwaddch(win, head->yCoord,head->xCoord, head->tipo);
        }
        head = head->next;
    }
}
void Nemico::addListToLevel(ptrNemici n){//aggiunge la lista di nemici al livello
    if(nemLevel==1){//caso in cui sono nel primo livello, quindi la lista è vuota
        listNemLiv= new nemiciLevel();
        listNemLiv->currentNem= new nemici();
        listNemLiv->currentNem=n;
        listNemLiv->next=NULL;
        listNemLiv->prev=NULL;
        
    }
    else{//caso in cui la lista non è vuota
        ptrListLevel app = listNemLiv;
        listNemLiv->next = new nemiciLevel();
        listNemLiv->next->currentNem = new nemici();
        listNemLiv->next->currentNem = n;
        listNemLiv->next->prev = app;
        listNemLiv->next->next = NULL;
        listNemLiv = listNemLiv->next;
    }
    nemLevel++;
}

void Nemico::GoNextNem(){
    listNemLiv = listNemLiv->next;
}

void Nemico::GoBackNem(){
    listNemLiv = listNemLiv->prev;
}

void Nemico::moveUp(ptrNemici n){//movimento sopra
    if(n->yCoord>BONUS_UBORDER) n->yCoord=n->yCoord-1;
}

void Nemico::moveBottom(ptrNemici n){//movimento sotto
    if(n->yCoord<BONUS_BBORDER) n->yCoord=n->yCoord+1;
}

void Nemico::moveLeft(ptrNemici n){//movimento a sinistra
    if(n->xCoord>BONUS_LBORDER) n->xCoord=n->xCoord-1;
}

void Nemico::moveRight(ptrNemici n){//movimento a destra
    if(n->xCoord<BONUS_RBORDER) n->xCoord=n->xCoord+1;
}
void Nemico::moveNemC(Personaggio* p, Livello lv, Bonus b, ptrNemici nem, int count){
    int x,y;//coordinate personaggio
    bool is_inLine = false;
    x=p->coordinata_x();
    y=p->coordinata_y();
    if(abs(nem->xCoord-x)<=nem->gittata && nem->yCoord==y && nem->xCoord < x) {is_inLine=true; sparo_right(lv, b, p, nem);}
    else if(abs(nem->xCoord-x)<=nem->gittata && nem->yCoord==y && nem->xCoord > x) {is_inLine=true; sparo_left(lv, b, p, nem);}
    else if(abs(nem->yCoord-y)<=nem->gittata-BONUS_RBORDER/12 && nem->xCoord==x && nem->yCoord < y) {is_inLine=true; sparo_down(lv, b, p, nem);}
    else if(abs(nem->yCoord-y)<=nem->gittata-BONUS_RBORDER/12 && nem->xCoord==x && nem->yCoord > y) {is_inLine=true; sparo_up(lv, b, p, nem);}
    if(is_inLine) lv.AddCharacter(nem->tipo,nem->yCoord,nem->xCoord,nem->yCoord,nem->xCoord);
    else{
        int xOld, yOld, r;
        bool dxB,sxB, upB, btB, sxN, dxN, upN, btN;
        xOld=nem->xCoord;
        yOld=nem->yCoord;
        dxB=isUpBonus(b, nem->xCoord+1, nem->yCoord);//caso in cui mi sposto verso destra
        sxB=isUpBonus(b, nem->xCoord-1, nem->yCoord);//caso in cui mi sposto verso sinistra
        upB=isUpBonus(b, nem->xCoord, nem->yCoord-1);//caso in cui mi sposto verso l'alto
        btB=isUpBonus(b, nem->xCoord, nem->yCoord+1);//caso in cui mi sposto verso il basso
        dxN=isUpNem(nem->xCoord+1, nem->yCoord, count);//caso in cui mi sposto verso destra
        sxN=isUpNem(nem->xCoord-1, nem->yCoord, count);//caso in cui mi sposto verso sinistra
        upN=isUpNem(nem->xCoord, nem->yCoord-1, count);//caso in cui mi sposto verso l'alto
        btN=isUpNem(nem->xCoord, nem->yCoord+1, count);//caso in cui mi sposto verso il basso
        r=rand()%2;//genero casualmente il movimento del nemico
        if(r==0){//se r=0 muovo il nemico sull'asse x
            if(nem->xCoord<x && (nem->yCoord > y+3 || nem->yCoord < y-3)){//caso in cui il personaggio è a destra 
                if(!dxN && !dxB) moveRight(nem);
                else if(!btN && !btB) moveBottom(nem);
                else if(!upN && !upB) moveUp(nem);
                else if(!sxN && !sxB) moveLeft(nem);
            }
            else if(nem->xCoord>x && (nem->yCoord < y-3 || nem->yCoord > y+3)){//caso in cui il personaggio è a sinistra
                if(!sxN && !sxB) moveLeft(nem);//caso in cui muovendomi a sinistra non incontro ostacoli
                else if(!btN && !btB) moveBottom(nem);
                else if(!upN && !upB) moveUp(nem);
                else if(!dxN && !dxB) moveRight(nem);                               
            }
            else if(nem->xCoord==x && nem->yCoord > y+3){//caso in cui il personaggio è in alto
                if(!upN && !upB) moveUp(nem);
                else if(!dxN && !dxB) moveRight(nem);
                else if(!sxN && !sxB) moveLeft(nem);
                else if(!btN && !btB) moveBottom(nem);
            } 
            else if(nem->xCoord==x && nem->yCoord < y-3){//caso in cui il personaggio è in basso
                if(!btN && !btB) moveBottom(nem);
                else if(!dxN && !dxB) moveRight(nem);
                else if(!sxN && !sxB) moveLeft(nem);
                else if(!upN && !upB) moveUp(nem);
            } 
        }
        else{//caso in cui muovo il nemico sull'asse y
            if(nem->yCoord>y && (nem->xCoord > x+3 || nem->xCoord < x-3)){//caso in cui il personaggio si trova in alto
                if(!upN && !upB) moveUp(nem);
                else if(!sxN && !sxB) moveLeft(nem);
                else if(!dxN && !dxB) moveRight(nem);
                else if(!btN && !btB) moveBottom(nem);
            }
            else if(nem->yCoord<y && (nem->xCoord > x+3 || nem->xCoord < x-3)){//caso in cui il personaggio è in basso
                    if(!btN && !btB) moveBottom(nem);
                    else if(!sxN && !sxB) moveLeft(nem);
                    else if(!dxN && !dxB) moveRight(nem);
                    else if(!upN && !upB) moveUp(nem);
            }    
            else if(nem->yCoord==y && nem->xCoord > x+3){
                if(!sxN && !sxB) moveLeft(nem);
                else if(!upN && !upB) moveUp(nem);
                else if(!btN && !btB) moveBottom(nem);
                else if(!dxN && !dxB) moveRight(nem);
            } 
            else if(nem->yCoord==y && nem->xCoord < x-3){
                if(!dxN && !dxB) moveRight(nem);
                else if(!btN && !btB) moveBottom(nem);
                else if(!upN && !upB) moveUp(nem);
                else if(!sxN && !sxB) moveLeft(nem);
            } 
        }
        lv.AddCharacter(nem->tipo, yOld, xOld, nem->yCoord, nem->xCoord);
    }
}

void Nemico::moveNemB(Personaggio* p, Livello lv, Bonus b, ptrNemici nem, int count){
    int xOld, yOld, r;
    int x,y;//coordinate personaggio
    bool dxB, sxB, upB, btB, sxN, dxN, upN, btN;
    xOld=nem->xCoord;
    yOld=nem->yCoord;
    x=p->coordinata_x();
    y=p->coordinata_y();
    dxB=isUpBonus(b, nem->xCoord+1, nem->yCoord);//caso in cui mi sposto verso destra
    sxB=isUpBonus(b, nem->xCoord-1, nem->yCoord);//caso in cui mi sposto verso sinistra
    upB=isUpBonus(b, nem->xCoord, nem->yCoord-1);//caso in cui mi sposto verso l'alto
    btB=isUpBonus(b, nem->xCoord, nem->yCoord+1);//caso in cui mi sposto verso il basso
    dxN=isUpNem(nem->xCoord+1, nem->yCoord, count);//caso in cui mi sposto verso destra
    sxN=isUpNem(nem->xCoord-1, nem->yCoord, count);//caso in cui mi sposto verso sinistra
    upN=isUpNem(nem->xCoord, nem->yCoord-1, count);//caso in cui mi sposto verso l'alto
    btN=isUpNem(nem->xCoord, nem->yCoord+1, count);//caso in cui mi sposto verso il basso
    r=rand()%2;//genero casualmente il movimento del nemico
    if(r==0){//se r=0 muovo il nemico sull'asse x
        if((nem->xCoord==x+1||nem->xCoord==x-1) && nem->yCoord==y) {
            p->aggiorna_vita(-(nem->danno * nem->attacco/p->def()));
            nem->ucciso = true;
            lv.AddCharacter(' ',nem->yCoord,nem->xCoord,nem->yCoord,nem->xCoord);
        }
        if(nem->xCoord<x){//caso in cui il personaggio è a destra 
            if(!dxN && !dxB) moveRight(nem);//caso in cui muovendomi a destra non incontro ostacoli
            else if(!upN && !upB) moveUp(nem);//caso in cui muovendomi a sinistra non incontro ostacoli
            else if(!btN && !btB) moveBottom(nem);
            else if(!sxN && !sxB) moveLeft(nem);
            }
        else if(nem->xCoord>x){//caso in cui il personaggio è a sinistra
            if(!sxN && !sxB) moveLeft(nem); //caso in cui muovendomi a sinistra non incontro ostacoli
            else if(!upN && !upB) moveUp(nem);//caso in cui muovendomi verso l'alto non trovo ostacoli
            else if(!btN && !btB) moveBottom(nem);//caso in cui muovendomi in basso non incontro ostacoli
            else if(!dxN && !dxB) moveRight(nem);
        }
    }
    else{
        if((nem->yCoord==y+1||nem->yCoord==y-1) && nem->xCoord==x){
            p->aggiorna_vita(-(nem->danno + nem->attacco/p->def()));
            nem->ucciso = true;
            lv.AddCharacter(' ',nem->yCoord,nem->xCoord,nem->yCoord,nem->xCoord);
        }
        if(nem->yCoord>y+1){//caso in cui il personaggio si trova in alto
            if(!upN && !upB) moveUp(nem);//caso in cui muovendomi verso l'alto non trovo ostacoli
            else if(!sxN && !sxB) moveLeft(nem);//caso in cui muovendomi a sinistra non incontro ostacoli
            else if(!dxN && !dxB) moveRight(nem);//caso in cui muovendomi a destra non incontro ostacoli
            else if(!btN && !btB) moveBottom(nem);
        }
        else if(nem->yCoord<y-1){//caso in cui il personaggio si trova in basso  
            if(!btN && !btB) moveBottom(nem);//caso in cui muovendomi in basso non incontro ostacoli        
            else if(!sxN && !sxB) moveLeft(nem);//caso in cui muovendomi a sinistra non incontro ostacoli
            else if(!dxN && !dxB) moveRight(nem);//caso in cui muovendomi a destra non incontro ostacoli
            else if(!sxN && !sxB) moveLeft(nem);
        }
    }
    if(!nem->ucciso) lv.AddCharacter(nem->tipo, yOld, xOld, nem->yCoord, nem->xCoord);
}

void Nemico::moveNem(Personaggio* p, Livello lv, Bonus b){
    int x, y, count;
    ptrNemici nem=listNemLiv->currentNem;
    count=0;
    while(nem!=NULL){
        if(nem->ucciso==false){  
            switch (nem->tipo){
                case 'A'://nemico che non si muove ma spara solo
                    x=p->coordinata_x();
                    y=p->coordinata_y();
                    if(nem->xCoord<x && nem->yCoord==y && x <= BONUS_RBORDER) sparo_right(lv, b, p, nem);//caso in cui il personaggio è a destra ed è nella traiettoria del nemico
                    if(nem->xCoord>x && nem->yCoord==y && x >= BONUS_LBORDER) sparo_left(lv, b, p, nem);//caso in cui il personaggio è a sinistra ed è nella traiettoria del nemico
                    if(nem->yCoord>y && nem->xCoord==x && y >= BONUS_UBORDER) sparo_up(lv, b, p, nem);//caso in cui il personaggio è sopra ed è nella traiettoria del nemico
                    if(nem->yCoord<y && nem->xCoord==x && y <= BONUS_BBORDER) sparo_down(lv, b, p, nem);//Caso in cui il personaggio è sotto ed è nella traiettoria del nemico   
                    break;
                case 'B'://nemico che si muove ma non spara
                    moveNemB(p, lv, b, nem, count);
                    break;
                case 'C'://nemico che si muove e spara
                    moveNemC(p, lv, b, nem, count);
                    resetSparo(nem);
            } 
        }
        if(!nem->ucciso) lv.AddCharacter(nem->tipo,nem->yCoord,nem->xCoord,nem->yCoord,nem->xCoord);
        nem=nem->next;
        count++;
    }
}
void Nemico::resetSparo(ptrNemici n){
    n->sparoCoordX=n->xCoord;
    n->sparoCoordY=n->yCoord;
}
void Nemico::sparo_up(Livello lv, Bonus b, Personaggio* p, ptrNemici n){
    int git,x, y;
    bool flag;
    git=n->gittata;
    x=p->coordinata_x();
    y=p->coordinata_y();
    while(git-BONUS_RBORDER/12 > 0 && n->sparoCoordY>BONUS_UBORDER && n->sparoCoordY > y){//stampo lo sparo fino a quando non arrivo al bordo o sono arrivato alla gittata massima
        flag=isUpBonus(b, n->sparoCoordX, n->sparoCoordY-1);
        if(!flag){
            n->sparoCoordY--;
            if(n->sparoCoordY!=y) {
                lv.AddCharacter(183, n->sparoCoordY, n->sparoCoordX, n->sparoCoordY, n->sparoCoordX);
                p->clock(40000);
                lv.AddCharacter(' ',n->sparoCoordY,n->sparoCoordX,n->sparoCoordY,n->sparoCoordX);
            }
            else if (n->tipo == 'C'){p->aggiorna_vita(-(n->danno * n->attacco/p->def())); lv.AddCharacter('@',y,x,y,x);}
            else p->aggiorna_vita(-1);
            git--;
        }
        else{
            n->sparoCoordY=n->sparoCoordY-2;
            if(n->sparoCoordY!=y){
                lv.AddCharacter(183, n->sparoCoordY, n->sparoCoordX, n->sparoCoordY, n->sparoCoordX);
                p->clock(40000);
                lv.AddCharacter(' ',n->sparoCoordY,n->sparoCoordX,n->sparoCoordY,n->sparoCoordX);
            }
            else if (n->tipo == 'C'){p->aggiorna_vita(-(n->danno * n->attacco/p->def())); lv.AddCharacter('@',y,x,y,x);}
            else p->aggiorna_vita(-1);
            git-=2;
        }
    }
    resetSparo(n);
}

void Nemico::sparo_down(Livello lv, Bonus b, Personaggio* p, ptrNemici n){
    int git,x, y;
    bool flag;
    git=n->gittata;
    x=p->coordinata_x();
    y=p->coordinata_y();
    while(git-BONUS_RBORDER/12 > 0 && n->sparoCoordY<BONUS_BBORDER && n->sparoCoordY<y){//stampo lo sparo fino a quando non arrivo al bordo o sono arrivato alla gittata massima
        flag=isUpBonus(b, n->sparoCoordX, n->sparoCoordY+1);
            if(!flag){
                n->sparoCoordY++;
                if(n->sparoCoordY!=y){
                    lv.AddCharacter(183, n->sparoCoordY, n->sparoCoordX, n->sparoCoordY, n->sparoCoordX);
                    p->clock(40000);
                    lv.AddCharacter(' ',n->sparoCoordY,n->sparoCoordX,n->sparoCoordY,n->sparoCoordX);
                } 
                else if (n->tipo == 'C'){p->aggiorna_vita(-(n->danno * n->attacco/p->def())); lv.AddCharacter('@',y,x,y,x);}
                else p->aggiorna_vita(-1);
                git--; 
            }
            else{
                n->sparoCoordY+=2;
                if(n->sparoCoordY!=y){
                    lv.AddCharacter(183, n->sparoCoordY, n->sparoCoordX, n->sparoCoordY, n->sparoCoordX);
                    p->clock(40000);
                    lv.AddCharacter(' ',n->sparoCoordY,n->sparoCoordX,n->sparoCoordY,n->sparoCoordX);
                }
                else if (n->tipo == 'C'){p->aggiorna_vita(-(n->danno * n->attacco/p->def())); lv.AddCharacter('@',y,x,y,x);}
                else p->aggiorna_vita(-1);
                git-=2;
            }   
    }
    resetSparo(n);
}

void Nemico::sparo_left(Livello lv, Bonus b, Personaggio* p, ptrNemici n){//sparo a sinistra
    int git, x, y;
    bool flag;
    git=n->gittata;
    x=p->coordinata_x();
    y=p->coordinata_y();
    while(git > 0 && n->sparoCoordX>BONUS_LBORDER && n->sparoCoordX > x){//stampo lo sparo fino a quando non arrivo al bordo o sono arrivato alla gittata massima
        flag=isUpBonus(b, n->sparoCoordX-1, n->sparoCoordY);
        if(!flag){
            n->sparoCoordX--;
            if(n->sparoCoordX!=x) {
                lv.AddCharacter(183, n->sparoCoordY, n->sparoCoordX, n->sparoCoordY, n->sparoCoordX);
                p->clock(40000);
                lv.AddCharacter(' ',n->sparoCoordY,n->sparoCoordX,n->sparoCoordY,n->sparoCoordX);
                }
            else if (n->tipo == 'C'){p->aggiorna_vita(-(n->danno * n->attacco/p->def())); lv.AddCharacter('@',y,x,y,x);}
            else p->aggiorna_vita(-1);
            git--;
        }
        else{
            n->sparoCoordX=n->sparoCoordX-2;
            if(n->sparoCoordX!=x){
                lv.AddCharacter(183, n->sparoCoordY, n->sparoCoordX, n->sparoCoordY, n->sparoCoordX);
                p->clock(40000);
                lv.AddCharacter(' ',n->sparoCoordY,n->sparoCoordX,n->sparoCoordY,n->sparoCoordX);
            }
            else if (n->tipo == 'C'){p->aggiorna_vita(-(n->danno * n->attacco/p->def())); lv.AddCharacter('@',y,x,y,x);}
            else p->aggiorna_vita(-1);
            git-=2;
        }
    }
    resetSparo(n);
}


void Nemico::sparo_right(Livello lv, Bonus b, Personaggio* p, ptrNemici n){//sparo a destra 
    int git, x, y;
    bool flag;
    git=n->gittata;
    x=p->coordinata_x();
    y=p->coordinata_y();
    while(git > 0 && n->sparoCoordX<BONUS_RBORDER && n->sparoCoordX < x){//stampo lo sparo fino a quando non arrivo al bordo o sono arrivato alla gittata massima
        flag=isUpBonus(b, n->sparoCoordX+1, n->sparoCoordY);
        if(!flag){
            n->sparoCoordX++;
            if(n->sparoCoordX!=x){
                lv.AddCharacter(183, n->sparoCoordY, n->sparoCoordX, n->sparoCoordY, n->sparoCoordX);
                p->clock(40000);
                lv.AddCharacter(' ',n->sparoCoordY,n->sparoCoordX,n->sparoCoordY,n->sparoCoordX);
            }
            else if (n->tipo == 'C'){p->aggiorna_vita(-(n->danno * n->attacco/p->def())); lv.AddCharacter('@',y,x,y,x);}
            else p->aggiorna_vita(-1);
            git--;
        }
        else{
            n->sparoCoordX=n->sparoCoordX+2;
            if(n->sparoCoordX!=x){
                lv.AddCharacter(183, n->sparoCoordY, n->sparoCoordX, n->sparoCoordY, n->sparoCoordX);
                p->clock(40000);
                lv.AddCharacter(' ',n->sparoCoordY,n->sparoCoordX,n->sparoCoordY,n->sparoCoordX);
                }
            else if (n->tipo == 'C'){p->aggiorna_vita(-(n->danno * n->attacco/p->def())); lv.AddCharacter('@',y,x,y,x);}
            else p->aggiorna_vita(-1);
            git-=2;
        }
    }
    resetSparo(n);
}

bool Nemico::isUpBonus(Bonus b, int x, int y){
    blist list=b.List_Curr_Bns();
    bool sopra = false;
    while(list!=NULL && !sopra){
        if((list->picked==false) && (list->axisX==x) && (list->axisY==y)) sopra=true;  
        list=list->next;
    }
    return sopra;
}
bool Nemico::isUpNem(int x, int y, int count){
    bool isUp=false;
    int i=0;
    ptrNemici nem=listNemLiv->currentNem;
    while(nem!=NULL && isUp==false){
        if(nem->xCoord==x && nem->yCoord==y && nem->ucciso==false && i!=count) isUp=true;
        nem=nem->next;
        i++;
    }
    return isUp;
}
ptrNemici Nemico::listNemLivCurr(){return listNemLiv->currentNem;}

void Nemico::Potenzia(){
    ptrNemici head = listNemLiv->currentNem;
    if (nemLevel%4==0){
        while (listNemLiv->currentNem != NULL){
            switch (listNemLiv->currentNem->tipo){
                case 'A':
                listNemLiv->currentNem->difesa += 0.25;
                listNemLiv->currentNem->vita += 4;
                break;
                case 'B':
                listNemLiv->currentNem->attacco += 0.25;
                listNemLiv->currentNem->difesa += 0.25;
                listNemLiv->currentNem->vita += 2;
                break;
                case 'C':
                listNemLiv->currentNem->attacco += 0.25;
                listNemLiv->currentNem->difesa += 0.25;
                listNemLiv->currentNem->vita += 2;
            }
            listNemLiv->currentNem = listNemLiv->currentNem->next;
        }
        listNemLiv->currentNem = head;
    }
}

void Nemico::PiuNemici(){
        if(nemLevel%2==0){//ogni due livelli aumento di uno il numero di nemici
        n_nemici = n_nemici+1;
        if (n_nemici > 15) n_nemici = 15;
    }
}
