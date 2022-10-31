#include "board.h"

#define TESTING_IMAGE_SIZE 1024

board::board( sf::RenderWindow *passWindow, std::string pathToTexture, int boardLength, int boardHeight, int padding)
{
    this->aWindow = passWindow;
    this->setTileTexture(pathToTexture);
    this->height = boardHeight;
    this->length = boardLength;
    this->padding = padding; // in px

    auto windowDimension = aWindow->getSize();

    float scaleX, scaleY; // windowSize - padding * 2 is to ensure tile only in the "play space"
    // divided by number of tile, then multiplied by th
    scaleX = (windowDimension.x - (padding*2))/(float)this->length*( this->tileScaleFloat / (float) windowDimension.x);
    scaleY = (windowDimension.y - (padding*2))/(float)this->height*( this->tileScaleFloat / (float) windowDimension.y);

    for (int x = 0; x < this->length; x++)
    {
        gameState.push_back(std::vector<boardtile>());
        for (int y = 0; y < this->height; y++)
        {
            int positionX, positionY;
            positionX = (windowDimension.x -(padding*2)) / length * x + padding;
            positionY = (windowDimension.y -(padding*2)) / height * y + padding;

            gameState[x].push_back(boardtile(x, y));

            gameState[x][y].tileSprite.setTexture(this->tileTexture);
            gameState[x][y].tileSprite.setPosition(positionX, positionY);
            gameState[x][y].tileSprite.setScale(scaleX, scaleY);
        }
    }
}


void board::setTileTexture(std::string pathToTexture)
{
    auto windowDimension = this->aWindow->getSize();
    if (!tileTexture.loadFromFile(pathToTexture, sf::IntRect(0, 0, windowDimension.x, windowDimension.y))) // arguments for this are
        //("string name", sf::IntRect(first corner of file (0 for full file), 0 (second corner), size of file, size of file))
    {
         if (this->setTileTexture())
         {
            return;
         }
         throw std::runtime_error("Bad tile texture path.");
    }
}
bool board::setTileTexture()
{
    auto windowDimension = this->aWindow->getSize();
    if (!tileTexture.loadFromFile("/tmp/tiletexture.png", sf::IntRect(0, 0, windowDimension.x, windowDimension.y)))
    {
         throw std::runtime_error("Bad tile texture path AND missing default missing texture.");
    }
    return true;
}

void board::clearBoardHighlights()
{
    for (int x = 0; x < this->length; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            gameState[x][y].setHighlightDefault();
        }
    }
}

void board::draw()
{
    for (int x = 0; x < this->length; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            this->gameState[x][y].draw(aWindow);
        }
    }
}
boardtile *board::mouseClick(int xPos, int yPos) // this function should maybe return a square or something?
// so that other libs can use it better
{
    this->clearBoardHighlights();
    // finding closest square
    // not sure if I want this to select exact square or just closest
    // exact, click must be within the bounds of a square
    auto windowSize = this->aWindow->getSize();
    int tileLength = ((windowSize.x - this->padding*2) / (this->length));
    int tileHeight = ((windowSize.y - this->padding*2) / (this->height));
    for (int x = 0; x < gameState.size(); x++)
    {
        for (int y = 0; y < gameState[x].size(); y++)
        {
            int tilePosX = ((windowSize.x - this->padding*2) / (this->length)) * x + padding;
            int tilePosY = ((windowSize.y - this->padding*2) / (this->height)) * y + padding;

            if ((xPos - tilePosX) < tileLength && (yPos-tilePosY) < tileHeight
            &&  (xPos - tilePosX) > 0          && (yPos-tilePosY) > 0)
            {
                this->selectedTile = &gameState[x][y];
                gameState[x][y].setHighlightSelected();
                return &this->gameState[x][y]; // currently all I want the board to do is highlight and select a tile
            }
        }
    }
    // no tile selected
    return nullptr;

    /*
    int smallestDistance = INT_MAX;
    distanceToSquare = a*a + b*b
    distanceToSquare = distanceToSquare**/
    // I think I like select exact enough to not implement closest, I will probably do this another weekend TODO
}


std::string board::generateFEN()
{
    std::string retStr = "";
    unsigned short C; // terrible naming convention for a joke
    for (int x = 0; x < gameState.size(); x++)
    {
        for (int y = 0; y < gameState[x].size(); y++)
        {
            char returnedFEN = gameState[x][y].getFEN();
            if (returnedFEN == ASCII_SPACE_DEFAULT_FEN_CHAR)
            {
                C++; // :)
                continue;
            }
            if (C > 0)
            {
                retStr += std::to_string(C);
                C = 0;
            }
            retStr += gameState[x][y].getFEN();
        }
        retStr += "/";
    }
    return retStr;
}

void board::moveUnit(int xStartTile, int yStartTile, int xFinalTile, int yFinalTile)
{
    this->gameState[xFinalTile][yFinalTile].setPiece(gameState[xStartTile][yStartTile].getPiece());
    gameState[xStartTile][yStartTile].clearTile();
}
