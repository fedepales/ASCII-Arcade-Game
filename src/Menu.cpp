#include "Inclusion.hpp"
using namespace std;

Menu::Menu(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    getmaxyx(stdscr,altezza,larghezza);
}

int Menu::Crea_Finestra(){
    WINDOW* menuwin = newwin(altezza-4,larghezza-8,2,4);
    WINDOW* win;
    box(menuwin, 0, 0);
    wrefresh(menuwin);
    keypad(menuwin, true);
    int scelta;
    int evidenzia = 0;
    int y = altezza/3;
    int x = (larghezza-8)/2;
    int yold = y;
    int xold [5] = {x-8, x-5, x-5, x-5, x-4};
    mvwaddstr(menuwin, y, x-6, "Nuova Partita");
    mvwaddstr(menuwin, y+2, x-3, "Legenda");
    mvwaddstr(menuwin, y+4, x-3, "Comandi");
    mvwaddstr(menuwin, y+6, x-3, "Crediti");
    mvwaddstr(menuwin, y+8, x-2, "Esci");
    mvwaddstr(menuwin, altezza*2/3, x-12, "Premere X per selezionare");
    mvwaddch(menuwin, yold, xold[0], '@');
    while(true){
        scelta = wgetch(menuwin);
        switch (scelta) {
            case KEY_DOWN:
                mvwaddch(menuwin, yold, xold[evidenzia], ' ');
                evidenzia++;
                if (evidenzia > 4){
                    evidenzia = 0;
                    y = altezza/3;
                    mvwaddch(menuwin, y, xold[evidenzia], '@');
                    yold = y;
                }
                else{
                    yold = y+2;
                    mvwaddch(menuwin, yold, xold[evidenzia], '@');
                    y= y+2;
                }
                break;
            case KEY_UP:
                mvwaddch(menuwin, yold, xold[evidenzia], ' ');
                evidenzia--;
                if (evidenzia < 0){
                    evidenzia = 4;
                    y = (altezza/3)+8;
                    mvwaddch(menuwin, y, xold[evidenzia], '@');
                    yold = y;
                }
                else {
                    yold = y-2;
                    mvwaddch(menuwin, yold, xold[evidenzia], '@');
                    y = y-2;
                }
                break;
            case 'x':
                switch (evidenzia) {
                    case 0:
                        return(evidenzia);
                        break;
                    case 1:
                        win = newwin(altezza-4,larghezza-8,2,4);
                        mvwaddstr(win, ((altezza-4)/3)+2, (larghezza-8)/3+2, "-");
                        mvwaddstr(win, ((altezza-4)/3)+2, (larghezza-8)/3+3, " + : bonus che aumenta la vita");
                        mvwaddstr(win, ((altezza-4)/3)+4, (larghezza-8)/3+2, "-");
                        mvwaddch(win, ((altezza-4)/3)+4, (larghezza-8)/3+4, acs_map[45]);
                        mvwaddstr(win, ((altezza-4)/3)+4, (larghezza-8)/3+5, " : bonus che aumenta la difesa");
                        mvwaddstr(win, ((altezza-4)/3)+6, (larghezza-8)/3+2, "-");
                        mvwaddch(win,((altezza-4)/3)+6, (larghezza-8)/3+4, 165);
                        mvwaddstr(win, ((altezza-4)/3)+6, (larghezza-8)/3+5, " : aumenta il tuo punteggio!");
                        mvwaddstr(win, ((altezza-4)/3)+8, (larghezza-8)/3+2, "-");
                        mvwaddch(win, ((altezza-4)/3)+8, (larghezza-8)/3+4, 164);
                        mvwaddstr(win, ((altezza-4)/3)+8, (larghezza-8)/3+5, " : bonus che aumenta l'attacco");
                        mvwaddstr(win, ((altezza-4)/3)+10, (larghezza-8)/3+2, "-");
                        mvwaddstr(win, ((altezza-4)/3)+10, (larghezza-8)/3+3, " @ : se non lo avessi gia' capito, questo sei tu");
                        mvwaddstr(win, ((altezza-4)/3)+12, (larghezza-8)/3+2, "-");
                        mvwaddstr(win, ((altezza-4)/3)+12, (larghezza-8)/3+3, " A : torretta nemica, se ti avvicini spara, chi lo avrebbe mai detto...");
                        mvwaddstr(win, ((altezza-4)/3)+14, (larghezza-8)/3+2, "-");
                        mvwaddstr(win, ((altezza-4)/3)+14, (larghezza-8)/3+3, " B : ti corre incontro ma non ha armi, attento, potrebbe esplodere");
                        mvwaddstr(win, ((altezza-4)/3)+16, (larghezza-8)/3+2, "-");
                        mvwaddstr(win, ((altezza-4)/3)+16, (larghezza-8)/3+3, " C : spara e corre, spera di non ritrovartelo contro! Aspetta...");
                        wrefresh(win);
                        getwchar();
                        wclear(win);
                        overwrite(menuwin, win);
                        wrefresh(win);
                        break;
                    case 2:
                        win = newwin(altezza-4,larghezza-8,2,4);
                        mvwaddstr(win, ((altezza-4)/3)+2, (larghezza-8)/5, "Usa le frecce direzionali per muoverti, se vai a destra o sinistra starai incredibilmente cliccando le rispettive frecce!");
                        mvwaddstr(win, ((altezza-4)/3)+4, (larghezza-8)/5, "Usa il tasto W per sparare verso l'alto!");
                        mvwaddstr(win, ((altezza-4)/3)+6, (larghezza-8)/5, "Usa il tasto S per sparare in basso!");
                        mvwaddstr(win, ((altezza-4)/3)+8, (larghezza-8)/5, "Usa il tasto D per sparare a destra!");
                        mvwaddstr(win, ((altezza-4)/3)+10, (larghezza-8)/5, "Usa il tasto A per sparare a sinistra!");
                        mvwaddstr(win, ((altezza-4)/3)+12, (larghezza-8)/5, "Corri in giro per la mappa e trova i bonus, passandoci sopra diventerai piu' du... Potente!");
                        mvwaddstr(win, ((altezza-4)/3)+14, (larghezza-8)/5, "Evita i nemici, o morirai!");
                        mvwaddstr(win, ((altezza-4)/3)+16, (larghezza-8)/5, "Lo scopo del gioco e' fare piu' punti possibile... Se la tua vita scende a 0 vedrai degli arcobaleni, provaci! Divertiti nel nostro gioco!");
                        wrefresh(win);
                        getwchar();
                        wclear(win);
                        overwrite(menuwin, win);
                        wrefresh(win);
                        break;
                    case 3:
                        win = newwin(altezza-4,larghezza-8,2,4);
                        mvwaddstr(win, ((altezza-4)/3)+2, (larghezza-8)/3, "Gli autori del gioco sono: ");
                        mvwaddstr(win, ((altezza-4)/3)+4, (larghezza-8)/3, "Nikolas Acquaviva per il Livello e i Bonus!");
                        mvwaddstr(win, ((altezza-4)/3)+6, (larghezza-8)/3, "Federica Palestini per i Nemici!");
                        mvwaddstr(win, ((altezza-4)/3)+8, (larghezza-8)/3, "Stefano Carminati per il Personaggio e il Menu!");
                        mvwaddstr(win, ((altezza-4)/3)+10, (larghezza-8)/3, "Un ringraziamento speciale alle nostre mani e alla nostra testa, saremmo morti senza di loro!");
                        mvwaddstr(win, ((altezza-4)/3)+12, (larghezza-8)/3, "Buon divertimento!");
                        wrefresh(win);
                        getwchar();
                        wclear(win);
                        overwrite(menuwin, win);
                        wrefresh(win);
                        break;
                    case 4: return(evidenzia);
                }
        }
    }
}

