//
//  main.cpp
//  OCC_Proj4
//
//  Created by Anna Li on 11/2/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//
#include <iostream>
#include "MazeSolver.h"
int main() {
    
    MazeSolver solver("/Users/anna/Downloads/text.txt");
    
    if(solver.mazeIsReady())
    {
        solver.solveMaze();
        
        solver.printSolution();
    }
    
    return 0;
}
