#include "board.h"

#define TESTING_IMAGE_SIZE 1024

board::board( sf::RenderWindow *passWindow, std::string pathToTexture, int boardLength, int boardHeight, int padding)
{
    this->aWindow = passWindow;
    this->setTileTexture(pathToTexture);
    this->height = boardHeight;
    this->length = boardLength;
    this->padding = padding; // in px
    this->selectedTile = nullptr;
}

void board::setUpInitialBoard() // this needs to be completely replaced, positioning should be done by the player
// functions kepy should probably be desiredScaleX -> scaleX, and some lighter form of ensuring each tile has the texture (set all to texture maybe)
{
    auto windowDimension = aWindow->getSize();
    int scaleX, scaleY; // windowSize - padding * 2 is to ensure tile only in the "play space"
    // divided by number of tile, then multiplied by th
    scaleX = (windowDimension.x - (padding*2))/(float)this->length - padding/10;
    scaleY = (windowDimension.y - (padding*2))/(float)this->height - padding/10;

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
            std::cout << "aX:" << scaleX << " aY:" << scaleY;
            gameState[x][y].scaleTile(scaleX, scaleY);
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

#include <iostream>

boardtile *board::mouseClick(int xPos, int yPos)
{
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
                std::cout << (int)this->selectedTile->getFEN() << " or " << this->selectedTile->getFEN() << std::endl;
                gameState[x][y].setHighlightSelected(); // TODO remove final version, used for testing

                return &this->gameState[x][y]; // currently all I want the board to do is highlight and select a tile
                // returning allows users to do more faster, and to change board behavior if a tile is not clicked
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

void board::movePiece(int xStartTile, int yStartTile, int xFinalTile, int yFinalTile)
{
    this->gameState[xFinalTile][yFinalTile].setPiece(gameState[xStartTile][yStartTile].getPiece());
    gameState[xStartTile][yStartTile].clearTile();
}

// NETWORKING W BOOST

std::string board::receive_FEN(boost::asio::ip::tcp::socket & socket) {
       boost::asio::streambuf buf;
       boost::asio::read_until( socket, buf, "\n" );
       std::string data = boost::asio::buffer_cast<const char*>(buf.data());
       readFEN(data);
       return data;
}
void board::send_FEN(boost::asio::ip::tcp::socket & socket) {
       const std::string msg = this->generateFEN() + "\n";
       boost::asio::write(socket, boost::asio::buffer(msg) );
}
