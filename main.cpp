#include <vector>
#include "rand-path.cpp"
#include <iostream>

class player{ //this class has been created by Ben G
    public:
    int posx;
    int posy;
    player(int startx, int starty){
        posx = startx;
        posy = starty;
    }
};

class maze{ //this class has been created by Ben G apart from some specified functions
    public:
    std::vector<std::vector<char>> mazeMap;
    int startx;
    int starty;
    int endx;
    int endy;
    int xSize;
    int ySize;
    std::vector<player> players; //this will allow more than one player if we want more than one player (however its unlikely that would be implemented)
    maze(int xSize, int ySize){
        mazeMap = mazeGeneration(xSize, ySize);
        std::vector<int> start = startLoc(mazeMap);
        startx = start[0];
        starty = start[1];
        std::vector<int> end = endLoc(mazeMap);
        endx = end[0];
        endy = end[1];
        ySize = ySize;
        xSize = xSize;
        player playerInit(startx, starty);
        players.push_back(playerInit);
    }
    void testDisplay(){ //used so it helps me to visualise the maze that is been created, final one will be completed by david
        std::string end;
        for(int y = 0; y < mazeMap.size(); y++){
            for(int x = 0; x < mazeMap[y].size(); x++){
                if(players[0].posx == x && players[0].posy == y){
                    end = end + 'p';
                }else if(mazeMap[y][x] == 's' || mazeMap[y][x] == 'e'){
                    end = end + mazeMap[y][x];
                }else{
                    end = end + mazeMap[y][x] ;
                }
            }
            end = end + '\n';
        }
        std::cout << end;
    }
};

int main(){
    int xSize = 25;
    int ySize = xSize;
    maze currentMaze(xSize, ySize);
    currentMaze.testDisplay();
    return 0;
}