#include <vector>
#include "rand-path.cpp"
#include <iostream>

class player{ //this class has been created by Ben G
    public:
    int posx;
    int posy;
    char character = 'p';
    std::string Name;
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
    char input;
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
        players.push_back(player(startx, starty));    
    }

    void Display(){ //made by David
        std::string end;
        for ( int i = 0 ; i<49 ; i++){
         std::cout << "\n";   
        }
            
        for(int y = 0; y < mazeMap.size(); y++){
            for(int x = 0; x < mazeMap[y].size(); x++){
                if(players[0].posx == x && players[0].posy == y){
                    end = end + players[0].character + ' ';
                }else if(mazeMap[y][x] == 's' || mazeMap[y][x] == 'e'){
                    end = end + mazeMap[y][x] + ' ';
                }else if(mazeMap[y][x]  == '-'){  
                end = end + ' ' + ' ';                          
                }else{
                    end = end + mazeMap[y][x] + ' ';              
                }
            }
            end = end + '\n';
        }
        std::cout << end;
    }
    void welcome() //made by emmanuel
    {
        std::cout << "\n\n\n\t\t\t    ***************************** ";
        std::cout << "\n\n\n\t\t\t    ***     THE MAZE GAME     ***";
        std::cout << "\n\n\n\t\t\t    ***************************** ";

        std::cout << "\n\n\n\t\t\t INTPUT FIRTS NAME OR USERNAME U WOULD LIKE TO BE REFERED TO IN THE GAME  ";
        std::cin >> players[0].Name;

        std::cout << "\n\n\n\t\t\t INTPUT CHARACTER TO BE REPRESENTED IN GAME";

        std::cout << "\n\n\n\t\t\t U CANNOT CHOOSE 'E' ";
        std::cin >> players[0].character;

        std::cout << " ARE U READY " << players[0].Name;
        std::cout << " ARE U CHRACTER " << players[0].character << "ON THE MAP";



        std::cout << "\n\n\n\n\n\t\t\t PRESS '0' TO START THE GAME";
        std::cout << "\n\t\t\t OR PRESS ANY KEY TO EXIT";
        std::cin >> input;

        std::cout << "\n";
        isExit();

    }
    void isExit() { //made by emmanuel
        if (input != '0') {
            exit(EXIT_SUCCESS);
        }
    }
};


int main(){
    char a;
    int xSize = 20;
    int ySize = 20;
    maze currentMaze(xSize, ySize);
    currentMaze.welcome();
    currentMaze.Display();
    std::cin >> a;
    return 0;
}