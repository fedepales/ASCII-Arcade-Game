#include "Inclusion.hpp"
using namespace std;

Personaggio::Personaggio() {
	punteggio = 0;
	vita = 50;
	danni = dancst;
	attacco = 1;
	difesa = 1;
	coordinate_y = BOTTOM_BORDER;
	coordinate_x = HUDLINE/2;
	range = BONUS_RBORDER/6;
	sparo_y = coordinate_y;
	sparo_x = coordinate_x;
}
;

void Personaggio::movimento_destra(Livello lv, Nemico n) {
	ptlist head = lv.Current_Win();
	ptrNemici testa = n.listNemLivCurr();
	ptrNemici traccia = testa;
	bool ciccio = false;
	while ((traccia != NULL) && (!ciccio) && (!head->isBonus)){
	if ((coordinate_y == traccia->yCoord) && (coordinate_x+1 == traccia->xCoord) && (!traccia->ucciso)){
		ciccio = true;
		aggiorna_vita(-5);
		lv.AddCharacter(' ', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x());
		lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x());
	}
	traccia = traccia->next;
	}
	if ((!ciccio) && (!head->isBonus)){
	lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x()+1);
	coordinate_x++;
	resetta_canna();
	}
	traccia = testa;
	if (head->isBonus){
		if (((coordinate_x != AWARD_RBORDER && coordinate_x != AWARD_LBORDER-2) 
		&& ((coordinate_y == AWARD_BBORDER+1 || coordinate_y == AWARD_UBORDER-1) 
		&& (coordinate_x < ((AWARD_RBORDER+AWARD_LBORDER-2)/2)+3 || coordinate_x > AWARD_RBORDER || coordinate_x < AWARD_LBORDER-2)))
		|| coordinate_y > AWARD_BBORDER+1 || coordinate_y < AWARD_UBORDER-1
		|| ((coordinate_y != AWARD_BBORDER+1 && coordinate_y != AWARD_UBORDER-1) && (coordinate_x != AWARD_RBORDER && coordinate_x != AWARD_LBORDER-2))){
				lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x()+1);
				coordinate_x++;
				resetta_canna();
		}
	}
}
;

void Personaggio::movimento_sinistra(Livello lv, Nemico n) {
	ptlist head = lv.Current_Win();
	ptrNemici testa = n.listNemLivCurr();
	ptrNemici traccia = testa;
	bool ciccio = false;
	while ((traccia != NULL) && (!ciccio) && (!head->isBonus)){
	if ((coordinate_y == traccia->yCoord) && (coordinate_x-1 == traccia->xCoord) && (!traccia->ucciso)){
		ciccio = true;
		aggiorna_vita(-5);
		lv.AddCharacter(' ', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x());
		lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x());
	}
	traccia = traccia->next;
	}
	if ((!ciccio) && (!head->isBonus)){
	lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x()-1);
	coordinate_x--;
	resetta_canna();
	}
	traccia = testa;
	if (head->isBonus){
		if (((coordinate_x != AWARD_RBORDER+2 && coordinate_x != AWARD_LBORDER) 
		&& ((coordinate_y == AWARD_BBORDER+1 || coordinate_y == AWARD_UBORDER-1) 
		&& (coordinate_x > (AWARD_RBORDER+AWARD_LBORDER-2)/2 || coordinate_x > AWARD_RBORDER+2 || coordinate_x < AWARD_LBORDER)))
		|| coordinate_y > AWARD_BBORDER+1 || coordinate_y < AWARD_UBORDER-1
		|| ((coordinate_y != AWARD_BBORDER+1 && coordinate_y != AWARD_UBORDER-1) && (coordinate_x != AWARD_RBORDER+2 && coordinate_x != AWARD_LBORDER))){
				lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x()-1);
				coordinate_x--;
				resetta_canna();
		}
	}
}
;

void Personaggio::movimento_su(Livello lv, Nemico n) {
	ptlist head = lv.Current_Win();
	ptrNemici testa = n.listNemLivCurr();
	ptrNemici traccia = testa;
	bool ciccio = false;
	while ((traccia != NULL) && (!ciccio) && (!head->isBonus)){
	if ((coordinate_y-1 == traccia->yCoord) && (coordinate_x == traccia->xCoord) && (!traccia->ucciso)){
		ciccio = true;
		aggiorna_vita(-5);
		lv.AddCharacter(' ', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x());
		lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x());
	}
	traccia = traccia->next;
	}
	if ((!ciccio) && (!head->isBonus)){
	lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y()-1, coordinata_x());
	coordinate_y--;
	resetta_canna();
	}
	traccia = testa;
	if (head->isBonus){
		if ((coordinate_y != AWARD_BBORDER+2 && coordinate_y != AWARD_UBORDER) || coordinate_x > AWARD_RBORDER+1 || coordinate_x < AWARD_LBORDER-1
		|| (coordinate_y == AWARD_BBORDER+2 && (coordinate_x > ((AWARD_RBORDER+AWARD_LBORDER-2)/2)-1 && coordinate_x < ((AWARD_RBORDER+AWARD_LBORDER-2)/2)+4))
		|| (coordinate_y == AWARD_UBORDER && (coordinate_x > ((AWARD_RBORDER+AWARD_LBORDER-2)/2)-1 && coordinate_x < ((AWARD_RBORDER+AWARD_LBORDER-2)/2)+4))){
				lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y()-1, coordinata_x());
				coordinate_y--;
				resetta_canna();
		}
	}
}
;

void Personaggio::movimento_down(Livello lv, Nemico n){
	ptlist head = lv.Current_Win();
	ptrNemici testa = n.listNemLivCurr();
	ptrNemici traccia = testa;
	bool ciccio = false;
	while ((traccia != NULL) && (!ciccio) && (!head->isBonus)){
	if ((coordinate_y+1 == traccia->yCoord) && (coordinate_x == traccia->xCoord) && (!traccia->ucciso)){
		ciccio = true;
		aggiorna_vita(-5);
		lv.AddCharacter(' ', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x());
		lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y(), coordinata_x());
	}
	traccia = traccia->next;
	}
	if ((!ciccio) && (!head->isBonus)){
	lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y()+1, coordinata_x());
	coordinate_y++;
	resetta_canna();
	}
	traccia = testa;
	if (head->isBonus){
		if ((coordinate_y != AWARD_BBORDER && coordinate_y != AWARD_UBORDER-2) || coordinate_x > AWARD_RBORDER+1 || coordinate_x < AWARD_LBORDER-1
		|| (coordinate_y == AWARD_BBORDER && (coordinate_x > ((AWARD_RBORDER+AWARD_LBORDER-2)/2)-1 && coordinate_x < ((AWARD_RBORDER+AWARD_LBORDER-2)/2)+4))
		|| (coordinate_y == AWARD_UBORDER-2 && (coordinate_x > ((AWARD_RBORDER+AWARD_LBORDER-2)/2)-1 && coordinate_x < ((AWARD_RBORDER+AWARD_LBORDER-2)/2)+4))){
				lv.AddCharacter('@', coordinata_y(), coordinata_x(), coordinata_y()+1, coordinata_x());
				coordinate_y++;
				resetta_canna();
		}
	}
}
;

int Personaggio::coordinata_x(){
	return (coordinate_x);
}
;

int Personaggio::coordinata_y(){
	return (coordinate_y);
}
;

void Personaggio::update_y(int y){
	coordinate_y = y;
}
;

void Personaggio::sparo_su(Livello lv, Bonus b, Nemico n) {
	while ((range-(BONUS_RBORDER/15) > 0) && (sparo_y > BONUS_UBORDER)){
	sparo_y--;
	lv.AddCharacter(183, sparo_y, sparo_x, sparo_y, sparo_x);
	clock(40000);
	lv.AddCharacter(' ', sparo_y, sparo_x, sparo_y, sparo_x);
	hit(b, lv, n);
	range--;
	}
	resetta_canna();
}
;

void Personaggio::sparo_giu(Livello lv, Bonus b, Nemico n) {
	while ((range-(BONUS_RBORDER/15) > 0) && (sparo_y < BONUS_BBORDER)){
		sparo_y++;
		lv.AddCharacter(183, sparo_y, sparo_x, sparo_y, sparo_x);
		clock(40000);
		lv.AddCharacter(' ', sparo_y, sparo_x, sparo_y, sparo_x);
		hit(b, lv, n);
	range--;
	}
	resetta_canna();
}
;

void Personaggio::sparo_destra(Livello lv, Bonus b, Nemico n) {
	while ((range > 0) && (sparo_x < BONUS_RBORDER)){
		sparo_x++;
		lv.AddCharacter(183, sparo_y, sparo_x, sparo_y, sparo_x);
		clock(40000);
		lv.AddCharacter(' ', sparo_y, sparo_x, sparo_y, sparo_x);
		hit(b, lv, n);
	range--;
	}
	resetta_canna();
}
;

void Personaggio::sparo_sinistra(Livello lv, Bonus b, Nemico n) {
	while ((range > 0) && (sparo_x > BONUS_LBORDER)){
		sparo_x--;
		lv.AddCharacter(183, sparo_y, sparo_x, sparo_y, sparo_x);
		clock(40000);
		lv.AddCharacter(' ', sparo_y, sparo_x, sparo_y, sparo_x);
		hit(b, lv, n);
	range--;
	}
	resetta_canna();
}
;

void Personaggio::hit(Bonus b, Livello lv, Nemico n) {
	blist head = b.List_Curr_Bns();
	blist scorro = head;
	WINDOW * w = lv.Current_Win()->current_level;
	ptrNemici testa = n.listNemLivCurr();
	ptrNemici traccia = testa;
	while (scorro != NULL){
	if ((Pum_X() == scorro->axisX) && (Pum_Y() == scorro->axisY) && (!scorro->picked)) b.Add_Bns(w, scorro);
		scorro = scorro->next;	
	}
	while (traccia != NULL){
	if ((Pum_X() == traccia->xCoord) && (Pum_Y() == traccia->yCoord) && (!traccia->ucciso)){
		traccia->vita = traccia->vita - danni/traccia->difesa;
		if (traccia->vita > 0) mvwaddch(w, traccia->yCoord, traccia->xCoord, traccia->tipo);
		else {
			traccia->ucciso = true;
			punteggio = punteggio + 200;
		}
	}
		traccia = traccia->next;
	}
	scorro = head;
	traccia = testa;
	wrefresh(w);	
}
;

void Personaggio::clock(int n) {
  int i,j;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
}
;

void Personaggio::resetta_canna(){
	sparo_y = coordinate_y;
	sparo_x = coordinate_x;
	range = BONUS_RBORDER/7;
}
;

int Personaggio::Pum_X(){
	return (sparo_x);
}
;

int Personaggio::Pum_Y(){
	return (sparo_y);
}
;

int Personaggio::life(){
	return(vita);
}
;

void Personaggio::aggiorna_vita(int x){
	vita = vita + x;
	vita = vita - (vita / 50) * (vita % 50);
	if (vita < 0) vita = 0;
}
;

int Personaggio::punti(){
	return(punteggio);
}
;

void Personaggio::aggiorna_punteggio(){
	punteggio = punteggio + 100;
}
;

double Personaggio::def(){
	return(difesa);
}
;

void Personaggio::aggiorna_def(){
	difesa = difesa + 0.25;
}
;

double Personaggio::atk(){
	return(attacco);
}
;

int Personaggio::danno(){
	return(danni);
}
;

void Personaggio::aggiorna_atk(){
	attacco = attacco + 0.25;
	danni = dancst*attacco;
}
;

bool Personaggio::GameOver(){
	return (vita==0);
}
;

bool Personaggio::In_Border(){
	return (coordinate_x >= BONUS_LBORDER && coordinate_x <= BONUS_RBORDER &&
	coordinate_y >= BONUS_UBORDER && coordinate_y <= BONUS_BBORDER);
}