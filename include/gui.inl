#ifndef GUI_INL
#define GUI_INL

inline void cp::gui::handle_event( const sf::Event& event )
{
    // Pass the event down to the widgets, probably gonna have to go under
    // this switch statement
    switch ( event.Type )
    {
// Precompiler switch that turns of the default event handling code
// It must be defined before you include this
#ifndef CP_GUI_NO_DEFAULT_EVENTS
    case sf::Event::Closed:
        window.Close();
        break;
    case sf::Event::KeyPressed:
        switch ( event.Key.Code )
        {
        case sf::Key::Escape:
            window.Close();
            break;
        default:
            break;
        }
        break;
#endif
    default:
        break;
    }
}

inline const sf::RenderWindow& cp::gui::get_window() const
{
    return window;
}

#endif // GUI_CONTAINER_INL_INCLUDED
