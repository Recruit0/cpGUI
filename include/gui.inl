#ifndef GUI_INL
#define GUI_INL

inline const sf::RenderWindow& cp::gui::get_window() const
{
    return window;
}

inline sf::RenderWindow& cp::gui::reference_window()
{
    return window;
}

inline const cp::widget* cp::gui::get_focused_widget() const
{
    return focused_widget;
}

#endif
