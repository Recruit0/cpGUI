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


// ***NOTE***: Combined image_button and shape_button together into just button

#include "button.hpp"
#include "functor.hpp"

using namespace sf;
using namespace cp;

button::button():
my_pressed( 0 ), my_callback( &dummy::dummy_functor )
{
}

bool button::is_pressed() const
{
    return my_pressed;
}

void button::handle_event( const sf::Event& new_event )
{
    switch( new_event.Type )
    {
        // Add case for mouse hovering
    case Event::MouseButtonPressed:
        if ( new_event.MouseButton.Button == Mouse::Left )
        {
            my_pressed = 1;
        }
        break;
    case Event::MouseButtonReleased:
        if ( new_event.MouseButton.Button == Mouse::Left )
        {
            my_pressed = 0;
            my_callback->run( *this );
        }
        break;
    default:
        break;
    }
}

#if 0

#include "cpGUI_base.h"
#include "cpImageButton.h"
using namespace cp;


/// ******************************************************************
/// A class of buttons that contain an image.
/// These buttons cannot be resized; the size is based on the
/// size of the image sent to it.  Also, there is no text label.
/// ******************************************************************
cpImageButton::cpImageButton(sf::RenderWindow *parent, cpGuiContainer *GUI,
                             sf::Image *image, float posx, float posy) : cpObject(parent,
                                         GUI, "", posx, posy, (float)image->GetWidth()+3,
                                         (float)image->GetHeight()+3)
{
    sprite.SetImage(*image);
    sprite.SetPosition(posx + 1, posy + 1);
}

cpImageButton::cpImageButton() : cpObject(NULL, NULL, "") {}

/// Clears the sprite and loads the new image into it.
/// the sprite is used to display the image in the button.
void cpImageButton::SetImage(sf::Image *image)
{
    Width = (float)image->GetWidth()+3;
    Height = (float)image->GetHeight()+3;
    sprite.SetImage(sf::Image());
    sprite.SetImage(*image);
    CreateRects("");
}

/// Draws the different parts that make up an image button
void cpImageButton::Draw()
{
    if(!bShow)
        return;

    Parent->Draw(backRect);
    Parent->Draw(sprite);

    if(hasFocus)
        DrawDashedRect(PosX+2, PosY+2, Width-4, Height-4);
}

/// This function checks for mouse events within the control.
/// it updates the look of the control according to the event.
/// it also returns an integer enumeration member to inform the user.
/// possible return values are:
/// CP_ST_NONE, CP_ST_MOUSE_ENTER, CP_ST_MOUSE_EXIT,
/// CP_ST_MOUSE_IN, CP_ST_LBUTTON_DOWN, CP_ST_LBUTTON_RELEASED.
///
/// The difference between CP_ST_MOUSE_ENTER & CP_ST_MOUSE_IN
/// is that IN is active the entire time the mouse is inside the control
/// and ENTER is only active right when the mouse enters the control
int cpImageButton::CheckState(const sf::Input *input)
{
    int state = cpObject::CheckState(input);

    if(state == CP_ST_MOUSE_LBUTTON_DOWN)
        backgroundColor = sf::Color(140, 140, 140);

    if(state == CP_ST_MOUSE_LBUTTON_RELEASED)
        backgroundColor = backgroundColorTemp;

    CreateRects("");
    return state;
}

/// Sets the image button's width & height dimensions
bool cpImageButton::SetSize(float width, float height)
{
    return false;
}

/// Sets the image button's position coordinates in the window
void cpImageButton::SetPosition(float posx, float posy)
{
    cpObject::SetPosition(posx, posy);
    CreateRects("");
}

/// Sets the image button's background color
void cpImageButton::SetBackgroundColor(sf::Color color)
{
    cpObject::SetBackgroundColor(color);
    CreateRects("");
}

/// Sets whether the image button is shown or hidden
void cpImageButton::Show(bool show)
{
    cpObject::Show(show);
    CreateRects("");
}
#endif

// Previously shape_button.cpp

#if 0

#include "cpGUI_base.h"
#include "cpShapeButton.h"
using namespace cp;


/// **************************************************************
/// A clickable button based on an sf::Shape.
/// **************************************************************
cpShapeButton::cpShapeButton(sf::RenderWindow *parent, cpGuiContainer *GUI, sf::Shape *shape,
                             float posx, float posy) : cpObject(parent, GUI, "", posx, posy)
{
    button = shape;
    ComputeRectDimensions();
    SetPosition(PosX, PosY);

}

cpShapeButton::cpShapeButton() : cpObject(NULL, NULL, "") {}

/// Sets the shape that makes the button
void cpShapeButton::SetShape(sf::Shape *shape)
{
    button = shape;
    ComputeRectDimensions();
    CreateRects(Label.GetText());
}

/// Draws the shape button
void cpShapeButton::Draw()
{
    if(!bShow)
        return;

    Parent->Draw(*button);
}

/// This function checks for mouse events within the control.
/// it updates the look of the control according to the event.
/// it also returns an integer enumeration member to inform the user.
/// possible return values are:
/// CP_ST_NONE, CP_ST_MOUSE_ENTER, CP_ST_MOUSE_EXIT,
/// CP_ST_MOUSE_IN, CP_ST_LBUTTON_DOWN, CP_ST_LBUTTON_RELEASED.
///
/// The difference between CP_ST_MOUSE_ENTER & CP_ST_MOUSE_IN
/// is that IN is active the entire time the mouse is inside the control
/// and ENTER is only active right when the mouse enters the control
int cpShapeButton::CheckState(const sf::Input *input)
{
    int state = cpObject::CheckState(input);
    if(state == CP_ST_NONE)
    {
        if(hasFocus)
            outlineColor = sf::Color(90,90,230);
        else
            outlineColor = sf::Color::Black;
    }
    else
        outlineColor = outlineColorTemp;


    CreateRects("");
    return state;
}

/// This function is unavailable in this class.
bool cpShapeButton::SetSize(float width, float height)
{
    return false;
}

/// Moves the shape button to new coordinates
void cpShapeButton::SetPosition(float posx, float posy)
{
    PosX = posx;
    PosY = posy;
    button->Move(PosX-relX, PosY-relY);
    relX = PosX;
    relY = PosY;
    CreateRects("");
}

/// Updates the look of the shape button
void cpShapeButton::CreateRects(std::string label)
{
    button->SetOutlineWidth(1.f);
    for(unsigned int t=0; t < button->GetNbPoints(); t++)
        button->SetPointOutlineColor(t, outlineColor);
}

/// Computes the width and height of the rectangle
/// that the shape fits in. Also the coordinates of
/// the top left corner
void cpShapeButton::ComputeRectDimensions()
{
    int left=0, right=0, top=0, bottom=0;
    for(unsigned int t=1; t < button->GetNbPoints(); t++)
    {
        if(button->GetPointPosition(t).x < button->GetPointPosition(t-1).x)
            left = t;
        if(button->GetPointPosition(t).x > button->GetPointPosition(t-1).x)
            right = t;
        if(button->GetPointPosition(t).y < button->GetPointPosition(t-1).y)
            top = t;
        if(button->GetPointPosition(t).y > button->GetPointPosition(t-1).y)
            bottom = t;
    }
    Width = button->GetPointPosition(right).x - button->GetPointPosition(left).x;
    Height = button->GetPointPosition(bottom).y - button->GetPointPosition(top).y;
    relX = button->GetPointPosition(left).x;
    relY = button->GetPointPosition(top).y;
}

/// This function is unavailable in this class
void cpShapeButton::SetFont(std::string filename, unsigned int size) {}

/// This function is unavailable in this class
void cpShapeButton::SetBackgroundColor(sf::Color color) {}

/// This function is unavailable in this class
void cpShapeButton::SetFontSize(unsigned int size) {}

/// This function is unavailable in this class
void cpShapeButton::SetFontStyle(unsigned long TextStyle) {}

/// This function is unavailable in this class
void cpShapeButton::SetLabelColor(sf::Color color) {}

/// This function is unavailable in this class
void cpShapeButton::SetLabelText(std::string text) {}

#endif
