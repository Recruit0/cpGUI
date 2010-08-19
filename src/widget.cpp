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

#include "widget.hpp"
#include "gui.hpp"

using namespace cp;

namespace cp
{
namespace dummy
{
cp::widget dummy_widget;
}
}

widget::widget( const boost::uint32_t new_x, const boost::uint32_t new_y ):
        x( new_x ), y( new_y ), my_gui( &dummy::dummy_gui )
{
}

widget::widget():
        x( 0 ), y( 0 ), my_gui( &dummy::dummy_gui )
{
}

widget::~widget()
{
    disconnect();
}

void widget::draw() const
{
}

void widget::handle_event( const sf::Event& new_event )
{
}

bool widget::contains( int check_x, int check_y ) const
{
    return 0;
}

void widget::connect_to( gui& new_gui )
{
    new_gui.connect( *this );
    my_gui = &new_gui;
}

void widget::disconnect()
{
    my_gui->disconnect( this );
    my_gui = &dummy::dummy_gui;
}
