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

/*
A menu is used to group widgets together.
Radio buttons, drop-down list, full list and bar? all classify as menu types
menu_list and menu_table
May need widget to widget connections. Signals and slots?
*/

#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <boost/cstdint.hpp>
#include <boost/gil/rgba.hpp>
#include <boost/gil/typedefs.hpp>

#include "widget.hpp"

namespace cp
{
/// Represents a list to choose from.
class menu: public widget
{
public:
    /// Adds an option to the list.
    ///
    /// \param new_widget: What widget to add.
    ///
    void add( cp::widget* const new_widget );

    /// Removes an option from the list. Does nothing if option does not exist.
    ///
    /// \param option: What option to remove.
    ///
    void remove( const boost::uint32_t option );

    /// Returns whether option is selected or not. If option does not exist then
    /// returns 0.
    ///
    /// \param option:  What option to check.
    ///
    bool is_selected( const boost::uint32_t option ) const;

    // Inherited functions
    virtual void draw() const;
    virtual void handle_event( const sf::Event& new_event );
    virtual bool contains( const int check_x, const int check_y ) const;

private:
    struct option
    {
        option( cp::widget* const new_widget );
        // Should probably use a smart pointer, not sure which one.
        widget* my_widget; // What widget the option is for.
        bool my_selected; // Whether it's selected or not.
    };

    bool resizable; // Whether it's resizable with mouse click.
    bool movable; // Whether it can be moved with mouse drag.
    // How many options can be selected at once. A negative value means no max.
    int max_selections;

    std::vector< option > my_options; // Choices up for selection.
    // What color to border selections with.
    boost::gil::rgba8_pixel_t my_selection_border_color;
    // What color to highlight selections with.
    boost::gil::rgba8_pixel_t my_selection_color;
    // What color to border mouse overs with.
    boost::gil::rgba8_pixel_t my_hover_border_color;
    // What color to fill mouse overs with.
    boost::gil::rgba8_pixel_t my_hover_fill_color;
    // What color to fill the widget with.
    boost::gil::rgba8_pixel_t my_fill_color;
    // What color the bounding box is.
    boost::gil::rgba8_pixel_t my_border_color;
    boost::uint32_t my_width; // The widget's width.
    boost::uint32_t my_height; // The widget's height.

    // Position of options relative to the menu.
    int my_options_x, my_options_y;
};
}

#endif

/*----------------------------------------------------------------------------//
THIS IS THE OLD CODE BELOW
USED AS A REFERENCE
REMOVE BEFORE API IS RELEASED
//----------------------------------------------------------------------------*/

/*namespace std
{
// Forward declare std::string
template<typename CharT, typename Traits, typename Alloc> class basic_string;
typedef basic_string<char> string;
template< class Tp, class Alloc > class vector;
}*/

#if 0

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
