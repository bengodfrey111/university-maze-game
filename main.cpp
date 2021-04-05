#include <vector>
#include "rand-path.cpp"
#include <iostream>
#include <array>
#include<ncurses.h>

class barrier{ //this class has been created by david
   public:
   int posx;
   int posy;
   barrier(int startx, int starty){
       posx = startx;
       posy = starty;
   }
};

class player{ //this class has been created by Ben G
    public:
    int posx;
    int posy;
    char character = 'p'; //defaults at p since I don't need to run welcome in that case
    std::string name;
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
    std::vector<barrier> barriers;
    char input;
    bool moveToStart = false;
    maze(int _xSize, int _ySize){
        ySize = _ySize;
        xSize = _xSize;
        mazeMap = mazeGeneration(xSize, ySize);
        std::array<int, 2> start = startLoc(mazeMap);
        startx = start[0];
        starty = start[1];
        std::array<int,2> end = endLoc(mazeMap);
        endx = end[0];
        endy = end[1];
        players.push_back(player(startx, starty));
        srand(time(NULL));//start Davids code
        int randPosx;
        int randPosy;
        for(int i = 0; i < 10; i++){
            while(true){
            randPosx = (rand() % (xSize - 1)) + 1;//generates random number between and x size
            randPosy = (rand() % (ySize - 1)) + 1;
            if (mazeMap[randPosx][randPosy] != '#'){ //if there are no # in the position of the randomly generated positions
                break ;//continue past the break else keep generating positions
            }
        }
            barriers.push_back(barrier(randPosx,randPosy));
        } //end davids code

    }


    void barrierskip(){// maze class Made by David
            for(int i = 0; i < barriers.size(); i++){//initialises the number of barriers in the maze
                for(int j = 0; j < players.size(); j++){//number of players in maze
                if(players[j].posx == barriers[i].posx && players[j].posy == barriers[i].posy){ //if any of j number of players x&&y
                                                                        //positions is the same as any of the i number barriers x&&y              
                if( i + 1 == barriers.size()){
                    players[j].posx = barriers[0].posx;
                    players[j].posy = barriers[0].posy;
                }else{
                    players[j].posx = barriers[i+1].posx;
                    players[j].posy = barriers[i+1].posy;
                }
                }
                }
            }
    }
    void display(){ //made by David
        std::string end;
        for ( int i = 0 ; i<49 ; i++){
         std::cout << "\n";   
        }
        int displayed = false;
        for(int y = 0; y < mazeMap.size(); y++){
            for(int x = 0; x < mazeMap[y].size(); x++){
                displayed = false;
                for(int i = 0; i < barriers.size(); i++){
                    if(x == barriers[i].posx && y == barriers[i].posy && not(players[0].posx == x && players[0].posy == y)){
                        displayed = true;
                        end = end + 'b' + ' ';
                    }
                }
                if(displayed == false){
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
            }
            end = end + '\n' + '\r';
        }
        std::cout << end;
    }
    void welcome() //made by emmanuel
    {
        std::cout << "\n\n\n\t\t\t    ***************************** ";
        std::cout << "\n\n\n\t\t\t    ***     THE MAZE GAME     ***";
        std::cout << "\n\n\n\t\t\t    ***************************** ";

        std::cout << "\n\n\n\t\t\t INTPUT FIRTS NAME OR USERNAME U WOULD LIKE TO BE REFERED TO IN THE GAME  ";
        std::cin >> players[0].name;

        std::cout << "\n\n\n\t\t\t INTPUT CHARACTER TO BE REPRESENTED IN GAME";

        std::cout << "\n\n\n\t\t\t U CANNOT CHOOSE 'E' ";
        std::cin >> players[0].character;

        std::cout << " ARE U READY " << players[0].name;
        std::cout << " ARE U CHRACTER " << players[0].character << "ON THE MAP";



        std::cout << "\n\n\n\n\n\t\t\t PRESS '0' TO START THE GAME";
        std::cout << "\n\t\t\t OR PRESS ANY KEY TO EXIT";
        std::cin >> input;

        std::cout << "\n";
        isExit();

    }

        void doMove(std::string dir) { //Benjamin A
        //Do move
        if (dir == "LEFT") {
        players[0].posx--;
        } else if (dir == "RIGHT") {
        players[0].posx++;
        } else if (dir == "UP") {
        players[0].posy--;
        } else if (dir == "DOWN") {
        players[0].posy++;
        }
        //Checking if movement is allowed
        if (players[0].posx < 0 || players[0].posy < 0 ||
        players[0].posx >= xSize || players[0].posy >= ySize ||
        mazeMap[players[0].posy][players[0].posx] == '#') {
        if (!moveToStart) {
        //Movement is taken back
        if (dir == "LEFT") {
        players[0].posx++;
        } else if (dir == "RIGHT") {
        players[0].posx--;
        } else if (dir == "UP") {
        players[0].posy++;
        } else if (dir == "DOWN") {
        players[0].posy--;
        }
        } else {
        //Going to start
        players[0].posx = startx;
        players[0].posy = starty;
        }
        }
    }

    void mode(char c){ //made by Ben A
        if (c == 's') {
            std::cout << "Mode set to: start from beginning if wall\n";
            moveToStart = true;
        } else if (c == 'n') {
            std::cout << "Mode set to: don't move if wall\n";
            moveToStart = false;
        }
    }

    void move(char c){ //made by Ben A
        if (c == 'e') {
            input = 0;
            isExit();
        } else {
            if (c == 'a') {
                doMove("LEFT");
            } else if (c == 'd') {
                doMove("RIGHT");
            } else if (c == 'w') {
                doMove("UP");
            } else if (c == 's') {
                doMove("DOWN");
            }
        }
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
    //currentMaze.welcome();
    char key_press;
    initscr();
    noecho();
    currentMaze.display();
    while((key_press = getch()) != '#'){
        currentMaze.move(key_press);
        currentMaze.barrierskip();
        currentMaze.display();
    }
    std::cin >> a;
    return 0;
}