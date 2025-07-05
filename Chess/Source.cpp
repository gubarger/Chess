// The game is designed for 2 players

#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <tuple>

using std::cout, std::endl, std::vector;
using namespace sf;

RenderWindow window(VideoMode(600, 600), "Chess game");

class Board;

enum class ComandColor {
    White, Black
};

enum class FigureStyle {
    Default, Style1, Style2
};

FigureStyle currentStyle = FigureStyle::Default;

class Figure {
public:
    virtual ~Figure() = default;
    virtual void draw(RenderWindow& window) const = 0;
    virtual bool isType(const std::string& type) const = 0;
    virtual void handleMouse(float mouse_x, float mouse_y) = 0;

    virtual vector<Vector2f> validMoves(const Board& board) const = 0;

    virtual void hoverEffect(float, float) {}
    virtual void resetColor() {}

    Texture texture{};
    Sprite sprite{};
    ComandColor comandColor{};
    Mouse::Button raising{};
    Vector2f position{};
};

// figures classes
class Pawn : public Figure {
private:
    bool isRaised = false;
    Vector2f offset;

    const float cellSize = 75.f;

public:
    Pawn(float x, float y, ComandColor colorCom) {
        std::string stylePath;

        switch (currentStyle)
        {
        case FigureStyle::Style1: stylePath = "Skins/memeSkins/";
            break;
        case FigureStyle::Style2: stylePath = "Skins/memeSkins2/";
            break;
        default: stylePath = "Skins/Default/";
            break;
        }

        if (colorCom == ComandColor::White)
        {
            if (!texture.loadFromFile(stylePath + "W_Pawn.png"))
            {
                std::cerr << "Load white king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/W_Pawn.png"))
                {
                    std::cerr << "Load default white king texture - failed!" << endl;
                }
            }
        }
        else
        {
            if (!texture.loadFromFile(stylePath + "B_Pawn.png"))
            {
                std::cerr << "Load black king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/B_Pawn.png"))
                {
                    std::cerr << "Load default black king texture - failed!" << endl;
                }
            }
        }

        sprite.setTexture(texture);

        float scale = 60.f / std::max(texture.getSize().x, texture.getSize().y);
        sprite.setScale(scale, scale);

        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(x + cellSize / 2, y + cellSize / 2);

        comandColor = colorCom;
        raising = Mouse::Left;
        position = Vector2f(x, y);
    }

    void handleMouse(float mouse_x, float mouse_y) override {
        FloatRect bounds = sprite.getGlobalBounds();

        if (!isRaised)
        {
            if (bounds.contains(mouse_x, mouse_y) && Mouse::isButtonPressed(raising))
            {
                isRaised = true;

                offset.x = sprite.getPosition().x - mouse_x;
                offset.y = sprite.getPosition().y - mouse_y;
            }
        }
        else
        {
            sprite.setPosition(mouse_x + offset.x, mouse_y + offset.y);

            if (!Mouse::isButtonPressed(raising))
            {
                isRaised = false;

                float newX = std::round((sprite.getPosition().x) / cellSize) * cellSize;
                float newY = std::round((sprite.getPosition().y) / cellSize) * cellSize;

                sprite.setPosition(newX, newY);
            }
        }
    }

    vector<Vector2f> validMoves(const Board& board) const override;

    void hoverEffect(float mouse_x, float mouse_y) override {}
    void resetColor() override {}

    void draw(RenderWindow& window) const override {
        window.draw(sprite);
    }

    bool isType(const std::string& type) const override {
        return type == "Pawn";
    }
};

class Rook : public Figure {
private:
    bool isRaised = false;
    Vector2f offset;

    const float cellSize = 75.f;

public:
    Rook(float x, float y, ComandColor colorCom) {
        std::string stylePath;

        switch (currentStyle)
        {
        case FigureStyle::Style1: stylePath = "Skins/memeSkins/";
            break;
        case FigureStyle::Style2: stylePath = "Skins/memeSkins2/";
            break;
        default: stylePath = "Skins/Default/";
            break;
        }

        if (colorCom == ComandColor::White)
        {
            if (!texture.loadFromFile(stylePath + "W_Rook.png"))
            {
                std::cerr << "Load white king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/W_Rook.png"))
                {
                    std::cerr << "Load default white king texture - failed!" << endl;
                }
            }
        }
        else
        {
            if (!texture.loadFromFile(stylePath + "B_Rook.png"))
            {
                std::cerr << "Load black king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/B_Rook.png"))
                {
                    std::cerr << "Load default black king texture - failed!" << endl;
                }
            }
        }

        sprite.setTexture(texture);

        float scale = 60.f / std::max(texture.getSize().x, texture.getSize().y);
        sprite.setScale(scale, scale);

        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(x + cellSize / 2, y + cellSize / 2);

        comandColor = colorCom;
        raising = Mouse::Left;
        position = Vector2f(x, y);
    }

    void handleMouse(float mouse_x, float mouse_y) override {
        FloatRect bounds = sprite.getGlobalBounds();

        if (!isRaised)
        {
            if (bounds.contains(mouse_x, mouse_y) && Mouse::isButtonPressed(raising))
            {
                isRaised = true;

                offset.x = sprite.getPosition().x - mouse_x;
                offset.y = sprite.getPosition().y - mouse_y;
            }
        }
        else
        {
            sprite.setPosition(mouse_x + offset.x, mouse_y + offset.y);

            if (!Mouse::isButtonPressed(raising))
            {
                isRaised = false;

                float newX = std::round((sprite.getPosition().x) / cellSize) * cellSize;
                float newY = std::round((sprite.getPosition().y) / cellSize) * cellSize;

                sprite.setPosition(newX, newY);
            }
        }
    }

    vector<Vector2f> validMoves(const Board& board) const override;

    void hoverEffect(float mouse_x, float mouse_y) override {}
    void resetColor() override {}

    void draw(RenderWindow& window) const override {
        window.draw(sprite);
    }

    bool isType(const std::string& type) const override {
        return type == "Rook";
    }
};

class Knight : public Figure {
private:
    bool isRaised = false;
    Vector2f offset;

    const float cellSize = 75.f;

public:
    Knight(float x, float y, ComandColor colorCom) {
        std::string stylePath;

        switch (currentStyle)
        {
        case FigureStyle::Style1: stylePath = "Skins/memeSkins/";
            break;
        case FigureStyle::Style2: stylePath = "Skins/memeSkins2/";
            break;
        default: stylePath = "Skins/Default/";
            break;
        }

        if (colorCom == ComandColor::White)
        {
            if (!texture.loadFromFile(stylePath + "W_Knight.png"))
            {
                std::cerr << "Load white king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/W_Knight.png"))
                {
                    std::cerr << "Load default white king texture - failed!" << endl;
                }
            }
        }
        else
        {
            if (!texture.loadFromFile(stylePath + "B_Knight.png"))
            {
                std::cerr << "Load black king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/B_Knight.png"))
                {
                    std::cerr << "Load default black king texture - failed!" << endl;
                }
            }
        }

        sprite.setTexture(texture);

        float scale = 60.f / std::max(texture.getSize().x, texture.getSize().y);
        sprite.setScale(scale, scale);

        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(x + cellSize / 2, y + cellSize / 2);

        comandColor = colorCom;
        raising = Mouse::Left;
        position = Vector2f(x, y);
    }

    void handleMouse(float mouse_x, float mouse_y) override {
        FloatRect bounds = sprite.getGlobalBounds();

        if (!isRaised)
        {
            if (bounds.contains(mouse_x, mouse_y) && Mouse::isButtonPressed(raising))
            {
                isRaised = true;

                offset.x = sprite.getPosition().x - mouse_x;
                offset.y = sprite.getPosition().y - mouse_y;
            }
        }
        else
        {
            sprite.setPosition(mouse_x + offset.x, mouse_y + offset.y);

            if (!Mouse::isButtonPressed(raising))
            {
                isRaised = false;

                float newX = std::round((sprite.getPosition().x) / cellSize) * cellSize;
                float newY = std::round((sprite.getPosition().y) / cellSize) * cellSize;

                sprite.setPosition(newX, newY);
            }
        }
    }

    vector<Vector2f> validMoves(const Board& board) const override;

    void hoverEffect(float mouse_x, float mouse_y) override {}
    void resetColor() override {}

    void draw(RenderWindow& window) const override {
        window.draw(sprite);
    }

    bool isType(const std::string& type) const override {
        return type == "Knight";
    }
};

class Bishop : public Figure {
private:
    bool isRaised = false;
    Vector2f offset;

    const float cellSize = 75.f;

public:
    Bishop(float x, float y, ComandColor colorCom) {
        std::string stylePath;

        switch (currentStyle)
        {
        case FigureStyle::Style1: stylePath = "Skins/memeSkins/";
            break;
        case FigureStyle::Style2: stylePath = "Skins/memeSkins2/";
            break;
        default: stylePath = "Skins/Default/";
            break;
        }

        if (colorCom == ComandColor::White)
        {
            if (!texture.loadFromFile(stylePath + "W_Bishop.png"))
            {
                std::cerr << "Load white king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/W_Bishop.png"))
                {
                    std::cerr << "Load default white king texture - failed!" << endl;
                }
            }
        }
        else
        {
            if (!texture.loadFromFile(stylePath + "B_Bishop.png"))
            {
                std::cerr << "Load black king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/B_Bishop.png"))
                {
                    std::cerr << "Load default black king texture - failed!" << endl;
                }
            }
        }

        sprite.setTexture(texture);

        float scale = 60.f / std::max(texture.getSize().x, texture.getSize().y);
        sprite.setScale(scale, scale);

        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(x + cellSize / 2, y + cellSize / 2);

        comandColor = colorCom;
        raising = Mouse::Left;
        position = Vector2f(x, y);
    }

    void handleMouse(float mouse_x, float mouse_y) override {
        FloatRect bounds = sprite.getGlobalBounds();

        if (!isRaised)
        {
            if (bounds.contains(mouse_x, mouse_y) && Mouse::isButtonPressed(raising))
            {
                isRaised = true;

                offset.x = sprite.getPosition().x - mouse_x;
                offset.y = sprite.getPosition().y - mouse_y;
            }
        }
        else
        {
            sprite.setPosition(mouse_x + offset.x, mouse_y + offset.y);

            if (!Mouse::isButtonPressed(raising))
            {
                isRaised = false;

                float newX = std::round((sprite.getPosition().x) / cellSize) * cellSize;
                float newY = std::round((sprite.getPosition().y) / cellSize) * cellSize;

                sprite.setPosition(newX, newY);
            }
        }
    }

    vector<Vector2f> validMoves(const Board& board) const override;

    void hoverEffect(float mouse_x, float mouse_y) override {}
    void resetColor() override {}

    void draw(RenderWindow& window) const override {
        window.draw(sprite);
    }

    bool isType(const std::string& type) const override {
        return type == "Bishop";
    }
};

class Queen : public Figure {
private:
    bool isRaised = false;
    Vector2f offset;

    const float cellSize = 75.f;

public:
    Queen(float x, float y, ComandColor colorCom) {
        std::string stylePath;

        switch (currentStyle)
        {
        case FigureStyle::Style1: stylePath = "Skins/memeSkins/";
            break;
        case FigureStyle::Style2: stylePath = "Skins/memeSkins2/";
            break;
        default: stylePath = "Skins/Default/";
            break;
        }

        if (colorCom == ComandColor::White)
        {
            if (!texture.loadFromFile(stylePath + "W_Queen.png"))
            {
                std::cerr << "Load white king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/W_Queen.png"))
                {
                    std::cerr << "Load default white king texture - failed!" << endl;
                }
            }
        }
        else
        {
            if (!texture.loadFromFile(stylePath + "B_Queen.png"))
            {
                std::cerr << "Load black king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/B_Queen.png"))
                {
                    std::cerr << "Load default black king texture - failed!" << endl;
                }
            }
        }

        sprite.setTexture(texture);

        float scale = 60.f / std::max(texture.getSize().x, texture.getSize().y);
        sprite.setScale(scale, scale);

        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(x + cellSize / 2, y + cellSize / 2);

        comandColor = colorCom;
        raising = Mouse::Left;
        position = Vector2f(x, y);
    }

    void handleMouse(float mouse_x, float mouse_y) override {
        FloatRect bounds = sprite.getGlobalBounds();

        if (!isRaised)
        {
            if (bounds.contains(mouse_x, mouse_y) && Mouse::isButtonPressed(raising))
            {
                isRaised = true;

                offset.x = sprite.getPosition().x - mouse_x;
                offset.y = sprite.getPosition().y - mouse_y;
            }
        }
        else
        {
            sprite.setPosition(mouse_x + offset.x, mouse_y + offset.y);

            if (!Mouse::isButtonPressed(raising))
            {
                isRaised = false;

                float newX = std::round((sprite.getPosition().x) / cellSize) * cellSize;
                float newY = std::round((sprite.getPosition().y) / cellSize) * cellSize;

                sprite.setPosition(newX, newY);
            }
        }
    }

    vector<Vector2f> validMoves(const Board& board) const override;

    void hoverEffect(float mouse_x, float mouse_y) override {}
    void resetColor() override {}

    void draw(RenderWindow& window) const override {
        window.draw(sprite);
    }

    bool isType(const std::string& type) const override {
        return type == "Queen";
    }
};

class King : public Figure {
private:
    bool isRaised = false;
    Vector2f offset;

    const float cellSize = 75.f;

public:
    King(float x, float y, ComandColor colorCom) {
        std::string stylePath;

        switch (currentStyle) 
        {
        case FigureStyle::Style1: stylePath = "Skins/memeSkins/";
            break;
        case FigureStyle::Style2: stylePath = "Skins/memeSkins2/";
            break;
        default: stylePath = "Skins/Default/";
            break;
        }

        if (colorCom == ComandColor::White) 
        {
            if (!texture.loadFromFile(stylePath + "W_King.png"))
            {
                std::cerr << "Load white king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/W_King.png")) 
                {
                    std::cerr << "Load default white king texture - failed!" << endl;
                }
            }
        }
        else 
        {
            if (!texture.loadFromFile(stylePath + "B_King.png")) 
            {
                std::cerr << "Load black king texture - failed!" << endl;

                if (!texture.loadFromFile("Skins/Default/B_King.png")) 
                {
                    std::cerr << "Load default black king texture - failed!" << endl;
                }
            }
        }

        sprite.setTexture(texture);

        float scale = 60.f / std::max(texture.getSize().x, texture.getSize().y);
        sprite.setScale(scale, scale);

        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(x + cellSize / 2, y + cellSize / 2);

        comandColor = colorCom;
        raising = Mouse::Left;
        position = Vector2f(x, y);
    }

    void handleMouse(float mouse_x, float mouse_y) override {
        FloatRect bounds = sprite.getGlobalBounds();

        if (!isRaised)
        {
            if (bounds.contains(mouse_x, mouse_y) && Mouse::isButtonPressed(raising))
            {
                isRaised = true;

                offset.x = sprite.getPosition().x - mouse_x;
                offset.y = sprite.getPosition().y - mouse_y;
            }
        }
        else
        {
            sprite.setPosition(mouse_x + offset.x, mouse_y + offset.y);

            if (!Mouse::isButtonPressed(raising))
            {
                isRaised = false;

                float newX = std::round((sprite.getPosition().x) / cellSize) * cellSize;
                float newY = std::round((sprite.getPosition().y) / cellSize) * cellSize;

                sprite.setPosition(newX, newY);
            }
        }
    }

    vector<Vector2f> validMoves(const Board& board) const override;

    void hoverEffect(float mouse_x, float mouse_y) override {}
    void resetColor() override {}

    void draw(RenderWindow& window) const override {
        window.draw(sprite);
    }

    bool isType(const std::string& type) const override {
        return type == "King";
    }
};

class Board {
private:
    std::vector<std::unique_ptr<Figure>> figures;
    std::vector<RectangleShape> blocks;
    Figure* selectedFigure = nullptr;
    Vector2f selectOffset;
    ComandColor turn = ComandColor::White;

    vector<CircleShape> moveIndicators;

    const float cellSize = 75.f;

public:
    void addFigure(std::unique_ptr<Figure> figure) {
        figures.push_back(std::move(figure));
    }

    void addBlock(const RectangleShape& block) {
        blocks.push_back(block);
    }

    bool isKing(const Vector2f& position) const {
        for (const auto& figure : figures)
        {
            if (std::abs(figure->position.x - position.x) < 1.f && std::abs(figure->position.y - position.y) < 1.f && figure->isType("King"))
            {
                return true;
            }
        }
        return false;
    }

    void handleMouse(float mouse_x, float mouse_y) {
        if (!selectedFigure && Mouse::isButtonPressed(Mouse::Left)) 
        {
            for (auto& figure : figures)
            {
                FloatRect bounds = figure->sprite.getGlobalBounds();
                if (bounds.contains(mouse_x, mouse_y) && figure->comandColor == turn)
                {
                    selectedFigure = figure.get();

                    selectOffset.x = figure->sprite.getPosition().x - mouse_x;
                    selectOffset.y = figure->sprite.getPosition().y - mouse_y;

                    auto moves = figure->validMoves(*this);
                    indicatorMove(moves);
                    break;
                }
            }
        }
        else if (selectedFigure) 
        {
            selectedFigure->sprite.setPosition(mouse_x + selectOffset.x, mouse_y + selectOffset.y);

            if (!Mouse::isButtonPressed(Mouse::Left)) {
                float newX = std::round((selectedFigure->sprite.getPosition().x - cellSize / 2) / cellSize) * cellSize + cellSize / 2;
                float newY = std::round((selectedFigure->sprite.getPosition().y - cellSize / 2) / cellSize) * cellSize + cellSize / 2;

                Vector2f newPos(newX - cellSize / 2, newY - cellSize / 2);

                auto validMoves = selectedFigure->validMoves(*this);
                bool isValidMove = false;

                for (const auto& move : validMoves)
                {
                    if (std::abs(move.x - newPos.x) < 0.1f && std::abs(move.y - newPos.y) < 0.1f) 
                    {
                        isValidMove = true;
                        break;
                    }
                }

                if (isValidMove)
                {
                    Figure* target = nullptr;

                    for (auto it = figures.begin(); it != figures.end(); ++it) 
                    {
                        if (it->get() != selectedFigure && std::abs((*it)->position.x - newPos.x) < 1.f &&
                            std::abs((*it)->position.y - newPos.y) < 1.f)
                        {
                            target = it->get();
                            break;
                        }
                    }

                    selectedFigure->sprite.setPosition(newX, newY);
                    selectedFigure->position = newPos;

                    if (target) 
                    {
                        figures.erase(std::remove_if(figures.begin(), figures.end(), 
                            [target](const auto& f) { return f.get() == target; }), figures.end());
                    }

                    turn = (turn == ComandColor::White) ? ComandColor::Black : ComandColor::White;

                    moveIndicators.clear();
                }
                else 
                {
                    selectedFigure->sprite.setPosition(
                        selectedFigure->position.x + cellSize / 2,
                        selectedFigure->position.y + cellSize / 2);
                    
                    moveIndicators.clear();
                }

                selectedFigure = nullptr;
            }
        }
    }

    bool isSquareEmpty(const Vector2f& position) const {
        for (const auto& figure : figures)
        {
            if (std::abs(figure->position.x - position.x) < 1.f && std::abs(figure->position.y - position.y) < 1.f)
            {
                return false;
            }
        }
        return true;
    }

    bool isOpponent(const Vector2f& position, ComandColor color) const {
        for (const auto& figure : figures)
        {
            if (std::abs(figure->position.x - position.x) < 1.f && std::abs(figure->position.y - position.y) < 1.f && figure->comandColor != color)
            {
                return true;
            }
        }
        return false;
    }

    bool isOnBoard(const Vector2f& position) const {
        return position.x >= 0 && position.x < 8 * cellSize && position.y >= 0 && position.y < 8 * cellSize;
    }

    void indicatorMove(const vector<Vector2f>& moves) {
        moveIndicators.clear();

        for (const auto& move : moves)
        {
            if (!isKing(move))
            {
                if (isOpponent(move, selectedFigure->comandColor))
                {
                    CircleShape indicator(15.f, 4);

                    indicator.setFillColor(Color(255, 100, 100, 150));
                    indicator.setPosition(move.x + cellSize / 2 - 15, move.y + cellSize / 2 - 15);

                    moveIndicators.push_back(indicator);
                }
                else
                {
                    CircleShape indicator(10.f);

                    indicator.setFillColor(Color(124, 252, 0, 150));
                    indicator.setPosition(move.x + cellSize / 2 - 10, move.y + cellSize / 2 - 10);

                    moveIndicators.push_back(indicator);
                }
            }
        }
    }

    void changeStyle(FigureStyle newStyle, Board& board) {
        currentStyle = newStyle;

        std::vector<std::tuple<Vector2f, ComandColor, std::string>> figuresInfo;

        for (const auto& figure : board.figures) 
        {
            std::string type;

            if (figure->isType("Pawn")) type = "Pawn";
            else if (figure->isType("Rook")) type = "Rook";
            else if (figure->isType("Knight")) type = "Knight";
            else if (figure->isType("Bishop")) type = "Bishop";
            else if (figure->isType("Queen")) type = "Queen";
            else if (figure->isType("King")) type = "King";

            figuresInfo.emplace_back(figure->position, figure->comandColor, type);
        }

        board.figures.clear();

        for (const auto& info : figuresInfo) 
        {
            Vector2f pos = std::get<0>(info);
            ComandColor color = std::get<1>(info);
            std::string type = std::get<2>(info);

            if (type == "Pawn") board.addFigure(std::make_unique<Pawn>(pos.x, pos.y, color));
            else if (type == "Rook") board.addFigure(std::make_unique<Rook>(pos.x, pos.y, color));
            else if (type == "Knight") board.addFigure(std::make_unique<Knight>(pos.x, pos.y, color));
            else if (type == "Bishop") board.addFigure(std::make_unique<Bishop>(pos.x, pos.y, color));
            else if (type == "Queen") board.addFigure(std::make_unique<Queen>(pos.x, pos.y, color));
            else if (type == "King") board.addFigure(std::make_unique<King>(pos.x, pos.y, color));
        }
    }

    void drawAll(RenderWindow& window) const {
        for (const auto& block : blocks) 
        {
            window.draw(block);
        }

        for (const auto& figure : figures) 
        {
            figure->draw(window);
        }

        for (const auto& indicator : moveIndicators)
        {
            window.draw(indicator);
        }
    }
};

// Logic moves for figures //
vector<Vector2f> Pawn::validMoves(const Board& board) const {
    vector<Vector2f> validMoves;

    int direction = (comandColor == ComandColor::White) ? 1 : -1;

    auto isInsideBoard = [&](const Vector2f& position) {
        return position.x >= 0 && position.x < 8 * cellSize && position.y >= 0 && position.y < 8 * cellSize;
    };

    Vector2f moveForvard(position.x, position.y + direction * cellSize);

    if (isInsideBoard(moveForvard) && board.isSquareEmpty(moveForvard))
    {
        validMoves.push_back(moveForvard);

        bool isWhiteStart = (comandColor == ComandColor::White && position.y == 1 * cellSize);
        bool isBlackStart = (comandColor == ComandColor::Black && position.y == 6 * cellSize);

        if (isWhiteStart || isBlackStart)
        {
            Vector2f moveDouble(position.x, position.y + 2 * direction * cellSize);

            if (isInsideBoard(moveDouble) && board.isSquareEmpty(moveDouble))
            {
                validMoves.push_back(moveDouble);
            }
        }
    }

    Vector2f captureLeft(position.x - cellSize, position.y + direction * cellSize);
    Vector2f captureRight(position.x + cellSize, position.y + direction * cellSize);

    if (isInsideBoard(captureLeft) && board.isOpponent(captureLeft, comandColor)) validMoves.push_back(captureLeft);
    if (isInsideBoard(captureRight) && board.isOpponent(captureRight, comandColor)) validMoves.push_back(captureRight);

    return validMoves;
}

vector<Vector2f> Rook::validMoves(const Board& board) const {
    vector<Vector2f> validMoves;

    auto isInsideBoard = [&](const Vector2f& position) {
        return position.x >= 0 && position.x < 8 * cellSize && position.y >= 0 && position.y < 8 * cellSize;
    };

    for (int i = 1; i < 8; i++)
    {
        Vector2f newPos(position.x, position.y - i * cellSize);

        if (!isInsideBoard(newPos)) break;

        if (board.isSquareEmpty(newPos))
        {
            validMoves.push_back(newPos);
        }
        else
        {
            if (board.isOpponent(newPos, comandColor))
            {
                validMoves.push_back(newPos);
            }
            break;
        }
    }

    for (int i = 1; i < 8; i++)
    {
        Vector2f newPos(position.x, position.y + i * cellSize);

        if (!isInsideBoard(newPos)) break;

        if (board.isSquareEmpty(newPos))
        {
            validMoves.push_back(newPos);
        }
        else
        {
            if (board.isOpponent(newPos, comandColor))
            {
                validMoves.push_back(newPos);
            }
            break;
        }
    }

    for (int i = 1; i < 8; i++)
    {
        Vector2f newPos(position.x - i * cellSize, position.y);

        if (!isInsideBoard(newPos)) break;

        if (board.isSquareEmpty(newPos))
        {
            validMoves.push_back(newPos);
        }
        else
        {
            if (board.isOpponent(newPos, comandColor))
            {
                validMoves.push_back(newPos);
            }
            break;
        }
    }

    for (int i = 1; i < 8; i++)
    {
        Vector2f newPos(position.x + i * cellSize, position.y);

        if (!isInsideBoard(newPos)) break;

        if (board.isSquareEmpty(newPos))
        {
            validMoves.push_back(newPos);
        }
        else
        {
            if (board.isOpponent(newPos, comandColor))
            {
                validMoves.push_back(newPos);
            }
            break;
        }
    }

    return validMoves;
}

vector<Vector2f> Knight::validMoves(const Board& board) const {
    vector<Vector2f> validMoves;

    const vector<Vector2f> MovesKnight {
        { -1 * cellSize, -2 * cellSize},
        {  1 * cellSize, -2 * cellSize},
        { -2 * cellSize, -1 * cellSize},
        {  2 * cellSize, -1 * cellSize},
        { -2 * cellSize,  1 * cellSize},
        {  2 * cellSize,  1 * cellSize},
        { -1 * cellSize,  2 * cellSize},
        {  1 * cellSize,  2 * cellSize},
    };

    for (const auto& move : MovesKnight)
    {
        Vector2f newPos(position.x + move.x, position.y + move.y);

        if (board.isOnBoard(newPos))
        {
            if (board.isSquareEmpty(newPos) || board.isOpponent(newPos, comandColor))
            {
                validMoves.push_back(newPos);
            }
        }
    }

    return validMoves;
}

vector<Vector2f> Bishop::validMoves(const Board& board) const {
    vector<Vector2f> validMoves;

    const vector<Vector2f> MovesBishop {
        {  1,  1},
        {  1, -1},
        { -1,  1},
        { -1, -1},
    };

    for (const auto& move : MovesBishop)
    {
        for (int i = 1; i < 8; i++)
        {
            Vector2f newPos(position.x + i * move.x * cellSize, position.y + i * move.y * cellSize);

            if (!board.isOnBoard(newPos))
            {
                break;
            }

            if (board.isSquareEmpty(newPos))
            {
                validMoves.push_back(newPos);
            }
            else if (board.isOpponent(newPos, comandColor))
            {
                validMoves.push_back(newPos);
                break;
            }
            else
            {
                break;
            }
        }
    }

    return validMoves;
}

vector<Vector2f> Queen::validMoves(const Board& board) const {
    vector<Vector2f> validMoves;

    const vector<Vector2f> MovesQueen {
        {  1,  0 },
        { -1,  0 },
        {  0,  1 },
        {  0, -1 },
        {  1,  1 },
        {  1, -1 },
        { -1,  1 },
        { -1, -1 },
    };

    for (const auto& move : MovesQueen)
    {
        for (int i = 1; i < 8; i++)
        {
            Vector2f newPos(position.x + i * move.x * cellSize, position.y + i * move.y * cellSize);

            if (!board.isOnBoard(newPos))
            {
                break;
            }

            if (board.isSquareEmpty(newPos))
            {
                validMoves.push_back(newPos);
            }
            else if (board.isOpponent(newPos, comandColor))
            {
                validMoves.push_back(newPos);
                break;
            }
            else
            {
                break;
            }
        }
    }

    return validMoves;
}

vector<Vector2f> King::validMoves(const Board& board) const {
    vector<Vector2f> validMoves;

    const vector<Vector2f> MovesKing {
        {  1,  0 },
        { -1,  0 },
        {  0,  1 },
        {  0, -1 },
        {  1,  1 },
        {  1, -1 },
        { -1,  1 },
        { -1, -1 },
    };

    for (const auto& move : MovesKing)
    {
        Vector2f newPos(position.x + move.x * cellSize, position.y + move.y * cellSize);

        if (!board.isOnBoard(newPos))
        {
            continue;
        }

        if (board.isSquareEmpty(newPos) || board.isOpponent(newPos, comandColor))
        {
            validMoves.push_back(newPos);
        }
    }

    return validMoves;
}

int main()
{
    Board board;

    for (int i = 0; i < 8; ++i) 
    {
        for (int j = 0; j < 8; ++j) 
        {
            RectangleShape block(Vector2f(75, 75));

            block.setPosition(i * 75, j * 75);
            block.setFillColor((i + j) % 2 ? Color::White : Color(72, 60, 50));

            board.addBlock(block);
        }
    }

    // figures create //

    // 1) white
    for (int i = 0; i < 8; i++)
    {
        board.addFigure(std::make_unique<Pawn>(i * 75, 1 * 75, ComandColor::White));
    }

    board.addFigure(std::make_unique<Rook>(0 * 75.f, 0 * 75.f, ComandColor::White));
    board.addFigure(std::make_unique<Rook>(7 * 75.f, 0 * 75.f, ComandColor::White));

    board.addFigure(std::make_unique<Knight>(1 * 75.f, 0 * 75.f, ComandColor::White));
    board.addFigure(std::make_unique<Knight>(6 * 75.f, 0 * 75.f, ComandColor::White));

    board.addFigure(std::make_unique<Bishop>(2 * 75.f, 0 * 75.f, ComandColor::White));
    board.addFigure(std::make_unique<Bishop>(5 * 75.f, 0 * 75.f, ComandColor::White));

    board.addFigure(std::make_unique<Queen>(3 * 75.f, 0 * 75.f, ComandColor::White));
    board.addFigure(std::make_unique<King>(4 * 75.f, 0 * 75.f, ComandColor::White));

    // 2) black
    for (int i = 0; i < 8; i++)
    {
        board.addFigure(std::make_unique<Pawn>(i * 75, 6 * 75, ComandColor::Black));
    }

    board.addFigure(std::make_unique<Rook>(0 * 75.f, 7 * 75.f, ComandColor::Black));
    board.addFigure(std::make_unique<Rook>(7 * 75.f, 7 * 75.f, ComandColor::Black));

    board.addFigure(std::make_unique<Knight>(1 * 75.f, 7 * 75.f, ComandColor::Black));
    board.addFigure(std::make_unique<Knight>(6 * 75.f, 7 * 75.f, ComandColor::Black));

    board.addFigure(std::make_unique<Bishop>(2 * 75.f, 7 * 75.f, ComandColor::Black));
    board.addFigure(std::make_unique<Bishop>(5 * 75.f, 7 * 75.f, ComandColor::Black));

    board.addFigure(std::make_unique<Queen>(3 * 75.f, 7 * 75.f, ComandColor::Black));
    board.addFigure(std::make_unique<King>(4 * 75.f, 7 * 75.f, ComandColor::Black));

    cout << "The game is running..." << endl;
    cout << "press the key to end the game - E" << endl;

    while (window.isOpen())
    {
        Event event;

        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) 
            {
                if (event.key.code == Keyboard::Num1) 
                {
                    board.changeStyle(FigureStyle::Default, board);
                }
                else if (event.key.code == Keyboard::Num2) 
                {
                    board.changeStyle(FigureStyle::Style1, board);
                }
                else if (event.key.code == Keyboard::Num3) 
                {
                    board.changeStyle(FigureStyle::Style2, board);
                }
                else if (event.key.code == Keyboard::E)
                {
                    window.close();
                    return 0;
                }
            }
        }

        board.handleMouse(mousePos.x, mousePos.y);

        window.clear();
        board.drawAll(window);
        window.display();
    }

    return 0;
}