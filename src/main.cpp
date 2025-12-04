#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>

using namespace std;

float const tilesize = 96.f;
float const startingtilePos = 299.f;

float const pieceUpscale = 2.2f;
float const pieceXoffset = 13.f;
float const pieceYoffset = 6.f;

int state = 0; //0 for piece selection 1 for move selection 
bool whiteTurn = true;


bool highlightOn = false;
bool dangerHighlightOn = false;

int selectedRow, selectedCol;
int selectedRow1, selectedCol1;


sf::Texture whiteTextures[6];
sf::Texture blackTextures[6];

//prototypes
bool isValidMoves(char piece, int row, int col);
bool isValidMovesforCheck(char piece, int row, int col);
bool isValidPawnMove(int row, int col);
bool isValidKnightMove(int row, int col);
bool isValidBishopMove(int row, int col);
bool isValidQueenMove(int row, int col);
bool isValidKingMove(int row, int col);
void Move(int row, int col);
bool isPiece(int rows, int collumns);
char CheckPiece(int rows , int collumns);
bool isTurn(char piece);
bool isFriendPiece(int x, int y);
bool isEnemyPiece(int x, int y);
void loadPieceTextures();
sf::Texture& findTexture(char piece);
void drawBoard(sf::RenderWindow &window,sf::RectangleShape &tile,sf::RectangleShape &highlight, sf::RectangleShape &danghighlight);
void drawCheckHighlight(sf::RectangleShape &danghighlight);



char board[8][8] = {
    {'r','n','b','q','k','b','n','r'},  
    {'p','p','p','p','p','p','p','p'},
    {'.','.','.','.','.','.','.','.'},  
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'P','P','P','P','P','P','P','P'},  
    {'R','N','B','Q','K','B','N','R'}  
};

int main() {

    char currentPiece;
   

    //Get fullscreen size and render accordingly
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "SFML Chess", sf::Style::Fullscreen);

    //Setting view to match board
    sf::View view(sf::FloatRect(0.f, 0.f, desktop.width, desktop.height));
    window.setView(view);


    //chess tiles
    sf::RectangleShape tile(sf::Vector2f(tilesize,tilesize));

    sf::RectangleShape highlight(sf::Vector2(tilesize,tilesize));
    highlight.setFillColor(sf::Color::Transparent);
    highlight.setOutlineThickness(-3.f);
    highlight.setOutlineColor(sf::Color::Green);

    sf::RectangleShape danghighlight(sf::Vector2(tilesize,tilesize));
    danghighlight.setFillColor(sf::Color::Transparent);
    danghighlight.setOutlineThickness(-3.f);
    danghighlight.setOutlineColor(sf::Color::Red);
    
    loadPieceTextures();

    //main loop
    while (window.isOpen()) {
        sf::Event event;



        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                sf::Vector2u WindowSize = window.getSize();


                if(event.mouseButton.x > startingtilePos && event.mouseButton.y < startingtilePos + tilesize * 8){
                int col = (event.mouseButton.x - startingtilePos) / tilesize;
                int row = event.mouseButton.y / tilesize;

                    if(state == 0){
                        highlightOn = true;
                        highlight.setPosition(sf::Vector2f(tilesize * col + startingtilePos, tilesize * row));
                       
                        if(isPiece(row,col)){
                            if(isTurn(CheckPiece(row,col))){

                             currentPiece = CheckPiece(row,col);
                             selectedRow = row;
                             selectedCol = col;
                             state = 1;
                                cout << "row " << row << "col " << col << endl;
                            }  
                        }
                    }
                    else if (state == 1){

                        if(isValidMoves(currentPiece,row,col)){
                            Move(row,col);
                            whiteTurn = !whiteTurn;
                            drawCheckHighlight(danghighlight);
                        }
                        highlightOn = false;
                        state = 0;
                    }
                }
            }


           
        //Grey background
        window.clear(sf::Color(65,65,65));
        drawBoard(window,tile,highlight,danghighlight);
        window.display();
    }




    }

    
    return 0;
}




bool isPiece(int rows, int collumns){

    if(board[rows][collumns] != '.')
    return true;

    return false;

}

char CheckPiece(int rows , int collumns){

    return board[rows][collumns];

}

bool isTurn(char piece){

    bool isValid = false;

    if(piece == 'P' || piece == 'N' || piece == 'B' || piece == 'R' || piece == 'Q' || piece == 'K'){
        if(whiteTurn)
        isValid = true;

    }

    else if(piece == 'p' || piece == 'n' || piece == 'b' || piece == 'r' || piece == 'q' || piece == 'k'){
        if(!whiteTurn)
        isValid = true;
    }

    return isValid;

}

bool isFriendPiece(int x, int y){
    bool isvalid = false;
    if(whiteTurn){
        if(board[x][y] == 'P' || board[x][y] == 'N'  || board[x][y] == 'B' ||  board[x][y] == 'R' ||  board[x][y] == 'Q' ||  board[x][y] == 'K')
         isvalid = true;
        
      

    }
    else{
        if(board[x][y] == 'p' || board[x][y] == 'n'  || board[x][y] == 'b' ||  board[x][y] == 'r' ||  board[x][y] == 'q' ||  board[x][y] == 'k')
        isvalid = true;

    }

    return isvalid;

}

bool isEnemyPiece(int x, int y){
    bool isvalid = false;
    if(whiteTurn){
       
        if(board[x][y] == 'p' || board[x][y] == 'n'  || board[x][y] == 'b' ||  board[x][y] == 'r' ||  board[x][y] == 'q' ||  board[x][y] == 'k')
        isvalid = true;

    }
    else{

        if(board[x][y] == 'P' || board[x][y] == 'N'  || board[x][y] == 'B' ||  board[x][y] == 'R' ||  board[x][y] == 'Q' ||  board[x][y] == 'K')
        isvalid = true;
        
    }
    
  

    return isvalid;

}





void loadPieceTextures(){

    if (!whiteTextures[0].loadFromFile("assets/sprites/white_pawn.png")) {
    std::cout << "Failed to load wr.png\n";
}
    whiteTextures[0].loadFromFile("assets/sprites/white_pawn.png");
    whiteTextures[1].loadFromFile("assets/sprites/white_knight.png");
    whiteTextures[2].loadFromFile("assets/sprites/white_bishop.png");
    whiteTextures[3].loadFromFile("assets/sprites/white_rook.png");
    whiteTextures[4].loadFromFile("assets/sprites/white_queen.png");
    whiteTextures[5].loadFromFile("assets/sprites/white_king.png");

    blackTextures[0].loadFromFile("assets/sprites/black_pawn.png");
    blackTextures[1].loadFromFile("assets/sprites/black_knight.png");
    blackTextures[2].loadFromFile("assets/sprites/black_bishop.png");
    blackTextures[3].loadFromFile("assets/sprites/black_rook.png");
    blackTextures[4].loadFromFile("assets/sprites/black_queen.png");
    blackTextures[5].loadFromFile("assets/sprites/black_king.png");

}

sf::Texture& findTexture(char piece){

    switch(piece){

        case 'P':
        return whiteTextures[0];
        case 'N':
        return whiteTextures[1];
        case 'B':
        return whiteTextures[2];
        case 'R':
        return whiteTextures[3];
        case 'Q':
        return whiteTextures[4];
        case 'K':
        return whiteTextures[5];
     

        case 'p':
        return blackTextures[0];
        case 'n':
        return blackTextures[1];
        case 'b':
        return blackTextures[2];
        case 'r':
        return blackTextures[3];
        case 'q':
        return blackTextures[4];
        case 'k':
        return blackTextures[5];
    }
}

void drawBoard(sf::RenderWindow &window,sf::RectangleShape &tile,sf::RectangleShape &highlight, sf::RectangleShape &danghighlight){


    for(int i = 0; i < 8; i++){

        for(int j = 0; j < 8; j++){

            //tiles
            if( (i+j) % 2 == 0)
            
            tile.setFillColor(sf::Color::White);
            else
            tile.setFillColor(sf::Color::Black);


            tile.setPosition(sf::Vector2(tilesize * j + startingtilePos, tilesize * i));

           
            window.draw(tile);

            if(highlightOn)
            window.draw(highlight);

            if(dangerHighlightOn)
            window.draw(danghighlight);


            //pieces
            if(isPiece(i,j)){
                char piece = CheckPiece(i,j);
                
                sf::Sprite pieceSprite;
                pieceSprite.setTexture(findTexture(piece));
                pieceSprite.setScale(pieceUpscale,pieceUpscale);
                pieceSprite.setPosition(sf::Vector2(tilesize * j + startingtilePos + pieceXoffset, tilesize * i + pieceYoffset));

                window.draw(pieceSprite);
            }

        }
    }



}

void drawCheckHighlight(sf::RectangleShape &danghighlight){

     dangerHighlightOn = false;

       

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

           if(whiteTurn && board[i][j] == 'K'){

            selectedRow1 = i;
             selectedCol1 = j;
            

           }
           else if(!whiteTurn && board[i][j] == 'k'){

            selectedRow1 = i;
             selectedCol1 = j;
            
           }


        }
    }



    int temp1 = selectedRow;
    int temp2 = selectedCol;


  

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(isEnemyPiece(i,j)){
                selectedRow = i;
                selectedCol = j;
               if(isValidMovesforCheck(board[i][j],selectedRow1,selectedCol1)) {
                
                danghighlight.setPosition(sf::Vector2f(tilesize * selectedCol1 + startingtilePos , tilesize * selectedRow1 ));

                cout << "King is threatened by piece " << board[i][j]
                         << " at (" << i << "," << j << ")" << endl;

                dangerHighlightOn = true;

               }

            }

        }
    }


    selectedRow = temp1;
    selectedCol = temp2;
   
   

}

void Move(int row, int col){
    char temp;
    if(isEnemyPiece(row,col))
    temp = '.';
    else
    temp = board[row][col];

    board[row][col] = board[selectedRow][selectedCol];
    board[selectedRow][selectedCol] = temp;

}



bool isValidPawnMove(int row, int col){

bool isvalid = false;


 int yDiff = row - selectedRow;
 int xDiff = col - selectedCol;

 if(col == selectedCol && !isEnemyPiece(row,col)){
    
    if(whiteTurn){

        if(yDiff == -2 && selectedRow == 6)
        isvalid = true;
        else if(yDiff == -1){
        isvalid = true;
    }
}
    else{
        if(yDiff == 2 && selectedRow == 1)
        isvalid = true;
        else if(yDiff == 1){
        isvalid = true;

     }

    }


}

else{

    if(whiteTurn && (xDiff == 1 && yDiff == -1 || xDiff == -1 && yDiff == -1)){
        if(isEnemyPiece(row,col))
            isvalid = true;
        }

    else if(!whiteTurn && (xDiff == -1 && yDiff == 1 || xDiff == 1 && yDiff == 1)){
        if(isEnemyPiece(row,col))
            isvalid = true;
    }




}


return isvalid;

}

bool isValidPawnMoveForCheck(char pawn,int row, int col){

bool isvalid = false;


 int yDiff = row - selectedRow;
 int xDiff = col - selectedCol;

   if(pawn == 'P') {
    if((xDiff == 1 && yDiff == -1) || (xDiff == -1 && yDiff == -1))
        isvalid = true;
    }


    else if(pawn == 'p') {
        if((xDiff == 1 && yDiff == 1) || (xDiff == -1 && yDiff == 1))
         isvalid = true;
    }


return isvalid;

}

bool isValidKnightMove(int row, int col){

    bool isValid = false;

    int yDiff = row - selectedRow;
    int xDiff = col - selectedCol;

    if((abs(xDiff) == 2 && abs(yDiff) == 1) || (abs(yDiff) == 2 && abs(xDiff) == 1))
        isValid = true;

    



    return isValid;

}


bool isValidBishopMove(int row, int col){
   
    bool isValid = true;


    if (row < 0 || row > 7 || col < 0 || col > 7)
    return false;




    int yDiff = row - selectedRow;
    int xDiff = col - selectedCol;
    
    if(abs(yDiff) != abs(xDiff))
        isValid = false;


    int xIncrement = 1;
    int yIncrement = 1;

    if(xDiff < 0)
        xIncrement = -1;
    if(yDiff < 0)
        yIncrement = -1;

    int i = selectedRow + yIncrement;
    int j = selectedCol + xIncrement;

        while (i != row && j != col) {
            if (i < 0 || i > 7 || j < 0 || j > 7)
            break;
        if (isPiece(i, j))
            isValid = false; 
        i += yIncrement;
        j += xIncrement;
    }

  


    return isValid;
}



bool isValidRookMove(int row, int col){
   
    bool isValid = true;


    if (row < 0 || row > 7 || col < 0 || col > 7)
    return false;



    int yDiff = row - selectedRow;
    int xDiff = col - selectedCol;
    
    if((row != selectedRow) && (col != selectedCol))
        isValid = false;


    int xIncrement = 1;
    int yIncrement = 1;


    if(xDiff == 0)
        xIncrement = 0;
    if(yDiff == 0)
        yIncrement = 0;
    if(xDiff < 0)
        xIncrement = -1;
    if(yDiff < 0)
        yIncrement = -1;

    int i = selectedRow + yIncrement;
    int j = selectedCol + xIncrement;

        while (i != row && j != col) {

            if (i < 0 || i > 7 || j < 0 || j > 7)
            break;

        if (isPiece(i, j))
            isValid = false; 
        i += yIncrement;
        j += xIncrement;
    }

  


    return isValid;
}


bool isValidQueenMove(int row, int col) {
    bool isValid = true;


    if (row < 0 || row > 7 || col < 0 || col > 7)
    return false;




    int yDiff = row - selectedRow;
    int xDiff = col - selectedCol;

    
    if (!((row == selectedRow) || (col == selectedCol) || (abs(yDiff) == abs(xDiff))))
        isValid = false;

    int xIncrement = 1;
    int yIncrement = 1;

    
    if (xDiff == 0)
        xIncrement = 0;
    if (yDiff == 0)
        yIncrement = 0;
    if (xDiff < 0)
        xIncrement = -1;
    if (yDiff < 0)
        yIncrement = -1;

    int i = selectedRow + yIncrement;
    int j = selectedCol + xIncrement;

    while (i != row || j != col) {
            if (i < 0 || i > 7 || j < 0 || j > 7)
            break;
        if (isPiece(i, j))
            isValid = false;
        i += yIncrement;
        j += xIncrement;
    }

    return isValid;
}

bool isValidKingMove(int row, int col){

    bool isValid = true;


    int yDiff = row - selectedRow;
    int xDiff = col - selectedCol;

    if((abs(xDiff) == 1 && abs(yDiff) == 0) || (abs(yDiff) == 1 && abs(xDiff) == 0) || (abs(yDiff) == 1 && abs(xDiff) == 1))
        isValid = true;

    

    return isValid;



}




bool isValidMoves(char piece, int row, int col){

    bool isvalid;

  

    if(piece == 'P' || piece == 'p')
    isvalid = isValidPawnMove(row,col);

    if(piece == 'N' || piece == 'n')
    isvalid = isValidKnightMove(row,col);

    if(piece == 'B' || piece == 'b')
    isvalid = isValidBishopMove(row,col);

    if(piece == 'R' || piece == 'r')
    isvalid = isValidRookMove(row,col);

    if(piece == 'Q' || piece == 'q')
     isvalid = isValidQueenMove(row,col);

    if(piece == 'K' || piece == 'k')
     isvalid = isValidKingMove(row,col);


    if(row == selectedRow && col == selectedCol)
        isvalid = false;

    if(isFriendPiece(row,col))
        isvalid = false;

    return isvalid;

}


bool isValidMovesforCheck(char piece, int row, int col){

    bool isvalid;

  

    if(piece == 'P' || piece == 'p')
    isvalid = isValidPawnMoveForCheck(piece,row,col);

    if(piece == 'N' || piece == 'n')
    isvalid = isValidKnightMove(row,col);

    if(piece == 'B' || piece == 'b')
    isvalid = isValidBishopMove(row,col);

    if(piece == 'R' || piece == 'r')
    isvalid = isValidRookMove(row,col);

    if(piece == 'Q' || piece == 'q')
     isvalid = isValidQueenMove(row,col);

    if(piece == 'K' || piece == 'k')
     isvalid = false;

    if(row == selectedRow && col == selectedCol)
        isvalid = false;

  

    return isvalid;

}