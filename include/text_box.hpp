/*----------------------------------------------------------------------------//
cpGUI - a GUI tool kit with SFML as its primary back-end.

Copyright (c) 2009 Jason Cupp
Copyright (c) 2010 Patrick VanDusen, Alvin F.

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software. If you use this software in a product, an
acknowledgment in the product documentation would be appreciated but is not
required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
//----------------------------------------------------------------------------*/

// ***NOTE***: Combined text_box and text_input_box

#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace cp
{

class text_box
{
public:
    text_box( const std::string& text,
              const sf::Color& background_color,
              const sf::Color& text_color,
              const sf::Rect& box );

private:
    std::string text;
    sf::Color background_color;
    sf::Color text_color;
    sf::Rect box;
};

}

#endif



#if 0

#ifndef CPTEXTBOX
#define CPTEXTBOX

#include "cpGUI_base.h"
#include "cpObject.h"
#include "cpScrollBar.h"

namespace cp
{
class cpTextBox : public cpObject
{
public:
    cpTextBox(sf::RenderWindow *parent, cpGuiContainer *GUI, float posx=0,
              float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
    ~cpTextBox();
    void Draw();
    void LoadFile( const char* const filename);
    int CheckState(const sf::Input *input);

    bool SetSize(float width, float height);
    void SetPosition(float posx, float posy);
    void SetFont(std::string filename, unsigned int size);
    void SetBackgroundColor(sf::Color color);
    void SetFontStyle(unsigned long TextStyle);
    void SetFontSize(unsigned int size);
    void SetLabelColor(sf::Color color);


private:
    std::vector<std::string> lineStrings;
    std::vector<sf::String> lineSFStrings;
    const char* Filename;
    int viewableLines, totalLines, startingLine;
    unsigned int fontSize;
    cpScrollBar *scrollbar;
    sf::Clock clock;
};
}

#endif

#ifndef CPTEXTINPUTBOX
#define CPTEXTINPUTBOX

#include "cpGUI_base.h"
#include "cpGuiContainer.h"
#include "cpObject.h"

namespace cp
{
class cpTextInputBox : public cpObject
{
public:
    cpTextInputBox();
    cpTextInputBox(sf::RenderWindow *parent, cpGuiContainer *GUI, std::string label,
                   float posx=0, float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT,
                   int Style=CP_TXT_LEFT_ALIGN);
    void Draw();
    int CheckState(const sf::Input *input);
    bool SetSize(float width, float height);
    void SetPosition(float posx, float posy);
    void SetFont(std::string filename, unsigned int size);
    void SetBackgroundColor(sf::Color color);
    void SetFontStyle(unsigned long TextStyle);
    void SetFontSize(unsigned int size);
    void SetLabelColor(sf::Color color);
    void SetLabelText(std::string text);
    void ProcessTextInput(sf::Event *evt);


private:
    void CreateRects(std::string label);
    bool CheckTextFit();

    sf::Shape caret;
    bool bTooBig, caretOn;
    std::string tempText;
    sf::String tempLabel;
    float elapsedTime;
    int style;
};
}

#endif

#ifndef CPSELECTIONBOX
#define CPSELECTIONBOX

#include "cpGUI_base.h"
#include "cpScrollBar.h"

namespace cp
{
class cpSelectionBox : public cpObject
{
public:
    cpSelectionBox(sf::RenderWindow *parent, cpGuiContainer *GUI, float posx=0,
                   float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
    cpSelectionBox();
    ~cpSelectionBox();
    void Draw();
    void AddChoice(std::string choice);
    void RemoveLastChoice();
    int CheckState(const sf::Input *input);
    void SetSelection(int sel);
    int GetSelection();
    bool SetSize(float width, float height);
    void SetFontSize(unsigned int size);
    void SetFontStyle(unsigned long TextStyle);
    void CheckTextWidth();
    void SetPosition(float posx, float posy);
    void SetFont(std::string filename, unsigned int size);
    void SetBackgroundColor(sf::Color color);

    std::vector<sf::String> choices;
    int viewableLines;

private:
    void CreateRects(std::string label);
    int currentSelection, currentStartingLine;
    unsigned int fontSize;
    sf::Shape selBox;
    sf::Clock clock;
    cpScrollBar *scrollbar;
    bool mouseDown, keyDown;
};

class cpDropDownBox : public cpObject
{
public:
    cpDropDownBox(sf::RenderWindow *parent, cpGuiContainer *GUI, std::string label,
                  float posx=0, float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
    ~cpDropDownBox();
    void CreateRects(std::string label);
    void Draw();
    int CheckState(const sf::Input *input);
    void AddChoice(std::string choice);
    void RemoveLastChoice();
    void SetSelection(int sel);
    int GetSelection();
    bool SetSize(float width, float height);
    void SetFontSize(unsigned int size);
    void SetFontStyle(unsigned long TextStyle);
    void SetPosition(float posx, float posy);
    void SetFont(std::string filename, unsigned int size);
    void SetBackgroundColor(sf::Color color);
    void SetMaxDepth(float depth);
    void SetLabelColor(sf::Color color);


private:
    void CheckTextWidth();
    void MoveButton();

    cpButton *downBtn;
    cpSelectionBox *sBox;
    sf::Shape downArrow;
    sf::Color btnBackground, tempTextColor;
    float maxDepth, depth;

};
}

#endif

#endif
