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

#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <boost/ref.hpp>

// R0: I've been thinking about having the widgets cache an image in memory
// then just blit that during the gui.draw() function. Then just update their
// images whenever needed. May do that later.

namespace std
{
template< class Tp, class Alloc > class vector;
}

namespace cp
{

class gui;

class widget
{
public:
    ~widget();

    /// Draws the widget in the specified window
    ///
    /// \param  window: The window to draw in.
    ///
    virtual void draw( sf::RenderWindow& window ) const;

    /// Responds to an event.
    ///
    /// \param event:   The event to process.
    ///
    virtual void handle_event( const sf::Event& event );

    /// Used to set the location of where the gui stores this widget so that it
    /// may be removed during destruction.
    ///
    /// \param new_location:    Location to point to.
    ///
    void set_location( std::vector< boost::reference_wrapper<cp::widget> >::iterator new_location );
protected:
    int x; ///< The widget's horizontal position in screen coordinates.
    int y; ///< The widget's vertical position in screen coordinates.
    /// Location of widget in gui::widgets so it can tell gui to delete it
    std::vector< boost::reference_wrapper<cp::widget> >::iterator
    location;
};
}

#endif // WIDGET_HPP

/*----------------------------------------------------------------------------//
THIS IS THE OLD CODE BELOW
USED AS A REFERENCE
REMOVE BEFORE API IS RELEASED
//----------------------------------------------------------------------------*/

#if 0

#ifndef CP_OBJECT_H
#define CP_OBJECT_H

#include "cpGuiContainer.h"

namespace cp {
class cpObject
{
public:
    cpObject(sf::RenderWindow *parent, cpGuiContainer *GUI, std::string label,
             float posx=0, float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
    virtual bool SetSize(float width, float height);
    virtual void SetPosition(float posx, float posy);
    virtual void SetFont(std::string filename, unsigned int size);
    virtual void SetBackgroundColor(sf::Color color);
    virtual void SetFontStyle(unsigned long TextStyle);
    virtual void SetFontSize(unsigned int size);
    virtual void SetLabelColor(sf::Color color);
    virtual void SetLabelText(std::string text);
    virtual int CheckState(const sf::Input *input);
    virtual void Show(bool show);
    void SetFocus(bool focus);
    void SetMouseoverColor(sf::Color color);
    bool GetShow();
    sf::Vector2f GetSize();
    sf::Vector2f GetPosition();
    sf::Color GetBackgroundColor();
    sf::Color GetMouseoverColor();
    unsigned long GetFontStyle();
    sf::Color GetLabelColor();
    std::string GetLabelText();

    bool hasFocus, useWheel;
    int wheelDelta, keyCode;
    std::string Font;
    sf::Font *textFont;

protected:
    virtual void CreateRects(std::string label);
    bool CheckMouseEntered(const sf::Input *input);
    void DrawDashedLine(sf::Vector2f start, sf::Vector2f end);
    void DrawDashedRect(float posx, float posy, float width, float height);
    void SetUseWheel(bool use);

    float Width, Height, PosX, PosY, labelX, labelY;
    sf::RenderWindow* Parent;
    sf::Color backgroundColor, backgroundColorTemp, textColor, outlineColor;
    sf::Color outlineColorTemp, mouseoverColor;
    sf::String Label, tempLabel;
    sf::Shape backRect;
    bool bDefaultSize, mouseIn, lbuttonDown, returnDown, bShow;
    cpGuiContainer *gui;
};

}

#endif

#endif // #if 0
