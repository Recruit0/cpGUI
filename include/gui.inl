#ifndef GUI_INL
#define GUI_INL

inline void cp::gui::handle_event( const sf::Event& event ) const
{
    // First, pass the event to the widget with focus

    // This is the default even handler
#ifndef CP_GUI_NO_DEFAULT_EVENTS // Switch off default event handler
    switch ( event.Type )
    {
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
    default:
        break;
    }
#endif // CP_GUI_NO_DEFAULT_EVENTS
}

inline const sf::RenderWindow& cp::gui::get_window() const
{
    return window;
}

#endif // GUI_CONTAINER_INL_INCLUDED
