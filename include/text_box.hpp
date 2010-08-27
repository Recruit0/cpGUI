/*----------------------------------------------------------------------------//
cpGUI - a GUI tool kit with SFML as its primary back-end.

Copyright (c) 2009 Jason Cupp
Copyright (c) 2010 Patrick VanDusen, Alvin Fagan

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

// NOTE: SFML dependencies should be kept to a minimum in order make it easier
// to make the library software independent (i.e. be able to use SDL or Allegro)

// ***NOTE***: Combined text_box and text_input_box

#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <SFML/Graphics.hpp>
#include <boost/cstdint.hpp>
// Recruit0: Tried to forward declare this, traced it through 3 files and
// decided to just include it for now
#include <boost/gil/rgba.hpp>
#include <boost/gil/typedefs.hpp>
// I don't think this can be forward declared, tried and failed
#include "widget.hpp"

namespace cp
{

/*
Am considering whether to use inheritance (create widget class)
Or use template with typedef
Add option to bold, underline, etc.
Maybe add AA option later
*/
/// Represents a text box.
class text_box : public widget
{
public:
    // Possibly too many arguments.
    text_box( const std::string& new_text,
              const int x = 0, const int y = 0,
              const boost::uint32_t width = 0,
              const boost::uint32_t height = 0,
              const boost::gil::rgba8_pixel_t new_text_color
              = boost::gil::rgba8_pixel_t( 0, 0, 0, 255 ),
              const boost::gil::rgba8_pixel_t new_fill_color
              = boost::gil::rgba8_pixel_t( 128, 128, 128, 255 ),
              const boost::gil::rgba8_pixel_t new_border_color
              = boost::gil::rgba8_pixel_t( 0, 0, 0, 255 )  );

    /// Loads a file as the text.
    ///
    /// \param file_name:   The file to load.
    ///
    void load_file( const std::string& file_name );

    /// Sets size of text box.
    ///
    /// \param new_width:   Width of box.
    /// \param new_height:  Height of box.
    ///
    void set_size( const boost::uint32_t new_width,
                   const boost::uint32_t new_height );

    /// Gets the text string.
    ///
    const std::string& get_text() const;

    // Inherited functions
    void draw() const;
    void handle_event( const sf::Event& new_event );
    bool contains( const int x, const int y ) const;

private:
    // Caret position handlers so that caret always stays inside box
    void increase_caret_position();
    void decrease_caret_position();

    bool my_resizable; // Whether it's resizable with mouse click.
    bool my_movable; // Whether it can be moved with mouse drag.
    bool my_writable; // Whether it can be edited.

    std::string my_text; // The text of this box.
    // What color to draw the text in.
    boost::gil::rgba8_pixel_t my_text_color;
    // What color to fill the widget with.
    boost::gil::rgba8_pixel_t my_fill_color;
    // What color the bounding box is.
    boost::gil::rgba8_pixel_t my_border_color;
    boost::uint32_t my_caret_position; // Position of caret in the text.

    int my_text_x; // Text's x position.
    int my_text_y; // Text's y position.

    // TODO: Add scroll bar
};

}

#endif

/*----------------------------------------------------------------------------//
THIS IS THE OLD CODE BELOW
USED AS A REFERENCE
REMOVE BEFORE API IS RELEASED
//----------------------------------------------------------------------------*/

/*namespace boost
{
namespace gil
{
template < typename ChannelValue, typename Layout > class pixel;
}
}*/

#if 0

// Start - Removed new code

namespace std
{
// Forward declare std::string
template<typename CharT, typename Traits, typename Alloc> class basic_string;
typedef basic_string<char> string;
}

// End - Removed new code

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
