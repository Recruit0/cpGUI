#ifndef GUI_CONTAINER_INL_INCLUDED
#define GUI_CONTAINER_INL_INCLUDED

inline void cp::gui::handle_event( const sf::Event& event )
{
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
}

#endif // GUI_CONTAINER_INL_INCLUDED
