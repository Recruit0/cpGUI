#include "list_box.hpp"
#include "text_box.hpp"

using namespace cp;
using namespace std;

void list_box::add( const std::string& text )
{
    menu::add( text_box( text ) ); // Position correctly
}
