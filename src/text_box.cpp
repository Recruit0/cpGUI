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

#include <string>

#include "text_box.hpp"

using namespace sf;
using namespace std;
using namespace cp;

bool resizable; ///< Whether the box can be resized.
    bool moveable; ///< Whether the box can be moved.
    bool writable; ///< Whether the text can be edited or not.
    // R0: I've heard from Laurent that the "String class could be faster" or
    // something similar. Might consider a different implementation later.
    std::string text; ///< The text of this box.
    sf::Color text_color; ///< What color to draw the text in.
    uint32_t fill_color; ///< What color to fill the widget with.
    uint32_t width; ///< The widget's width.
    uint32_t height; ///< The widget's height.

    // Inherited from widget
    uint32_t x; ///< The widget's horizontal position in screen coordinates.
    uint32_t y; ///< The widget's vertical position in screen coordinates.

text_box::text_box( const string& new_text,
              const uint32_t new_text_color,
              const uint32_t new_fill_color,
              const int new_x, const int new_y,
              const int new_width, const int new_height ):
              resizable( 0 ), movable( 0 ), writable( 1 ),
              text( new_text ), text_color( new_text_color ),
              fill_color( new_fill_color ),
              width( new_width ), height( new_height )
{
    x = new_x;
    y = new_y;
}

void text_box::draw( RenderWindow& window ) const
{
    window.Draw( String( text ) );
}

void text_box::handle_event( const sf::Event& new_event )
{
}

#if 0

#include "cpGUI_base.h"
#include "cpTextBox.h"
#include <cstring>

using namespace cp;
using namespace std;

/// *************************************************************
/// This is a non-editable, read only text box used
/// for displaying long strings of text, or displaying a
/// txt file.  This class automatically word wraps the text
/// to fit the size of the box.  Minimum size is 200x200.
/// *************************************************************
cpTextBox::cpTextBox(sf::RenderWindow *parent, cpGuiContainer *GUI,
                     float posx, float posy, float width, float height) :
        cpObject(parent, GUI, "", posx, posy, width, height)
{
    backgroundColor = sf::Color::White;
    if (Width < 200)
        Width = 200;
    if (Height < 200)
        Height = 200;
    Filename = NULL;
    fontSize = (unsigned int)Label.GetSize();
    totalLines = 0;
    startingLine = 0;
    viewableLines = int((Height-5)/(fontSize+2));
    clock.Reset();

    scrollbar = new cpScrollBar(Parent, gui, Height, viewableLines, totalLines,
                                PosX+Width, PosY);

    gui->AcceptsKeys(true, false);
    SetUseWheel(true);
    CreateRects(Label.GetText());
}

cpTextBox::~cpTextBox()
{
    delete scrollbar;
    scrollbar = NULL;
}

/// Draws the text box, any text loaded, and a
/// scrollbar if necessary.
void cpTextBox::Draw()
{
    if (!bShow)
        return;

    Parent->Draw(backRect);
    if (viewableLines < totalLines)
        scrollbar->Draw();
    if (lineSFStrings.size() < 1)
        return;

    int max = lineSFStrings.size();
    if (max > viewableLines)
        max = viewableLines;
    for (int t=0; t < max; t++)
    {
        lineSFStrings[t+startingLine].SetPosition(PosX+5, PosY+((Height-viewableLines*
                (fontSize+2))/2)+((fontSize+2)*t));
        Parent->Draw(lineSFStrings[t+startingLine]);
    }
}

/// Loads a simple text file, word wraps it to fit the
/// Text Box, and sets totalLines for the total number of lines.
/// Rich text is not supported.
void cpTextBox::LoadFile( const char* const filename)
{
    totalLines = 0;
    Filename = filename;
    // The code below used to try to use a completely null pointer "filename"
    // Should work as intended now, although have not stepped through the logic
    // of this code
    if ( filename == 0 ) // New code that catches null ptr
    {
        return;
    }
    // This is the original code, haven't stepped through code surrounding this
    // to see what the purpose of this was
    /*
    if( strcmp( Filename, "" ) )
    {
      Filename = "ERROR 2";
    	return;
    }
    */
    lineSFStrings.clear();
    std::ifstream file(filename);
    if (!file.is_open())
        return;

    std::string Line, tempWord, tempLine;
    sf::String sfTemp;
    std::vector<std::string> tokens;
    sfTemp = Label;
    while (std::getline(file, Line))
    {
        tokens.clear();
        std::stringstream words(Line);
        while (std::getline(words, tempWord, ' '))
        {
            tokens.push_back(tempWord);
        }
        tempLine = "";
        int wordinline = 0;
        for (unsigned int t=0; t < tokens.size(); t++)
        {
            wordinline++;
            bool longword = false;
            sfTemp.SetText(tempLine + tokens[t] + " ");

            if (sfTemp.GetRect().GetWidth() > Width - 10 && wordinline == 1)
            {
                longword = true;
                for (unsigned int r=0; r < tokens[t].length(); r++)
                {
                    sfTemp.SetText(tempLine + tokens[t][r]);
                    if (sfTemp.GetRect().GetWidth() >= Width-10)
                    {
                        sfTemp.SetText(tempLine);
                        lineSFStrings.push_back(sfTemp);
                        totalLines++;
                        tempLine = "";
                    }
                    tempLine = tempLine + tokens[t][r];
                }
            }

            if (sfTemp.GetRect().GetWidth() > Width - 10 && wordinline > 1)
            {
                sfTemp.SetText(tempLine);
                lineSFStrings.push_back(sfTemp);
                totalLines++;
                tempLine = "";
                wordinline = 0;
            }
            if (!longword)
                tempLine = tempLine + tokens[t] + " ";
        }
        sfTemp.SetText(tempLine);
        lineSFStrings.push_back(sfTemp);
        totalLines++;
    }
    file.close();
    scrollbar->Repopulate(viewableLines, totalLines);
}

/// This function checks for mouse events within the control.
/// it updates the look of the control according to the event.
/// it also returns an integer enumeration member to inform the user.
/// possible return values are:
/// CP_ST_NONE, CP_ST_MOUSE_ENTER, CP_ST_MOUSE_EXIT,
/// CP_ST_MOUSE_IN, CP_ST_LBUTTON_DOWN, CP_ST_LBUTTON_RELEASED.
///
/// The difference between CP_ST_MOUSE_ENTER & CP_ST_MOUSE_IN
/// is that IN is active the entire time the mouse is inside the control
/// and ENTER is only active right when the mouse enters the control
///
/// This class accepts mouse wheel delta information from the
/// GuiContainer to update the scrollbar.
int cpTextBox::CheckState(const sf::Input *input)
{
    int state = cpObject::CheckState(input);

    if (wheelDelta == 1)
    {
        scrollbar->MoveSlider(-1);
        wheelDelta = 0;
    }
    if (wheelDelta == -1)
    {
        scrollbar->MoveSlider(1);
        wheelDelta = 0;
    }

    if (input->IsKeyDown(sf::Key::Down) && hasFocus && clock.GetElapsedTime() > .15)
    {
        scrollbar->MoveSlider(1);
        //startingLine++;
        clock.Reset();
    }
    if (input->IsKeyDown(sf::Key::Up) && hasFocus && clock.GetElapsedTime() > .15)
    {
        scrollbar->MoveSlider(-1);
        //startingLine--;
        clock.Reset();
    }
    startingLine = scrollbar->CheckState(input);

    return state;
}

/// Sets the width & height dimensions of the Text Box.
/// BEWARE:
/// The current text file will be reloaded in order to
/// recalculate word wrap based on the new size.
/// Doing this could be time consuming for very large files.
bool cpTextBox::SetSize(float width, float height)
{
    Width = width;
    Height = height;
    viewableLines = int((Height-5)/(fontSize+2));
    LoadFile(Filename);
    CreateRects(Label.GetText());
    scrollbar->SetSize(Height, viewableLines);
    scrollbar->SetPosition(PosX+Width, PosY);
    return true;
}

/// Sets the coordinates for the text box's position.
void cpTextBox::SetPosition(float posx, float posy)
{
    cpObject::SetPosition(posx, posy);
    scrollbar->SetPosition(PosX+Width, PosY);
    CreateRects(Label.GetText());
}

/// Loads a new font for the text.
/// BEWARE: the current file will be reloaded in order to update
/// word wrap for the new font size. This could be time consuming
/// for very large files.
void cpTextBox::SetFont(std::string filename, unsigned int size)
{
    cpObject::SetFont(filename, size);
    fontSize = (unsigned int)Label.GetSize();
    viewableLines = int((Height-5)/(fontSize+2));
    LoadFile(Filename);
    scrollbar->Repopulate(viewableLines, totalLines);
}

/// Sets the background color of the text box.
void cpTextBox::SetBackgroundColor(sf::Color color)
{
    cpObject::SetBackgroundColor(color);
    CreateRects(Label.GetText());
}

/// Sets the font style of the text: Bold, Italic, Underlined, Regular.
/// This uses SFML's font styles.
/// BEWARE: The current file will be reloaded in order to update
/// word wrap in case bolding your print changes the width too much.
void cpTextBox::SetFontStyle(unsigned long TextStyle)
{
    cpObject::SetFontStyle(TextStyle);
    LoadFile(Filename);
    scrollbar->Repopulate(viewableLines, totalLines);
}

/// Sets the font size of the text. The current font is
/// reloaded with the new size for better quality.
/// BEWARE: the current file will be reloaded in order to update
/// word wrap for the new font size. This could be time consuming
/// for very large files.
void cpTextBox::SetFontSize(unsigned int size)
{
    cpObject::SetFontSize(size);
    fontSize = (unsigned int)Label.GetSize();
    viewableLines = int((Height-5)/(fontSize+2));
    LoadFile(Filename);
    scrollbar->Repopulate(viewableLines, totalLines);
}

/// Sets the color of your text.
void cpTextBox::SetLabelColor(sf::Color color)
{
    cpObject::SetLabelColor(color);
    if (lineSFStrings.size() > 0)
    {
        for (unsigned int t=0; t < lineSFStrings.size(); t++)
            lineSFStrings[t].SetColor(color);
    }
}
#endif

#if 0

#include "cpGUI_base.h"
#include "cpTextInputBox.h"
using namespace cp;


/// ***********************************************************
/// Rudimentary text input box.  It only allows you to enter
/// the number of characters that the box can contain.  The
/// font size is tied to the height of the box, so you can't
/// change the font size.
///
/// You can set CP_TXT_LEFT_ALIGN, CP_TXT_RIGHT_ALIGN, or
/// CP_TXT_CENTER_ALIGN.  This simple text box does not
/// support text selection, but you can backspace.
/// ***********************************************************
cpTextInputBox::cpTextInputBox(sf::RenderWindow *parent, cpGuiContainer *GUI,
                               std::string label, float posx, float posy,
                               float width, float height, int Style) : cpObject(
                                           parent, GUI, label, posx, posy, width, height)
{
    backgroundColor = sf::Color::White;
    bTooBig = false;
    caretOn = true;
    elapsedTime = 0.f;
    SetFont(Font, (unsigned int)Height-2);
    Label.SetSize(Height-2);
    tempLabel = Label;
    tempText = Label.GetText();

    style = Style;
    if (style < CP_TXT_RIGHT_ALIGN || style > CP_TXT_CENTER_ALIGN)
        style = CP_TXT_LEFT_ALIGN;

    CreateRects(Label.GetText());

}

cpTextInputBox::cpTextInputBox() : cpObject(NULL, NULL, ""){}

/// Updates the look of the text input box.
/// Computes the text alignement and position of the
/// Caret/cursor.
void cpTextInputBox::CreateRects(std::string label)
{
    Label.SetText(label);
    Label.SetColor(textColor);
    Label.SetSize(Height-2);
    tempLabel = Label;

    float thickness = 1.f;
    backRect = sf::Shape::Rectangle(PosX, PosY, PosX+Width, PosY+Height,
                                    backgroundColor, thickness);
    for (int t=0; t<4; t++)
        backRect.SetPointOutlineColor(t, outlineColor);

    if (style == CP_TXT_RIGHT_ALIGN)
        Label.SetPosition(PosX+Width-Label.GetRect().GetWidth()-8, PosY-Height/6);
    if (style == CP_TXT_LEFT_ALIGN)
        Label.SetPosition(PosX+4, PosY-Height/6);
    if (style == CP_TXT_CENTER_ALIGN)
        Label.SetPosition(PosX+(Width/2)-(Label.GetRect().GetWidth()/2),
                          PosY-Height/6);

    caret = sf::Shape::Line(Label.GetPosition().x + Label.GetRect().GetWidth() + 3,
                            PosY+2, Label.GetPosition().x + Label.GetRect().GetWidth() + 3, PosY+Height-2,
                            1.f, sf::Color(50,50,50));

}

/// Draws the text input box. The cursor/caret is
/// drawn every .75 seconds
void cpTextInputBox::Draw()
{
    if (!bShow)
        return;

    Parent->Draw(backRect);
    Parent->Draw(Label);

    if (gui->clock.GetElapsedTime() - elapsedTime > 0.75)
    {
        elapsedTime = gui->clock.GetElapsedTime();
        caretOn = !caretOn;
    }

    if (hasFocus && caretOn)
        Parent->Draw(caret);
}

/// This function checks for mouse events within the control.
/// it updates the look of the control according to the event.
/// it also returns an integer enumeration member to inform the user.
/// possible return values are:
/// CP_ST_NONE, CP_ST_MOUSE_ENTER, CP_ST_MOUSE_EXIT,
/// CP_ST_MOUSE_IN, CP_ST_LBUTTON_DOWN, CP_ST_LBUTTON_RELEASED.
///
/// The difference between CP_ST_MOUSE_ENTER & CP_ST_MOUSE_IN
/// is that IN is active the entire time the mouse is inside the control
/// and ENTER is only active right when the mouse enters the control
int cpTextInputBox::CheckState(const sf::Input *input)
{
    int state = cpObject::CheckState(input);

    if (state == CP_ST_NONE)
    {
        if (hasFocus)
            outlineColor = sf::Color(90,90,230);
        else
            outlineColor = sf::Color::Black;
    }
    else
        outlineColor = outlineColorTemp;

    CreateRects(Label.GetText());
    return state;
}

/// This function is used within the Event loop.
/// This accepts text input and assigns it to
/// the Label if it fits in the box.
void cpTextInputBox::ProcessTextInput(sf::Event *evt)
{
    if (!hasFocus)
        return;
    if (evt->Type == sf::Event::TextEntered)
    {
        int textSize = tempText.size();
        unsigned short unicode = evt->Text.Unicode;

        if (unicode == 8) //If backspace
        {
            if (textSize > 0)
                tempText.erase(textSize - 1, 1);
        }
        else if (unicode >= 32 && unicode <= 126)
            tempText += (char)unicode;
        else if (unicode >= 192 && unicode <= 255)
            tempText += (char)unicode;
        return;
    }

    tempLabel.SetText(tempText);
    if (CheckTextFit())
        Label.SetText(tempText);
}

/// Limits the size of the Label to the size of the box
bool cpTextInputBox::CheckTextFit()
{
    if (tempLabel.GetRect().GetWidth() > Width - 8)
    {
        tempText.erase(tempText.size()-1, 1);
        return false;
    }
    return true;
}

/// Set the width & height dimensions of the text input box.
/// also reloads the font with the new font size for
/// better text quality
bool cpTextInputBox::SetSize(float width, float height)
{
    Width = width;
    Height = height;
    SetFont(Font, (unsigned int)Height-2);
    CreateRects(Label.GetText());
    return true;
}

/// Sets the coordinates for the position of the text input box
void cpTextInputBox::SetPosition(float posx, float posy)
{
    cpObject::SetPosition(posx, posy);
    CreateRects(Label.GetText());
}

/// The font can be changed, but the font size
/// is determined by the size of the box.
void cpTextInputBox::SetFont(std::string filename, unsigned int size)
{
    cpObject::SetFont(filename, (unsigned int)Height-2);
    CreateRects(Label.GetText());
}

/// Sets the text input box's background color
void cpTextInputBox::SetBackgroundColor(sf::Color color)
{
    cpObject::SetBackgroundColor(color);
    CreateRects(Label.GetText());
}

/// Sets the font's style: Bold, Italic, Underlined, Regular
void cpTextInputBox::SetFontStyle(unsigned long TextStyle)
{
    cpObject::SetFontStyle(TextStyle);
    CreateRects(Label.GetText());
}

/// Not available.  Font size is determined
/// by the box's height.
void cpTextInputBox::SetFontSize(unsigned int size)
{
}

/// Sets the color of the text
void cpTextInputBox::SetLabelColor(sf::Color color)
{
    cpObject::SetLabelColor(color);
    CreateRects(Label.GetText());
}

/// Sets the text displayed in the text input box
void cpTextInputBox::SetLabelText(std::string text)
{
    cpObject::SetLabelText(text);
    CreateRects(Label.GetText());
}

#endif
