#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>

using namespace std;

float const tilesize = 96.f;
float const startingtilePos = 299.f;

float const pieceUpscale = 2.2f;
float const pieceXoffset = 13.f;
float const pieceYoffset = 6.f;




sf::Texture whiteTextures[6];
sf::Texture blackTextures[6];

//prototypes




//definitions
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


bool isPiece(int rows, int collumns){

    if(board[rows][collumns] != '.')
    return true;

    return false;

}

char CheckPiece(int rows , int collumns){

    return board[rows][collumns];

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






void drawBoard(sf::RenderWindow &window,sf::RectangleShape &tile){


    for(int i = 0; i < 8; i++){

        for(int j = 0; j < 8; j++){

            //tiles
            if( (i+j) % 2 == 0)
            
            tile.setFillColor(sf::Color::White);
            else
            tile.setFillColor(sf::Color::Black);


            tile.setPosition(sf::Vector2(tilesize * j + startingtilePos, tilesize * i));

            window.draw(tile);



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




int main() {

    //Get fullscreen size and render accordingly
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "SFML Chess", sf::Style::Fullscreen);

    //Setting view to match board
    sf::View view(sf::FloatRect(0.f, 0.f, desktop.width, desktop.height));
    window.setView(view);


    sf::RectangleShape tile(sf::Vector2f(tilesize,tilesize));
    
    loadPieceTextures();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


           
        //Grey background
        window.clear(sf::Color(65,65,65));

        drawBoard(window,tile);
            




        window.display();
    }




    }

    
    return 0;
}