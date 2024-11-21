#include "Inclusion.hpp"
using namespace std;

int main(){
    Menu menu = Menu();
    if (menu.Crea_Finestra()==0){
        Livello lv = Livello();
        Bonus b = Bonus();
        Personaggio pg = Personaggio();
        Nemico n = Nemico();
        Livello_Bonus lb = Livello_Bonus();
        bool nem_on = false;
        lv.NewLevel(pg); 
        lv.Setup_Level(&b, &n);
        lv.AddCharacter('@', 0, 0, pg.coordinata_y(), pg.coordinata_x());
        while(!pg.GameOver()){
            int c = lv.GetMove();
            if(c!=ERR){
                if(!lv.Current_Win()->isBonus && nem_on) {
                    pg.clock(60000);
                    n.moveNem(&pg, lv, b);
                    nem_on = false;
                    }
                else if(!lv.Current_Win()->isBonus && !nem_on) {pg.clock(80000); nem_on = true;}
                switch(c){
                    case KEY_RIGHT:
                        if (pg.coordinata_x() < RIGHT_BORDER) pg.movimento_destra(lv, n);
                        break;
                    case KEY_LEFT:
                        if (pg.coordinata_x() > LEFT_BORDER) pg.movimento_sinistra(lv, n);
                        break;
                    case KEY_UP:                
                        if (pg.coordinata_y() > UPPER_BORDER) pg.movimento_su(lv, n);
                        else if (lv.Current_Win()->next != NULL){
                            lv.AddCharacter(' ', pg.coordinata_y(), pg.coordinata_x(), pg.coordinata_y(), pg.coordinata_x());
                            if(!lv.Current_Win()->next->isBonus){
                                if(!lv.Current_Win()->isBonus) n.GoNextNem();
                                else lb.TurnOnNem(n);
                                lv.GoNext(); b.Next_Bns_List();
                            }
                            else{lv.GoNext(); b.Next_Bns_List(); lb.TurnOffNem(n);}
                            lv.AddCharacter('@', pg.coordinata_y(), pg.coordinata_x(), BOTTOM_BORDER, pg.coordinata_x());
                            pg.update_y(BOTTOM_BORDER);
                        }
                        else{
                            if(lv.LevelNum()%6==0){
                                lb.TurnOffNem(n);
                                lv.AddCharacter(' ', pg.coordinata_y(), pg.coordinata_x(), pg.coordinata_y(), pg.coordinata_x());
                                lb.NewLevel(pg,&lv,&b);
                                lv.AddCharacter('@', pg.coordinata_y(), pg.coordinata_x(), BOTTOM_BORDER, pg.coordinata_x());
                                pg.update_y(BOTTOM_BORDER);
                            }
                            else{
                                lv.AddCharacter(' ', pg.coordinata_y(), pg.coordinata_x(), pg.coordinata_y(), pg.coordinata_x());
                                lv.NewLevel(pg);
                                lv.Setup_Level(&b, &n);
                                lv.AddCharacter('@', pg.coordinata_y(), pg.coordinata_x(), BOTTOM_BORDER, pg.coordinata_x());
                                pg.update_y(BOTTOM_BORDER);
                            }
                        }
                        break;
                    case KEY_DOWN:
                        if (pg.coordinata_y() < BOTTOM_BORDER) pg.movimento_down(lv, n);
                        else if (lv.Current_Win()->prev != NULL){
                            lv.AddCharacter(' ', pg.coordinata_y(), pg.coordinata_x(), pg.coordinata_y(), pg.coordinata_x());
                            if(!lv.Current_Win()->prev->isBonus){
                                if(lv.Current_Win()->isBonus) lb.TurnOnNem(n);
                                else n.GoBackNem();
                                lv.GoBack(); b.Prev_Bns_List(); 
                                }
                            else{
                                lv.GoBack();
                                lb.TurnOffNem(n);
                                b.Prev_Bns_List();
                            }
                            lv.AddCharacter('@', pg.coordinata_y(), pg.coordinata_x(), UPPER_BORDER, pg.coordinata_x());
                            pg.update_y(UPPER_BORDER);
                        }
                        break;
                    case 'w':
                        if(!lv.Current_Win()->isBonus && pg.In_Border()) pg.sparo_su(lv, b, n);
                        break;
                    case 'a':
                        if(!lv.Current_Win()->isBonus && pg.In_Border()) pg.sparo_sinistra(lv, b, n);
                        break;
                    case 's':
                        if(!lv.Current_Win()->isBonus && pg.In_Border()) pg.sparo_giu(lv, b, n);
                    break;
                    case 'd':
                        if(!lv.Current_Win()->isBonus && pg.In_Border()) pg.sparo_destra(lv, b, n);
                }
                b.Is_Picked(&pg);
                lv.Update_Health(pg);
                lv.Update_Pts(pg);
                lv.Update_Atk(pg);
                lv.Update_Def(pg);
            }
            else{
                if(!lv.Current_Win()->isBonus && nem_on){
                    pg.clock(60000);
                    n.moveNem(&pg,lv,b);
                    nem_on = false;
                }
                else if(!lv.Current_Win()->isBonus && !nem_on) {pg.clock(60000); nem_on = true;}
                b.Is_Picked(&pg);
                lv.Update_Health(pg);
                lv.Update_Pts(pg);
                lv.Update_Atk(pg);
                lv.Update_Def(pg);
                }
            }  
        }
    return 0;
}