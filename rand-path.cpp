#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>


bool inArray(int x,int y, std::vector<int> xarray, std::vector<int> yarray, int backUp = 0){ //checks if values are in an array (backUp is reducing the amount of loops)
    for(int i = 0; i < xarray.size() - backUp; i++){
        if(xarray[i] == x && yarray[i] == y){
            return true;
        }
    }
    return false;
}

std::vector<std::vector<char>> sideDraw(std::vector<std::vector<char>> maze, int xSize, int ySize, std::vector<int> xRoute, std::vector<int> yRoute, int i = -1){ //draws the route
    if(i == -1){
        i = xRoute.size() - 1;
    }
    //draws the route
    if(yRoute[i] + 1 > 0 && yRoute[i] + 1 < ySize - 1 && inArray(xRoute[i],yRoute[i] + 1, xRoute, yRoute, 1) == false){
        maze[xRoute[i]][yRoute[i] + 1] = '#';
    }
    if(yRoute[i] - 1 > 0 && yRoute[i] - 1 < ySize - 1 && inArray(xRoute[i],yRoute[i] - 1, xRoute, yRoute, 1) == false){
        maze[xRoute[i]][yRoute[i] - 1] = '#';
    }
    if(xRoute[i] + 1 > 0 && xRoute[i] + 1 < xSize - 1 && inArray(xRoute[i] + 1,yRoute[i], xRoute, yRoute, 1) == false){
        maze[xRoute[i] + 1][yRoute[i]] = '#';
    }
    if(xRoute[i] - 1 > 0 && xRoute[i] - 1 < xSize - 1 && inArray(xRoute[i] - 1,yRoute[yRoute.size() - 1], xRoute, yRoute, 1) == false){
        maze[xRoute[i] - 1][yRoute[i]] = '#';
    }
    return maze;
}

std::vector<std::vector<char>> ensureClear(std::vector<std::vector<char>> maze, std::vector<int> xRoute, std::vector<int> yRoute){ //ensures there is a clear path
    for(int i = 0; i < xRoute.size(); i++){//xRoute is the same size as yRoute
        if(maze[xRoute[i]][yRoute[i]] != 'e' && maze[xRoute[i]][yRoute[i]] != 's'){
            maze[xRoute[i]][yRoute[i]] = ' ';
        }
    }
    return maze;
}

std::vector<std::vector<char>> emptyMaze(int xSize, int ySize){ //creates an empty maze
    std::vector<std::vector<char>> empty;
    for(int y = 0; y < xSize; y++){
        empty.push_back({});
        for(int x = 0; x < ySize; x++){
            empty[y].push_back(' ');
        }
    }
    return empty;
}

void testDisplay(std::vector<std::vector<char>> maze){
    std::string end;
    for(int x = 0; x < maze.size(); x++){
        for(int y = 0; y < maze[x].size(); y++){
            end = end + maze[x][y];
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


std::vector<std::vector<char>> mazeSolution(int xSize, int ySize){
    int yStart;
    std::vector<std::vector<char>> maze;
    int end[2]; //coorodinates of where the end of the maze is (end[0] = x end[1] = y)
    std::vector< int > yRoute;
    std::vector< int > xRoute;
    int steps;
    srand (time(NULL)); //https://stackoverflow.com/questions/7748071/same-random-numbers-every-time-i-run-the-program
    char displayedChar[2] = {'#', ' '}; //array[0] location is 1 array[1] location 2 array[3] is location 3
    int repeats = -1; //so I can see the amount of failed mazes
    while(true){ //repeats until there is a suffciently long and therefore complicated route, preferably will find an alternative to this way due to performance
        repeats = repeats + 1;
        yRoute = {};
        xRoute = {};
        maze = emptyMaze(xSize, ySize);
        yStart = (rand() % ySize - 1) + 1; //start defaults at x = 0, can't equal ySize or 0
        yRoute.push_back(yStart); //https://stackoverflow.com/questions/755835/how-to-add-element-to-c-array
        xRoute.push_back(0);
        yRoute.push_back(yStart);
        xRoute.push_back(1);
        int randomiseDelay = rand() % 3;
        int delay = 0;
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
                int changeDir = rand() % 3;
                maze = sideDraw(maze, xSize, ySize, xRoute, yRoute);
                if(changeDir == 0 && delay == 0){ //probability of changing directions
                    delay = 0;
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
                if(xRoute[xRoute.size() - 1] + xDir >= 0 && xRoute[xRoute.size() - 1] + xDir < xSize && yRoute[yRoute.size() - 1] + yDir >= 0 && yRoute[yRoute.size() - 1] + yDir < ySize){
                    break; //make sure track doesn't go outside the maze
                }
            }
            steps = steps + 1;
            xRoute.push_back(xRoute[xRoute.size() - 1] + xDir);
            yRoute.push_back(yRoute[yRoute.size() - 1] + yDir);
            if(xRoute[xRoute.size() - 1] == 0 || xRoute[xRoute.size() - 1] == xSize - 1 || yRoute[yRoute.size() - 1] == 0 || yRoute[yRoute.size() - 1] == ySize - 1){
                end[0] = xRoute[xRoute.size() - 1];
                end[1] = yRoute[yRoute.size() - 1];
                break;
            }

        }
        if(steps > xSize){
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
                    maze[x][y] = 's';
                }
                else if(end[0] == x && end[1] == y){
                    maze[x][y] = 'e';
                }
                else{
                    maze[x][y] = '#'; //maze[x][y]
                }
            }
                
        }
    }
    /*for(int i = 0; i < xRoute.size(); i++){ //xRoute and yRoute are the same size
        maze = sideDraw(maze, xSize, ySize, xRoute, yRoute, i);
    }*/
    maze = ensureClear(maze, xRoute, yRoute);
    countTrack(maze, xRoute, yRoute);
    std::cout << steps << " steps\n" << repeats << " repeats\n";
    return maze;
}


int main(){
    std::cout << time(NULL) << '\n';
    int xSize = 10;
    int ySize = xSize;
    int loop = -1;
    while(true){
        loop = loop + 1;
        std::vector<std::vector<char>> maze = mazeSolution(xSize, ySize);
        std::cout << '\n' << loop << '\n';
    }
    //testDisplay(maze);
    return 0;
}