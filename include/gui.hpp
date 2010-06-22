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

#include <SFML/Graphics.hpp> // Probably going to end up using lots of this
// reference_wrapper is used in an inlined function, don't think this can be
// forward declared, maybe inline is unnecessary as well
#include <boost/ref.hpp>

// See if forward declaring other classes will prevent us from having to include
// all the headers, so that the user can pick and choose which to include?
// Also forward declaring is preferable to including whole header files inside
// header files

// Forward declare small stuff so that user does not have to pull in
// headers they might not use
namespace std
{
template< class Tp, class Alloc > class vector;
}

namespace cp
{

// Forward declared classes
class widget;

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
    // What if the user wants to draw to more than 1 window?

    /// Passes the event to the widget with focus and handles default events.
    ///
    /// \param event:   The event to process
    ///
    void handle_event( const sf::Event& event ) const;
    // I don't think this should change any of its private contents

    /// Draws the entire GUI.
    ///
    void draw() const;
    // Probably should add error handling

    /// Adds a widget to the GUI
    ///
    void add( cp::widget& new_widget );
    // Still deciding how to design this part
    // Either dynamic binding or perhaps template mixed with typedef
    // Preferably static binding, i.e. compiler time
    // R0: The simplest solution would be to just use dynamic binding
    // Other methods may work but are more complicated and any increase in speed
    // is questionable. In the future this shouldn't change the API much/at all.
    // pdusen: It may be more appropriate to require widgets to be
    // allocated dynamically and contained in shared_ptrs; this can be
    // ensured using factory functions. Revisit this option later.

    /// Returns the attached window as read-only.
    ///
    const sf::RenderWindow& get_window() const;
    // May have function to retrun writable reference if necessary

    /// Gets a font loaded in the GUI.
    ///
    /// \param font:    The font to get
    ///
    const sf::Font& get_font( const std::string& font ) const;
    // What about case where font is not found?

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
    // References are preferred to make it impossible to add null pointers
    sf::RenderWindow& window; ///< The window that the GUI is attached to.
    std::vector< boost::reference_wrapper<cp::widget> >
    widgets; ///< Widgets of the GUI.
    // This may point to nothing if the GUI doesn't have any widgets
    // Don't think a special pointer is needed since not messing with
    // memory management
    widget* focused_widget;

#if 0
    // Incorporate the old font map design as a font_manager object
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
