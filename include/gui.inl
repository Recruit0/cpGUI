#ifndef GUI_INL
#define GUI_INL

inline const sf::RenderWindow& cp::gui::get_window() const
{
    return my_window;
}

inline sf::RenderWindow& cp::gui::reference_window()
{
    return my_window;
}

inline const cp::widget* cp::gui::get_focused_widget() const
{
    return my_focused_widget;
}

#endif
