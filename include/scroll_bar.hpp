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

// This does not need to be a separate object. A widget does not need multiple
// horizontal/vertical scroll bars.

/*----------------------------------------------------------------------------//
THIS IS THE OLD CODE BELOW
USED AS A REFERENCE
REMOVE BEFORE API IS RELEASED
//----------------------------------------------------------------------------*/

#if 0

#ifndef CP_SCROLL_BAR_H
#define CP_SCROLL_BAR_H

#include "cpGuiContainer.h"
#include "cpButton.h"

namespace cp {
	class cpScrollBar
	{
	public:
		cpScrollBar();
		cpScrollBar(sf::RenderWindow *parent, cpGuiContainer *GUI, float length,
			int ViewableLines, int TotalLines, float posx, float posy);
		~cpScrollBar();
		void Draw();
		int CheckState(const sf::Input *input);
		void MoveSlider(short direction);
		void Repopulate(int ViewableLines, int TotalLines);
		void SetPosition(float posx, float posy);
		void SetSize(float length, int ViewableLines);

	private:
		void MoveLines();
		void CreateRects();
		void CheckSliderValid();
		bool CheckMouseEntered(const sf::Input *input);
		int CheckMouseSlider(const sf::Input *input);

		sf::RenderWindow *Parent;
		sf::Shape groove, sliderShape, upArrow, downArrow, line1, line2, line3;
		sf::Clock clock, clock2;
		sf::Color backgroundColor, backgroundColor2;
		cpGuiContainer *gui;
		cpButton *upButton, *downButton;
		float Length, PosX, PosY, lineInc, currentPosition, slLength, mouseY;
		int viewableLines, totalLines;
		bool mouseDown, clickGroove, sliderDrag, slDown;
	};
}

#endif

#endif
