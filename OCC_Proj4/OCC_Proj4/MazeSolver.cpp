//
//  MazeSolver.cpp
//  OCC_Proj4
//
//  Created by Anna Li on 11/2/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//

#include "MazeSolver.h"
#include <fstream>
#include <iostream>

MazeSolver::MazeSolver(std::string input_file) {
    std::ifstream in_stream;
    //try
    //{
        
    in_stream.open(input_file);
    if (in_stream.fail()){
        std::cerr<<"Cannot read from " + input_file;
        exit(1);
    }
        /*
        std::string firstLine;
        while(!in_stream.eof()) // To get you all the lines.
        {
            std::getline(in_stream, firstLine); // Saves the line in firstLine.
        }
        
        maze_rows_ = stoi (firstLine.substr(0,1));
        maze_columns_ = stoi (firstLine.substr(2,3));
         */
    else {
        in_stream >> maze_rows_;
        in_stream >> maze_columns_;
        initializeMaze(maze_rows_, maze_columns_);
        fillMaze(in_stream);
        initializeSolution();
        
    }
    //catch (const std::ifstream::failure& e)
    //{
        //std::cout << "Cannot read from" + input_file;
    //}
   
}

MazeSolver::~MazeSolver() {
    for(int i = 0; i < maze_rows_; i++) {
        delete[] maze_[i];
        delete[] solution_[i];
    }
    
    delete[] maze_;
    maze_ = nullptr;
    delete[] solution_;
    solution_ = nullptr;
}

bool MazeSolver::mazeIsReady() {
    return maze_ready;
}

//called by constructor
void MazeSolver::initializeMaze(int rows, int columns) {
    
    //initializes maze_ with rows
    maze_ = new char *[rows];
    
    //initializes maze_ with columns
    for (int i = 0 ; i < rows ; i++) {
        maze_[i] = new char[columns];
    }
    maze_ready = true;
}

//called by constructor
void MazeSolver::fillMaze(std::ifstream& input_stream) {
    
/*
    //inputs line from input_stream into a string variable
    std::string firstLine;
    while(!input_stream.eof()) // To get you all the lines.
    {
        std::getline(input_stream, firstLine); // Saves the line in firstLine.
    }
   */
    //std::string character;
    //int count = 4;
    if (maze_ready) {
        for (int i = 0; i<maze_rows_; i++) {
            for (int j = 0; j<maze_columns_; j++) {
                input_stream >> maze_[i][j];
            
            /*
            //next character in input_stream file to put into 2d maze
            character = firstLine.substr(count, count+1);
            
            //convert type string from input into type char using pointer
            char *c = new char[1];
            std::copy(character.begin(), character.end(), c);
            //c[1] = '\0';
            
            //assign array to character stored in pointer
            maze_[i][j] = *c;
            
            //delete pointer
            delete[] c;
            std::cout << maze_[i][j] << "0"<< endl;
            */
            }
        }
    }

}

//called by constructor
void MazeSolver::initializeSolution(){
    if (maze_ready) {
    copyMazetoSolution();
    Position start;
    start.row = 0;
    start.column = 0;
    backtrack_stack_.push(start);
    extendPath(start);
    solution_[0][0] = '>';
    }
}

//called by initializeSolution
void MazeSolver::copyMazetoSolution(){
    
    //initializes solution_ array
    solution_ = new char *[maze_rows_];
    for (int i = 0 ; i < maze_rows_ ; i++){
        solution_[i] = new char[maze_columns_];
    }
    
    //DEEP??? copy of maze_ to solution
    for (int i = 0; i < maze_rows_; i++)
    {
        for (int j = 0; j < maze_columns_; j++)
        {
            solution_[i][j] = maze_[i][j];
        }
    }
}

bool MazeSolver::extendPath(Position current_position){
    bool pathExtended = false;
    if (isExtensible(current_position, SOUTH)) {
        backtrack_stack_.push(getNewPosition(current_position, SOUTH));
        pathExtended = true;
    }
    if (isExtensible(current_position, EAST)) {
        backtrack_stack_.push(getNewPosition(current_position, EAST));
        pathExtended = true;
    }
    return pathExtended;
}

Position MazeSolver::getNewPosition(Position old_position, direction dir) {
    Position newPosition;
    newPosition.row = 0;
    newPosition.column = 0;
    if (dir == EAST) {
        newPosition.row = old_position.row;
        newPosition.column = old_position.column+1;
    }
    if (dir == SOUTH) {
        newPosition.row = old_position.row +1;
        newPosition.column = old_position.column;
    }
   
    return newPosition;
}

bool MazeSolver::isExtensible(Position current_position, direction dir){
    if (dir == SOUTH && current_position.row <maze_rows_ -1 && current_position.column < maze_columns_) {
        if (maze_[current_position.row+1][current_position.column] == '_' || maze_[current_position.row+1][current_position.column] == '$') {
            return true;
        }
    }
    if (dir == EAST && current_position.column < maze_columns_ - 1 && current_position.row < maze_rows_) {
        if (maze_[current_position.row][current_position.column+1] == '_' || maze_[current_position.row][current_position.column+1] == '$') {
            return true;
        }
    }
    return false;
}

bool MazeSolver::solveMaze() {
    while (backtrack_stack_.size() !=0) {
        Position currentPosition;
        currentPosition = backtrack_stack_.top();
        
        int row = currentPosition.row;
        int col = currentPosition.column;
        
        if (row < maze_rows_ && col < maze_columns_ && solution_[row][col] == '$') {
            std::cout << "Found the exit!!!" << std::endl;
            return true;
        }
        else {
            if (isExtensible(currentPosition, SOUTH)|| isExtensible(currentPosition, EAST)) {
                solution_[currentPosition.row][currentPosition.column] = '>';
                extendPath(currentPosition);
            }
            else {
                maze_[currentPosition.row][currentPosition.column] = 'X';
                solution_[currentPosition.row][currentPosition.column] = '@';
                backtrack_stack_.pop();
                if (backtrack_stack_.size() == 0) {
                    std::cout << "This maze has no solution." << std::endl;
                    return false;
                }
            }
        }
    }
    return false;
}

void MazeSolver::printSolution() {
    std::cout << "The solution to this maze is:" << std::endl;
    for (int i = 0; i < maze_rows_; i++) {
        for (int j = 0; j < maze_columns_-1; j++) {
            std::cout << solution_[i][j] << " ";
        }
        std::cout << solution_[i][maze_columns_ -1] << std::endl;
    }
    std::cout<<""<<std::endl;
}

