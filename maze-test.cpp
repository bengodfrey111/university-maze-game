#include "rand-path.cpp"
#include <vector>


void display(std::vector<std::vector<char>> maze){ //basic display to see whats going on
    for(int y = 0; y < maze.size(); y++){
        for(int x = 0; x < maze.size(); x++){
            std::cout << maze[y][x] << ' ';
        }
        std::cout << "\n";
    }
}

bool completable(std::vector<std::vector<char>> maze){
    std::vector<int> doney; //- already covered before
    std::vector<int> donex;
    std::array<int,2> start = startLoc(maze);
    std::array<int,2> end = endLoc(maze);
    int startx = start[0];
    int starty = start[1];
    int endx = end[0];
    int endy = end[1];

    int y = starty;
    int x = startx + 1;
    doney.push_back(y);
    donex.push_back(x);
    int loop = 0;
    int stuck = 0; //how many times it go stuck in loop
    while(true){ //basically traverses the solution the maze thinks it created
        loop++;
        if(x + 1 == endx && y == endy){
            return true;
        }
        else if(x - 1 == endx && y == endy){
            return true;
        } else if(x == endx && y + 1 == endy){
            return true;
        }else if(x == endx && y - 1 == endy){
            return true;
         }
        
        if(maze[y][x + 1] == '-' && !(inArray(x + 1, y, donex, doney))){
            y = y;
            x = x + 1;
            doney.push_back(y);  
            donex.push_back(x);
        }
        else if(maze[y][x - 1] == '-' && !(inArray(x - 1, y, donex, doney))){
            y = y;
            x = x - 1;
            doney.push_back(y);
            donex.push_back(x);
        }
        else if(maze[y + 1][x] == '-' && !(inArray(x, y + 1, donex, doney))){
            y = y + 1;
            x = x;
            doney.push_back(y);
            donex.push_back(x);
        }
        else if(maze[y - 1][x] == '-' && !(inArray(x, y - 1, donex, doney))){
            y = y - 1;
            x = x;
            doney.push_back(y);
            donex.push_back(x);
        }
        
        if(loop > maze.size() * maze[maze.size() - 1].size()){ //if there are as many loops as elements in maze vector
            for(int i = 0; i < doney.size(); i++){ //incase it got stuck at a loop
                x = donex[i];
                y = doney[i];
                if(x + 1 == endx && y == endy){
                    return true;
                }
                else if(x - 1 == endx && y == endy){
                    return true;
                } else if(x == endx && y + 1 == endy){
                    return true;
                }else if(x == endx && y - 1 == endy){
                    return true;
                }
                
                if(maze[y][x + 1] == '-' && !(inArray(x + 1, y, donex, doney))){
                    y = y;
                    x = x + 1;
                    doney.push_back(y);  
                    donex.push_back(x);
                    loop = 0;
                }
                else if(maze[y][x - 1] == '-' && !(inArray(x - 1, y, donex, doney))){
                    y = y;
                    x = x - 1;
                    doney.push_back(y);
                    donex.push_back(x);
                    loop = 0;
                }
                else if(maze[y + 1][x] == '-' && !(inArray(x, y + 1, donex, doney))){
                    y = y + 1;
                    x = x;
                    doney.push_back(y);
                    donex.push_back(x);
                    loop = 0;
                }
                else if(maze[y - 1][x] == '-' && !(inArray(x, y - 1, donex, doney))){
                    y = y - 1;
                    x = x;
                    doney.push_back(y);
                    donex.push_back(x);
                    loop = 0;
                }
            }
            if(loop != 0){
                return false;
            }
        }
    }

    return false;
}

int main(){
    for(int i = 0; i < 100000; i++){
        std::vector<std::vector<char>> maze = mazeGeneration(30, 30, i);
        bool completed = completable(maze);
        if(completed == true){
            std::cout << "Maze seed " << i << " is completable\n";
        }else{
            std::cout << "Maze seed " << i << " couldn't be completed";
            throw "maze not completable";
        }
    }
    return 1;
}