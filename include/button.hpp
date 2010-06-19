// cpGUI 
// 
// Copyright (c) 2009 Jason Cupp
// Copyright 2010 Patrick VanDusen
//
//This software is provided 'as-is', without any express or implied warranty. 
//In no event will the authors be held liable for any damages arising from the 
//use of this software.
//
//Permission is granted to anyone to use this software for any purpose, including 
//commercial applications, and to alter it and redistribute it freely, subject to 
//the following restrictions:
//
//
//1. The origin of this software must not be misrepresented; you must not claim 
//that you wrote the original software. If you use this software in a product, an 
//acknowledgment in the product documentation would be appreciated but is not required.
//
//
//2. Altered source versions must be plainly marked as such, and must not be 
//misrepresented as being the original software.
//
//
//3. This notice may not be removed or altered from any source distribution.

// ***NOTE***: Combined image_button and shape_button into just button


namespace cpGUI
{
class button
{
public:

private:

};
}


#ifndef CP_BUTTON_H
#define CP_BUTTON_H

#include "cpObject.h"
#include "cpGuiContainer.h"

namespace cp {
	class cpButton : public cpObject
	{
	public:
		cpButton();
		cpButton(sf::RenderWindow* parent, cpGuiContainer *GUI, std::string label, 
			float posx=0, float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
		virtual void Draw();
		virtual bool SetSize(float width, float height);
		void SetPosition(float posx, float posy);
		void SetFont(std::string filename, unsigned int size);
		void SetBackgroundColor(sf::Color color);
		void SetFontStyle(unsigned long TextStyle);
		void SetFontSize(unsigned int size);
		void SetLabelColor(sf::Color color);
		void SetLabelText(std::string text);
		void Show(bool show);
		virtual int CheckState(const sf::Input *input);

	protected:
		virtual void CreateRects(std::string label);
		void TestLabelFit();

		sf::Color backgroundColor2;
		sf::Color backgroundColor2Temp;

		sf::Shape gradient;
		bool labelInside;
	};
}

#endif


#ifndef CPIMAGEBUTTON
#define CPIMAGEBUTTON

#include "cpGUI_base.h"
#include "cpObject.h"

namespace cp
{
	class cpImageButton : public cpObject
	{
	public:
		cpImageButton();
		cpImageButton(sf::RenderWindow *parent, cpGuiContainer *GUI, 
			sf::Image *image, float posx=0, float posy=0);
		void Draw();
		int CheckState(const sf::Input *input);
		bool SetSize(float width, float height);
		void SetPosition(float posx, float posy);
		void SetBackgroundColor(sf::Color color);
		void SetImage(sf::Image *image);
		void Show(bool show);

	private:
		sf::Sprite sprite;
	};
}

#endif



#ifndef CPSHAPEBUTTON
#define CPSHAPEBUTTON

#include "cpGUI_base.h"
#include "cpObject.h"

namespace cp
{
	class cpShapeButton : public cpObject
	{
	public:
		cpShapeButton(sf::RenderWindow *parent, cpGuiContainer *GUI, sf::Shape *shape,
			float posx=0, float posy=0);
		cpShapeButton();
		void Draw();
		int CheckState(const sf::Input *input);
		void SetPosition(float posx, float posy);
		void SetShape(sf::Shape *shape);

		bool SetSize(float width, float height);
		void SetFont(std::string filename, unsigned int size);
		void SetBackgroundColor(sf::Color color);
		void SetFontStyle(unsigned long TextStyle);
		void SetFontSize(unsigned int size);
		void SetLabelColor(sf::Color color);
		void SetLabelText(std::string text);

	private:
		void CreateRects(std::string label);
		void ComputeRectDimensions();

		sf::Shape *button;
		float relX, relY;
	};
}

#endif
