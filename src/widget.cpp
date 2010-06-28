#include "widget.hpp"
#include "gui.hpp"

using namespace cp;

widget::widget():
        x( 0 ), y( 0 ), my_gui( &dummy::dummy_gui )
{
}

widget::~widget()
{
    disconnect();
}

void widget::draw( sf::RenderWindow& window ) const
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
