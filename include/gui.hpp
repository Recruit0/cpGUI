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

// ***NOTE***: Combined gui and base

#ifndef GUI_CONTAINER_H
#define GUI_CONTAINER_H

#include <vector>
#include <SFML/Graphics.hpp>

// See if forward declaring other classes will prevent us from having to include
// all the headers, so that the user can pick and choose which to include?

namespace cp
{

// Not sure if we still need all of this
enum
{
    DEFAULT = -1,
    ST_MOUSE_ENTER,
    ST_MOUSE_EXIT,
    ST_MOUSE_IN,
    ST_MOUSE_LBUTTON_DOWN,
    ST_MOUSE_LBUTTON_RELEASED,
    ST_CHANGED,
    ST_NONE,
    TEXT_RIGHT_ALIGN,
    TEXT_LEFT_ALIGN,
    TEXT_CENTER_ALIGN
};

/*
class cpObject;
*/

/// The top level class that represents the GUI.
///
class gui
{
public:
    /// Constructor that stores what window the GUI belongs to.
    ///
    /// \param referenced_window:   SFML rendering window to draw in.
    ///
    gui( sf::RenderWindow& referenced_window );
    // Thought about multiple windows but a GUI should belong to 1 window

    /// Passes the event down to its sub components.
    ///
    /// \param event:   The event to process
    ///
    void handle_event( const sf::Event& event );

    /// Draws the entire GUI.
    ///
    void draw();

    /// Adds a widget to the GUI
    ///
    void add( /*widget*/ );
    // Still deciding how to design this part
    // Either dynamic binding or perhaps template mixed with typedef
    // Preferably static binding, i.e. compiler time

    /// Returns the attached window as read-only.
    ///
    const sf::RenderWindow& get_window() const;
    // May have function to retrun writable reference if necessary

    /// Gets a font loaded in the GUI.
    ///
    /// \param font:    The font to get
    ///
    const sf::Font& get_font( const std::string& font ) const;

#if 0
    void Register(cpObject* object);
    void Unregister(cpObject* object);
    void SetObjectFocus(cpObject* object, bool focused);
    void NextObjectFocus();
    void AcceptsKeys(bool accept, bool UseArrowKeys);
    void ProcessKeys(sf::Event *evt);
    void Show(bool show);
    bool GetShow();
    void ReleaseUnusedFonts();
    sf::Font* GetFont(std::string filename, unsigned int fontSize=20);

    std::vector<cpObject*> control;
    std::string defaultFilename;
    bool acceptsKeys, useArrowKeys, bShow;
    sf::Clock clock;
#endif

private:
    sf::RenderWindow& window; ///< The window that the GUI is attached to
    std::vector<sf::Font> fonts; ///< Loaded fonts
    // I don't think fonts need to be in a map, they aren't going to change
    // that often.
    // Also make it an ordered array to speed of searching

    // Recruit0: We may be able to incorporate the old FontMap design into
    // the new API, if it is the most efficient solution
#if 0
    typedef std::map<std::string, FontData> FontMap;
    std::map<std::string, FontData> fontMap;
    short rightleft;
    sf::Font *defaultFont;
#endif
};

}

#include "gui.inl"

#endif



#if 0

#ifndef CPGUI_BASE
#define CPGUI_BASE


#include <cmath>
#include <cstring>

#include <fstream>
#include <map>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>


namespace cpGUI
{

enum
{
    DEFAULT = -1,
    ST_MOUSE_ENTER,
    ST_MOUSE_EXIT,
    ST_MOUSE_IN,
    ST_MOUSE_LBUTTON_DOWN,
    ST_MOUSE_LBUTTON_RELEASED,
    ST_CHANGED,
    ST_NONE,
    TXT_RIGHT_ALIGN,
    TXT_LEFT_ALIGN,
    TXT_CENTER_ALIGN
};


struct FontData
{
    sf::Font *myFont;
    short timesUsed;
};


}
*/

#endif

#endif
