#ifndef Personaggio_HPP_
#define Personaggio_HPP_


const int dancst = 5;

class Livello;
class Livello_Bonus;
class Bonus;
class Nemico;

class Personaggio {
protected:
	int punteggio; //mi dice qual � il mio punteggio attuale
	int vita; //indica la mia vita attuale
	float danni; //mi dice che danno faccio per ogni colpo a segno
	float attacco; //è il moltiplicatore del danno
	float difesa; //mi da una riduzione di danno
	int coordinate_x; //contiene le coordinate dove il personaggio viene generato
	int coordinate_y; //contiene le coordinate dove il personaggio viene generato
	int range; //indica quanto in là spari
	int sparo_y;
	int sparo_x;
public:
	Personaggio();
	void movimento_su(Livello, Nemico);
	void movimento_sinistra(Livello, Nemico);
	void movimento_down(Livello, Nemico);
	void movimento_destra(Livello, Nemico);
	int coordinata_x();
	int coordinata_y();
	void update_y(int);
	void sparo_su(Livello, Bonus, Nemico);
	void sparo_giu(Livello, Bonus, Nemico);
	void sparo_destra(Livello, Bonus, Nemico);
	void sparo_sinistra(Livello, Bonus, Nemico);
	void hit(Bonus, Livello, Nemico);
	void clock(int);
    void resetta_canna();
	int Pum_X();
	int Pum_Y();
	int life();
	void aggiorna_vita(int);
	int punti();
	void aggiorna_punteggio();
	double atk();
	int danno();
	void aggiorna_atk();
	double def();
	void aggiorna_def();
	bool GameOver();
	bool In_Border();
};

#endif
