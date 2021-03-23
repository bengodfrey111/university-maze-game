#include <random> //this file has all been created by Ben G
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

int square(int a){
    return a * a;
}

bool inArray(int x,int y, std::vector<int> xarray, std::vector<int> yarray, int backUp = 0){ //checks if values are in an array (backUp is reducing the amount of loops)
    for(int i = 0; i < xarray.size() - backUp; i++){
        if(xarray[i] == x && yarray[i] == y){
            return true;
        }
    }
    return false;
}

std::vector<std::vector<char>> sideDraw(std::vector<std::vector<char>> maze, int xSize, int ySize, std::vector<int> xRoute, std::vector<int> yRoute, int i = -1){ //draws the route,
    if(i == -1){
        i = xRoute.size() - 1;
    }
    //draws the route
    if(yRoute[i] + 1 > 0 && yRoute[i] + 1 < ySize - 1 && inArray(xRoute[i],yRoute[i] + 1, xRoute, yRoute, 1) == false){
        maze[yRoute[i] + 1][xRoute[i]] = '#';
    }
    if(yRoute[i] - 1 > 0 && yRoute[i] - 1 < ySize - 1 && inArray(xRoute[i],yRoute[i] - 1, xRoute, yRoute, 1) == false){
        maze[yRoute[i] - 1][xRoute[i]] = '#';
    }
    if(xRoute[i] + 1 > 0 && xRoute[i] + 1 < xSize - 1 && inArray(xRoute[i] + 1,yRoute[i], xRoute, yRoute, 1) == false){
        maze[yRoute[i]][xRoute[i] + 1] = '#';
    }
    if(xRoute[i] - 1 > 0 && xRoute[i] - 1 < xSize - 1 && inArray(xRoute[i] - 1,yRoute[yRoute.size() - 1], xRoute, yRoute, 1) == false){
        maze[yRoute[i]][xRoute[i] - 1] = '#';
    }
    return maze;
}

std::vector<std::vector<char>> ensureClear(std::vector<std::vector<char>> maze, std::vector<int> xRoute, std::vector<int> yRoute){ //ensures there is a clear path
    for(int i = 0; i < xRoute.size(); i++){//xRoute is the same size as yRoute
        if(maze[yRoute[i]][xRoute[i]] != 'e' && maze[yRoute[i]][xRoute[i]] != 's' && maze[yRoute[i]][xRoute[i]] != '-'){
            maze[yRoute[i]][xRoute[i]] = ' ';
        }
    }
    return maze;
}

std::vector<std::vector<char>> emptyMaze(int xSize, int ySize){ //creates an empty maze
    std::vector<std::vector<char>> empty;
    for(int y = 0; y < ySize; y++){
        empty.push_back({});
        for(int x = 0; x < xSize; x++){
            empty[y].push_back(' ');
        }
    }
    return empty;
}

void testDisplay(std::vector<std::vector<char>> maze){ //used for development purposes only
    std::string end;
    for(int y = 0; y < maze.size(); y++){
        for(int x = 0; x < maze[y].size(); x++){
            end = end + maze[y][x];
        }
        end = end + '\n';
    }
    std::cout << end;
}

int countTrack(std::vector<std::vector<char>> maze, std::vector<int> xRoute, std::vector<int> yRoute){ //displays where player should go
    std::string end;
    int length = 0;
    for(int i = 0; i < xRoute.size(); i++){
        if(maze[xRoute[i]][yRoute[i]] != 'e' && maze[xRoute[i]][yRoute[i]] != 's'){
            maze[xRoute[i]][yRoute[i]] = '-';
            length = length + 1;
        }
    }
    testDisplay(maze); //so i can see the track instead of the edges of the track
    return length;
}


std::vector<std::vector<char>> mazeSolution(int xSize, int ySize, time_t seed = time(NULL)){ //seed can be changed for testing purposes
    int yStart;
    int xStart;
    std::vector<std::vector<char>> maze;
    std::vector<std::vector<char>> eMaze = emptyMaze(xSize, ySize); // this is to create an empty maze
    int end[2]; //coorodinates of where the end of the maze is (end[0] = x end[1] = y)
    std::vector< int > yRoute;
    std::vector< int > xRoute;
    int steps;
    srand (seed); //https://stackoverflow.com/questions/7748071/same-random-numbers-every-time-i-run-the-program
    char displayedChar[2] = {'#', ' '}; //array[0] location is 1 array[1] location 2 array[3] is location 3
    int repeats = -1; //so I can see the amount of failed mazes
    while(true){ //repeats until there is a suffciently long and therefore complicated route, preferably will find an alternative to this way due to performance
        repeats = repeats + 1;
        yRoute = {};
        xRoute = {};
        maze = eMaze;
        yStart = (rand() % ySize - 1) + 1; //start defaults at x = 0, can't equal ySize or 0
        xStart = 0;
        yRoute.push_back(yStart); //https://stackoverflow.com/questions/755835/how-to-add-element-to-c-array
        xRoute.push_back(0);
        int randomiseDelay = rand() % 3;
        int delay = 1;
        /*if(randomiseDelay == 3){
            delay = 3;
        }
        else{
            delay = xSize / (3 - randomiseDelay); //to delay potental turns so maze doesn't look so weird
        }*/
        int xDir = 1; //states which direction the solution will go
        int yDir = 0; //states which direction the solution will go
        steps = 0; //counts how many steps the solution to the maze will contain
        while(true){
            while (true){
                if(delay > 0){
                    delay = delay - 1;
                }
                int changeDir = rand() % 2;
                //maze = sideDraw(maze, xSize, ySize, xRoute, yRoute);
                if(changeDir == 0 && delay == 0){ //probability of changing directions
                    delay = (rand() % (xSize / 10)) + 2;
                    bool negative = rand() % 2; //deciding if the direction in the axis will be negative
                    if(xDir == 0){
                        yDir = 0;
                        if(negative == true){
                            xDir = -1;
                        }else{
                            xDir = 1;
                        }
                    }else{
                        xDir = 0;
                        if(negative == true){
                            yDir = -1;
                        }else{
                            yDir = 1;
                        }
                    }
                }
                if(xRoute[xRoute.size() - 1] + xDir >= 0 && xRoute[xRoute.size() - 1] + xDir < xSize && yRoute[yRoute.size() - 1] + yDir >= 0 && yRoute[yRoute.size() - 1] + yDir < ySize && maze[yRoute[yRoute.size() - 1] + yDir][xRoute[xRoute.size() - 1] + xDir] != 's'){
                    break; //make sure track doesn't go outside the maze or conflict with anything
                }
            }
            steps = steps + 1;
            xRoute.push_back(xRoute[xRoute.size() - 1] + xDir);
            yRoute.push_back(yRoute[yRoute.size() - 1] + yDir);
            maze[yRoute[yRoute.size() - 1]][xRoute[xRoute.size() - 1]] = '-'; //so that other functions know what the clear path is (was added later so that is the reason for the redundant vectors)
            if(xRoute[xRoute.size() - 1] == 0 || xRoute[xRoute.size() - 1] == xSize - 1 || yRoute[yRoute.size() - 1] == 0 || yRoute[yRoute.size() - 1] == ySize - 1){
                end[0] = xRoute[xRoute.size() - 1];
                end[1] = yRoute[yRoute.size() - 1];
                break;
            }

        }
        if((square(end[0] - xStart) + square(end[1] - yStart)) * 2 > square(xSize) && square(end[0] - xStart) + square(end[1] - yStart) >=  square(steps - xSize)){ //using pythagoras theorem to compare distance between the start and end point of the maze and to make path not loop back on itself too often
            break;
        }else{
            xRoute.clear();
            yRoute.clear();
        }
    }


    for(int y = 0; y < ySize; y++){
        for(int x = 0; x < xSize; x++){
            if(y == 0 || x == 0 || y == ySize - 1 || x == xSize - 1){
                if(yStart == y && x == 0){
                    maze[y][x] = 's';
                }
                else if(end[0] == x && end[1] == y){
                    maze[y][x] = 'e';
                }
                else{
                    maze[y][x] = '#';
                }
            }
                
        }
    }
    /*for(int i = 0; i < xRoute.size(); i++){ //xRoute and yRoute are the same size
        maze = sideDraw(maze, xSize, ySize, xRoute, yRoute, i);
    }*/
    maze = ensureClear(maze, xRoute, yRoute);
    //countTrack(maze, xRoute, yRoute);
    //std::cout << steps << " steps\n" << repeats << " repeats\n";
    xRoute.clear();
    yRoute.clear();
    std::cout << repeats << "\n";//to see how efficient solution finder is
    return maze;
}


std::vector<int> endLoc(std::vector<std::vector<char>> maze){ //not that efficient but easier to implement
    for(int y = 0; y < maze.size(); y++){
        for(int x = 0; x < maze[y].size(); x++){
            if(maze[y][x] == 'e'){
                return {x, y};
            }
        }
    }
    return {-1,-1}; //-1 if it can't be found
}

std::vector<int> startLoc(std::vector<std::vector<char>> maze){
    for(int y = 0; y < maze.size(); y++){
        for(int x = 0; x < maze[y].size(); x++){
            if(maze[y][x] == 's'){
                return {x, y};
            }
        }
    }
    return {-1,-1}; //-1 if it can't be found
}


std::vector<std::vector<char>> deadEndPaths(int xSize, int ySize, time_t seed = time(NULL)){
    std::vector<std::vector<char>> maze = emptyMaze(xSize, ySize);
    char displayedChar[2] = {'#', ' '};
    srand(seed);
    for(int y = 0; y < ySize; y++){
        for(int x = 0; x < xSize; x++){
            int randomNumber = rand() % 5;
            if(randomNumber > 1){
                maze[y][x] = displayedChar[0];
            }else{
                maze[y][x] = displayedChar[1];
            }
        }
    }
    return maze;
}

std::vector<std::vector<char>> mazeFusion(std::vector<std::vector<char>> mazeSol, std::vector<std::vector<char>> deadEnd){
    int ySize = mazeSol.size();
    int xSize = mazeSol[ySize - 1].size();
    std::vector<std::vector<char>> maze = emptyMaze(xSize, ySize);
    for(int y = 0; y < ySize; y++){
        for(int x = 0; x < xSize; x++){
            if(mazeSol[y][x] != ' '){
                maze[y][x] = mazeSol[y][x];
            }else{
                maze[y][x] = deadEnd[y][x];
            }
        }
    }
    return maze;

}

std::vector<std::vector<char>> mazeGeneration(int xSize, int ySize, time_t seed = time(NULL)){ //put together the maze generation, seed is just to help debugging
    std::vector<std::vector<char>> mazeSol = mazeSolution(xSize, ySize, seed);
    std::vector<std::vector<char>> deadEnd = deadEndPaths(xSize, ySize, seed);
    std::vector<std::vector<char>> maze = mazeFusion(mazeSol, deadEnd);
    return maze;
}
