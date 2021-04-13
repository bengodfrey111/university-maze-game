#include <vector>
#include "rand-path.cpp"
#include <iostream>
#include <array>
#include <ncurses.h> //https://www.youtube.com/watch?v=i_reXgq-0pM

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
    bool moveToStart = false;
    bool shadow = false;
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
            if (mazeMap[randPosy][randPosx] == ' '){ //if there are no # in the position of the randomly generated positions
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
        end = '\r';
        bool displayed = false;
        bool player = false;
        for(int y = 0; y < mazeMap.size(); y++){
            for(int x = 0; x < mazeMap[y].size(); x++){
                if(isShadow(x, y) || not(shadow)){
                    player = false;
                    displayed = false;
                    for(int i = 0; i < barriers.size(); i++){
                        for(int j = 0; j < players.size(); j++){
                            if(x == barriers[i].posx && y == barriers[i].posy && not(players[0].posx == x && players[0].posy == y)){
                                displayed = true;
                            }
                        }
                    }
                    if(displayed == false){
                        for(int i = 0; i < players.size(); i++){
                            if(players[i].posx == x && players[i].posy == y){
                                end = end + players[i].character + ' ';
                                player = true;
                                break;
                            }
                        }
                        if((mazeMap[y][x] == 's' || mazeMap[y][x] == 'e') && player == false){
                            end = end + mazeMap[y][x] + ' ';
                        }else if(mazeMap[y][x]  == '-' && player == false){  
                            end = end + '-' + ' ';                     
                        }else if(player == false){
                            end = end + mazeMap[y][x] + ' ';     
                        }
                    }else{
                        end = end + 'b' + ' ';
                    }
                }else if(shadowSquare(x, y)){
                    end = end + ' ' + ' ';
                }
            }
            if(shadowLine(y)){
                end = end + '\n' + '\r';
            }
        }
        //end = end + "\nPress b for mode where when you hit # you go back to begining, press n to do nothing";
        std::cout << end;
    }

    bool isShadow(int x, int y){ //determines which characters are going to be displayed
        for(int i = 0; i < players.size(); i++){
            if(square(players[i].posx - x) + square(players[i].posy - y) < square(5)){
                return true;
            }
        }
        return false;
    }

    bool shadowSquare(int x, int y){ //helps to determine which characters are going to turn into a space
        for(int i = 0; i < players.size(); i++){
            if(square(players[i].posx - x) < square(5) && square(players[i].posy - y) < square(5)){
                return true;
            }
        }
        return false;
    }

    bool shadowLine(int y){ //helps determine where a newline will happen
        for(int i = 0; i < players.size(); i++){
            if(square(players[i].posy - y) < square(5)){
                return true;
            }
        }
        return false;
    }

    void welcome() //made by emmanuel
    {

        int playerCount;
        char input;
        char shad;
        std::cout << "\r\n\n\n\t\t\t    ***************************** ";
        std::cout << "\r\n\n\n\t\t\t    ***     THE MAZE GAME     ***";
        std::cout << "\r\n\n\n\t\t\t    ***************************** ";

        std::cout << "\r\n\n\n\t\t\t DO YOU WANT 1 OR 2 PLAYERS?  ";
        std::cin >> playerCount;
        if(playerCount != 1){
            players.push_back(player(startx, starty));
            playerCount = 2;
        }

        std::cout << "\r\n\n\n\t\t\t TYPE 1 IF YOU WANT A SHADOW OR ANYTHING ELSE IF YOU DON'T  ";
        std::cin >> shad;
        if(shad == '1'){
            shadow = true;
        }

        for(int i = 0; i < playerCount; i++){

            //std::cout << "\n\n\n\t\t\t INTPUT FIRTS NAME OR USERNAME PLAYER 1 WOULD LIKE TO BE REFERED TO IN THE GAME  ";
            //std::cin >> players[i].name;

            std::cout << "\r\n\n\n\t\t\t INTPUT CHARACTER TO BE REPRESENTED IN GAME";

            std::cout << "\r\n\n\n\t\t\t U CANNOT CHOOSE '#' AND 'b' ";
            std::cin >> players[i].character;

            std::cout << "\n\r\t\t\t ARE U READY " << players[i].name;
            std::cout << " ARE U CHRACTER " << players[i].character << "ON THE MAP";

        }

        std::cout << "\r\n\n\n\n\n\t\t\t PRESS '0' TO START THE GAME";
        std::cout << "\r\n\t\t\t OR PRESS ANY KEY TO EXIT";
        std::cout << "\n\r\t\t\t USE KEYS wasd TO CONTROL PLAYER 1 AND uhjk TO CONTROL PLAYER 2\n\r\t\t\t PRESS KEY IN GAME b TO GO TO BEGINING WHEN PLAYER HITS # AND PRESS n TO DO NOTHING ";
        std::cin >> input;
        if(input != '0'){
            Exit();
        }
        std::cout << "\n";

    }

        void doMove(std::string dir, int p) { //Benjamin A
        //Do move
        if(p + 1 <= players.size()){
            if (dir == "LEFT") {
            players[p].posx--;
            } else if (dir == "RIGHT") {
            players[p].posx++;
            } else if (dir == "UP") {
            players[p].posy--;
            } else if (dir == "DOWN") {
            players[p].posy++;
            }
            //Checking if movement is allowed
            if (players[p].posx < 0 || players[0].posy < 0 ||
            players[p].posx >= xSize || players[0].posy >= ySize ||
            mazeMap[players[p].posy][players[p].posx] == '#') {
            if (!moveToStart) {
            //Movement is taken back
            if (dir == "LEFT") {
            players[p].posx++;
            } else if (dir == "RIGHT") {
            players[p].posx--;
            } else if (dir == "UP") {
            players[p].posy++;
            } else if (dir == "DOWN") {
            players[p].posy--;
            }
            } else {
            //Going to start
            players[p].posx = startx;
            players[p].posy = starty;
            }
            }
        }
    }

    void mode(char c){ //made by Ben A
        if (c == 'b') {
            std::cout << "Mode set to: start from beginning if wall\n";
            moveToStart = true;
        } else if (c == 'n') {
            std::cout << "Mode set to: don't move if wall\n";
            moveToStart = false;
        }
    }

    void move(char c){ //made by Ben A
        if (c == 'a') {
            doMove("LEFT", 0);
        } else if (c == 'd') {
            doMove("RIGHT", 0);
        } else if (c == 'w') {
            doMove("UP", 0);
        } else if (c == 's') {
            doMove("DOWN", 0);
        }
        if (c == 'h') {
            doMove("LEFT", 1);
        } else if (c == 'k') {
            doMove("RIGHT", 1);
        } else if (c == 'u') {
            doMove("UP", 1);
        } else if (c == 'j') {
            doMove("DOWN", 1);
        }

    }

    bool end(){
        for(int i = 0; i < players.size(); i++){
            if(players[i].posx == endx && players[i].posy == endy){
                return true;
            }
        }
        return false;
    }

    void reset(){
        players = {};
        barriers = {};
        ySize = ySize * 1.3; //just copied from the constructor
        xSize = xSize * 1.3;
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
            if (mazeMap[randPosy][randPosx] == ' '){ //if there are no # in the position of the randomly generated positions
                break ;//continue past the break else keep generating positions
            }
        }
            barriers.push_back(barrier(randPosx,randPosy));
        } //end davids code
    }

    void Exit() { //made by emmanuel
        exit(EXIT_SUCCESS);
    }

};


int main(){
    char a;
    int xSize = 20;
    int ySize = 20;
    maze currentMaze(xSize, ySize);
    currentMaze.welcome();
    while(true){
        currentMaze.display();
        char key_press;
        initscr();
        noecho();
        while((key_press = getch()) != '#'){
            currentMaze.move(key_press);
            currentMaze.mode(key_press);
            currentMaze.barrierskip();
            currentMaze.display();
            if(currentMaze.end()){
                currentMaze.reset();
                break;
            }
        }
    }
    endwin();
    return 0;
}