#ifndef LIST_BOX_HPP_INCLUDED
#define LIST_BOX_HPP_INCLUDED

#include "menu.hpp"

namespace cp
{
class list_box: public menu
{
public:
    // Add constructor to set settings

    /// Adds a line of text as an option.
    ///
    /// \param text: What text to add.
    ///
    void add( const std::string& text );

private:

};
}

#endif // LIST_BOX_HPP_INCLUDED
