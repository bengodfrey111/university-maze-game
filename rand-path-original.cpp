#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

bool inArray(int x,int y, std::vector<int> xarray, std::vector<int> yarray, int backUp = 0){ //checks if values are in an array (backUp is reducing the amount of loops)
    for(int locX = 0; locX < xarray.size() - backUp; locX++){
        for(int locY = 0; locY < yarray.size() - backUp; locY++){
            if(xarray[locX] == x && yarray[locY] == y){
                return true;
            }
        }
    }
    return false;
}

void sideDraw(char *maze, int xSize, int ySize, std::vector<int> xRoute, std::vector<int> yRoute, int xDir, int yDir){ //draws the route
    if(xDir != 0){ //draws the route
        if(yRoute[yRoute.size() - 1] + 1 > 0 && yRoute[yRoute.size() - 1] + 1 < ySize - 1 && inArray(xRoute[xRoute.size() - 1],yRoute[yRoute.size() - 1] + 1, xRoute, yRoute, 1) == false){
            *(maze + (((yRoute[yRoute.size() - 1] + 1) * xSize) + xRoute[xRoute.size() - 1])) = '#';
        }
        if(yRoute[yRoute.size() - 1] - 1 > 0 && yRoute[yRoute.size() - 1] - 1 < ySize - 1 && inArray(xRoute[xRoute.size() - 1],yRoute[yRoute.size() - 1] - 1, xRoute, yRoute, 1) == false){
            *(maze + (((yRoute[yRoute.size() - 1] - 1) * xSize) + xRoute[xRoute.size() - 1])) = '#';
        }
    }
    if(yDir != 0){
        if(xRoute[xRoute.size() - 1] + 1 > 0 && xRoute[xRoute.size() - 1] + 1 < xSize - 1 && inArray(xRoute[xRoute.size() - 1] + 1,yRoute[yRoute.size() - 1], xRoute, yRoute, 1) == false){
            *(maze + ((yRoute[yRoute.size() - 1] * xSize) + (xRoute[xRoute.size() - 1] + 1))) = '#';
        }
        if(xRoute[xRoute.size() - 1] - 1 > 0 && xRoute[xRoute.size() - 1] - 1 < xSize - 1 && inArray(xRoute[xRoute.size() - 1] - 1,yRoute[yRoute.size() - 1], xRoute, yRoute, 1) == false){
            *(maze + ((yRoute[yRoute.size() - 1] * xSize) + (xRoute[xRoute.size() - 1] - 1))) = '#';
        }
    }
}


void mazeSolution(int xSize, int ySize, char *maze){ // https://www.cplusplus.com/doc/tutorial/pointers/
    char displayedChar[4] = {'#', ' '}; //array[0] location is 1 array[1] location 2 array[3] is location 3
    srand (time(NULL)); //https://stackoverflow.com/questions/7748071/same-random-numbers-every-time-i-run-the-program

    for(int y = 0; y < ySize; y++){
        for(int x = 0; x < xSize; x++){
            *(maze + ((y * xSize) + x)) = ' '; //makes the default character as a space
        }
    }

    int yStart = (rand() % ySize - 2) + 1; //start defaults at x = 0, can't equal ySize or 0
    int end[2]; //coorodinates of where the end of the maze is (end[0] = x end[1] = y)
    std::vector< int > yRoute;
    std::vector< int > xRoute;
    yRoute.push_back(yStart); //https://stackoverflow.com/questions/755835/how-to-add-element-to-c-array
    xRoute.push_back(0);
    yRoute.push_back(yStart);
    xRoute.push_back(1);
    int xDir = 1; //states which direction the solution will go
    int yDir = 0; //states which direction the solution will go
    while(true){
        sideDraw(maze, xSize, ySize, xRoute, yRoute, xDir, yDir);
        *(maze + ((yRoute[yRoute.size() - 1] * xSize) + xRoute[xRoute.size() - 1])) = ' ';
        int changeDir = rand() % 9;
        if(changeDir == 0){ //probability of changing directions
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
        sideDraw(maze, xSize, ySize, xRoute, yRoute, xDir, yDir);

        xRoute.push_back(xRoute[xRoute.size() - 1] + xDir);
        yRoute.push_back(yRoute[yRoute.size() - 1] + yDir);
        if(xRoute[xRoute.size() - 1] == 0 || xRoute[xRoute.size() - 1] == xSize - 1 || yRoute[yRoute.size() - 1] == 0 || yRoute[yRoute.size() - 1] == ySize - 1){
            end[0] = xRoute[xRoute.size() - 1];
            end[1] = yRoute[yRoute.size() - 1];
            break;
        }

    }


    for(int y = 0; y < ySize; y++){
        for(int x = 0; x < xSize; x++){
            if(y == 0 || x == 0 || y == ySize - 1 || x == xSize - 1){
                if(yStart == y && x == 0){
                    *(maze + ((y * xSize) + x)) = 's';
                }
                else if(end[0] == x && end[1] == y){
                    *(maze + ((y * xSize) + x)) = 'e';
                }
                else{
                    *(maze + ((y * xSize) + x)) = '#'; //maze[x][y]
                }
            }
            
        }
    }
}
void testDisplay(char * maze, int xSize, int ySize){
    std::string end;
    for(int y = 0; y < ySize; y++){
        for(int x = 0; x < xSize; x++){
            end = end + *(maze + ((y * xSize) + x));
        }
        end = end + '\n';
    }
    std::cout << end;
}

int main(){
    int xSize = 50;
    int ySize = xSize;
    char maze[xSize][ySize];
    char *mazeLoc = &maze[0][0];
    mazeSolution(xSize, ySize, mazeLoc);
    testDisplay(mazeLoc, xSize, ySize);
    return 0;
}