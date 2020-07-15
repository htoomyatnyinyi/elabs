/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#ifndef BOARDS_DEFS_H
#define BOARDS_DEFS_H

#include "board.h"
#include "board_1.h"

#define board_init(function)  static void __attribute__((constructor)) function(void) 

typedef board * (* board_create_func)(void);

void board_register(int num, const char * name, board_create_func bcreate);

//boards object creation
board * create_board(int *lab, int *lab_);

#define BOARDS_MAX 10

extern int BOARDS_LAST;

typedef struct {
    int num;
    char name[30];
    board_create_func bcreate;
} board_desc;

extern board_desc boards_list[BOARDS_MAX];

#endif /* BOARDS_DEFS_H */

