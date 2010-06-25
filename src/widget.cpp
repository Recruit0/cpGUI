#include "widget.hpp"

using namespace cp;

widget::~widget()
{
}

void widget::draw( sf::RenderWindow& window ) const
{
}

void widget::handle_event( const sf::Event& event )
{
}

void widget::set_location( std::vector< boost::reference_wrapper<cp::widget> >::
                           iterator new_location )
{
    location = new_location;
}
