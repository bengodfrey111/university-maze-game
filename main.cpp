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
        bool displayed = false;
        bool player = false;
        for(int y = 0; y < mazeMap.size(); y++){
            for(int x = 0; x < mazeMap[y].size(); x++){
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
                        end = end + ' ' + ' ';                     
                    }else if(player == false){
                        end = end + mazeMap[y][x] + ' ';     
                     }
                }else{
                    end = end + 'b' + ' ';
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

    void mode(){ //made by Ben A
        std::cout << "Type s to set start from beginning if wall and type n to don't move if wall\n";
        char c;
        std::cin >> c;
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
    currentMaze.display();
    initscr();
    noecho();
    while((key_press = getch()) != '#'){
        currentMaze.move(key_press);
        currentMaze.barrierskip();
        currentMaze.display();
    }
    endwin();
    return 0;
}