#ifndef NEMICO_HPP_
#define NEMICO_HPP_

#include <ncurses.h>

#include "Livello.hpp"
#include "Personaggio.hpp"
#include "Bonus.hpp"

#define BONUS_RBORDER (RIGHT_BORDER-2)
#define BONUS_LBORDER (LEFT_BORDER+2)
#define BONUS_UBORDER (UPPER_BORDER+3)
#define BONUS_BBORDER (BOTTOM_BORDER-3)

class Livello;
class Personaggio;
class Bonus;


struct nemici{//lista di nemici per il singolo livello
    char tipo; //identifica il tipo di mostro
	bool ucciso; //indica se il nemico è stato ucciso o no, true se ucciso, false se non è stato ucciso
	int danno;
	double attacco;
	int vita;
	double difesa;
	int gittata;
	int sparoCoordX;
	int sparoCoordY;
	int xCoord;//cordinata x del nemico
    int yCoord;//cordinata y del nemico
	nemici *next;
};
typedef nemici* ptrNemici;

struct nemiciLevel{//lista di livelli, ogni livello contine una lista di nemici ancora vivi
	nemiciLevel *prev;
	ptrNemici currentNem;
	nemiciLevel *next;
};
typedef nemiciLevel* ptrListLevel;


class Nemico {
	private:
		void moveUp(ptrNemici n);//muove i nemici di una coordinata sopra
		void moveBottom(ptrNemici n);//muove i nemici di una coordinata sotto
		void moveLeft(ptrNemici n);//muove i nemici di una coordinata a sinistra
		void moveRight(ptrNemici n);//muove i nemici di una coordinata a destra
		bool isUpBonus(Bonus, int x, int y);//controlla che il nemico non vada sopra ad un bonus
		bool isUpNem(int x, int y, int count);//controlla che il nemico non vada sopra altri nemici
		void sparo_up(Livello, Bonus, Personaggio*, ptrNemici n);
		void sparo_down(Livello, Bonus, Personaggio*, ptrNemici n);
		void sparo_left(Livello, Bonus, Personaggio*, ptrNemici n);
		void sparo_right(Livello, Bonus, Personaggio*, ptrNemici n);
		void resetSparo(ptrNemici n);

	protected:
		ptrListLevel listNemLiv;//puntatore alla lista di livelli che contiene un puntatore alla lista di nemici di quel livello
		int n_nemici;
		int baseAtk;
		int baseDef;
		int baseHealth;
		int nemLevel;//livello corrente

	public:
		Nemico();
		void createListNemici();//genera la lista di nemici di un singolo livello
		int moveNemicoX(int x);//muove il nemico sull'asse x;
		int moveNemicoy(int y);//muove il nemico sull'asse Y;
		void printListNemici(WINDOW*);//stampa i nemici nella finestra 
		void addListToLevel(ptrNemici n);//aggiunge la lista di nemici al livello corrente
		void GoNextNem();//va nella lista di nemici del livello successivo
		void GoBackNem();//va nella lista di nemici del livello precedente
		ptrNemici listNemLivCurr();//ritorna la lista dei nemici del livello corrente
		void moveNem(Personaggio* p, Livello, Bonus);//muove il nemico a seconda del personaggio
		void moveNemB(Personaggio* p, Livello , Bonus , ptrNemici nem, int count);
		void moveNemC(Personaggio* p, Livello , Bonus , ptrNemici nem, int count);
		void sparo(Livello, Bonus, Personaggio, ptrNemici n);
		void Potenzia();
		void PiuNemici();
};

#endif
