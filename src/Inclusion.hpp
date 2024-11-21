#ifndef INCLUSION_HPP_
#define INCLUSION_HPP_
#include <ncurses.h>
#include <cmath>
#include <ctime>
#include <random>
#include "Personaggio.hpp"
#include "Livello.hpp"
#include "Livello_Bonus.hpp"
#include "Nemico.hpp"
#include "Bonus.hpp"
#include "Menu.hpp"

#define HUDLINE (int)(getmaxx(stdscr)*0.65)
#define BOTTOM_BORDER (getmaxy(stdscr)-8)
#define UPPER_BORDER 4
#define RIGHT_BORDER (HUDLINE-5)
#define LEFT_BORDER 5

#define BONUS_RBORDER (RIGHT_BORDER-2)
#define BONUS_LBORDER (LEFT_BORDER+2)
#define BONUS_UBORDER (UPPER_BORDER+3)
#define BONUS_BBORDER (BOTTOM_BORDER-3)

#define AWARD_UBORDER (BONUS_UBORDER+7)
#define AWARD_LBORDER (BONUS_LBORDER+5)
#define AWARD_RBORDER (BONUS_RBORDER-7)
#define AWARD_BBORDER (BONUS_BBORDER-5)

struct bonus_item;
typedef bonus_item* blist;

#endif
