//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    file->seekg(0, file->end);
    int pos = file->tellg();
    return pos;
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){

    this->board_size= board_size;

    //open files as filestream
    ifstream p1;
    p1.open (p1_setup_board, ifstream::in);
    ifstream p2;
    p2.open(p2_setup_board, ifstream::in);

    //get length of files
    unsigned int p1size= get_file_length(&p1);
    unsigned int p2size = get_file_length(&p2);

    //compare to board size, accounting for newline chars
    int board_length = pow(board_size, 2) + board_size-1;

    if(!(board_length==p1size && board_length==p2size)){
        throw ServerException("Invalid Boards!");
    }

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    if(player < 1 || player > MAX_PLAYERS){
        throw ServerException("Invalid Player Number");
    }

    if(x > BOARD_SIZE || y > BOARD_SIZE){
        return OUT_OF_BOUNDS;
    }

    string player_file;
    player_file = get_file_name("setup_board", player, ".txt");
    ifstream setupboard;
    setupboard.open(player_file);

    int position;
    position = (y*(BOARD_SIZE+1));
    position += x;
    setupboard.seekg(position);
    char current = setupboard.get();


    if(current == 'D' || current == 'C' || current == 'B' || current == 'S' || current == 'R'){
        return HIT;
    }

    else
        return MISS;


}


int Server::process_shot(unsigned int player) {
   if(player < 1 || player > MAX_PLAYERS){
       throw ServerException("Invalid Player Number");
   }
   return NO_SHOT_FILE;
}

string Server::get_file_name(string board, int player, string extension){
    string player_file = "player_";
    string player_number = to_string(player);
    player_file.append(player_number);
    player_file.append(".");
    player_file.append(board);
    player_file.append(extension);
    return player_file;
}