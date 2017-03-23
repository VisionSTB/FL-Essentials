/*********************************************************************************
created:	2017/01/29   02:58AM
filename: 	Fle_InputSlider.h
file base:	Fle_InputSlider
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized FLTK slider with input.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_InputSlider.h"

using namespace R3D;

Fle_InputSlider::Fle_InputSlider(int _x, int _y, int _w, int _h, const char* _l /*= 0*/, int _textbox_width) : 
Fl_Group(_x, _y, _w, _h, _l)
{
	p_slider = new Fl_Slider(_x, _y, _w - _textbox_width, _h);
	p_slider->callback(slider_cb_, (void*)this);

	p_input = new Fl_Int_Input(_x + _w - _textbox_width, _y, _textbox_width, _h);
	p_input->callback(input_cb_, (void*)this);
	p_input->when(FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED);

	box(FL_UP_BOX);
	align(FL_ALIGN_LEFT);
	type(FL_HOR_SLIDER);
	labelsize(13);
	textsize(13);
	value(1);
	bounds(1, 100);
	step(1);
	color(fl_rgb_color(240, 240, 240));
	selection_color(fl_rgb_color(144, 200, 246));

	end();
}

void Fle_InputSlider::slider_cb()
{
	static int recurse = 0;
	if (recurse) return;
	else
	{
		recurse = 1;
		char s[80];
		sprintf(s, "%d", static_cast<int>(p_slider->value() + 0.5));
		p_input->value(s);          // pass slider's value to input
		recurse = 0;
	}
}

void Fle_InputSlider::slider_cb_(Fl_Widget* _w, void* _p)
{
	static_cast<Fle_InputSlider*>(_p)->slider_cb();
}

void Fle_InputSlider::input_cb()
{
	static int recurse = 0;
	if (recurse) return;
	else
	{
		recurse = 1;
		int val = 0;
		if (sscanf(p_input->value(), "%d", &val) != 1)
			val = 0;
		p_slider->value(val);
		recurse = 0;
	}
}

void Fle_InputSlider::input_cb_(Fl_Widget* _w, void* _p)
{
	static_cast<Fle_InputSlider*>(_p)->input_cb();
}

void Fle_InputSlider::box(Fl_Boxtype _type)
{
	p_slider->box(_type);
	p_input->box(_type);
}
Fl_Boxtype Fle_InputSlider::box() const
{
	return p_slider->box();
}

void Fle_InputSlider::type(uchar _t)
{
	p_slider->type(_t);
}
uchar Fle_InputSlider::type() const
{
	return p_slider->type();
}

void Fle_InputSlider::value(int _val)
{
	p_slider->value(_val); 
	slider_cb();
}

int Fle_InputSlider::value() const
{
	return (static_cast<int>(p_slider->value() + 0.5));
}

int Fle_InputSlider::minimum() const
{
	return (static_cast<int>(p_slider->minimum()));
}

void Fle_InputSlider::minimum(int val)
{
	p_slider->minimum(val);
}

int Fle_InputSlider::maximum() const
{
	return (static_cast<int>(p_slider->maximum()));
}

void Fle_InputSlider::maximum(int val)
{
	p_slider->maximum(val);
}

void Fle_InputSlider::bounds(int low, int high)
{
	p_slider->bounds(low, high);
}

void Fle_InputSlider::step(int n)
{
	p_slider->step(n);
}

void Fle_InputSlider::textsize(int n)
{
	p_input->textsize(n);
}
int Fle_InputSlider::textsize() const
{
	return p_input->textsize();
}

void Fle_InputSlider::color(Fl_Color _c)
{
	p_slider->color(_c);
	p_input->color(_c);
}
Fl_Color Fle_InputSlider::color() const
{
	return p_slider->color();
}
void Fle_InputSlider::selection_color(Fl_Color _c)
{
	p_slider->selection_color(_c);
	p_input->selection_color(_c);
}
Fl_Color Fle_InputSlider::selection_color() const
{
	return p_slider->selection_color();
}
void Fle_InputSlider::textcolor(Fl_Color _c)
{
	p_input->textcolor(_c);
}
Fl_Color Fle_InputSlider::textcolor() const
{
	return p_input->textcolor();
}

Fl_Slider* Fle_InputSlider::getSlider() const
{
	return p_slider;
}
Fl_Int_Input* Fle_InputSlider::getInput() const
{
	return p_input;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
Fle_FloatInputSlider::Fle_FloatInputSlider(int _x, int _y, int _w, int _h, const char* _l /*= 0*/, int _textbox_width) : Fl_Group(_x, _y, _w, _h, _l)
{
	align(FL_ALIGN_LEFT);
	p_slider = new Fl_Slider(_x, _y, _w - _textbox_width, _h);
	p_slider->callback(sliderCallback_, (void*)this);

	p_input = new Fl_Float_Input(_x + _w - _textbox_width, _y, _textbox_width, _h);
	p_input->callback(inputCallback_, (void*)this);
	p_input->when(FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED);

	align(FL_ALIGN_LEFT);
	type(FL_HOR_SLIDER);
	labelsize(13);
	textsize(13);
	value(1);
	bounds(1, 100);
	step(0.1);
	color(fl_rgb_color(240, 240, 240));
	selection_color(fl_rgb_color(144, 200, 246));

	end();
}

void Fle_FloatInputSlider::sliderCallback()
{
	static int recurse = 0;
	if (recurse) return;
	else
	{
		recurse = 1;
		char s[80];
		sprintf(s, "%.2f", p_slider->value());
		p_input->value(s);          // pass slider's value to input
		recurse = 0;
	}
}

void Fle_FloatInputSlider::sliderCallback_(Fl_Widget* _w, void* _p)
{
	static_cast<Fle_FloatInputSlider*>(_p)->sliderCallback();
}

void Fle_FloatInputSlider::inputCallback()
{
	static int recurse = 0;
	if (recurse) return;
	else
	{
		recurse = 1;
		int val = 0;
		if (sscanf(p_input->value(), "%d", &val) != 1)
			val = 0;
		p_slider->value(val);
		recurse = 0;
	}
}

void Fle_FloatInputSlider::inputCallback_(Fl_Widget* _w, void* _p)
{
	static_cast<Fle_FloatInputSlider*>(_p)->inputCallback();
}

void Fle_FloatInputSlider::box(Fl_Boxtype _type)
{
	p_slider->box(_type);
	p_input->box(_type);
}
Fl_Boxtype Fle_FloatInputSlider::box() const
{
	return p_slider->box();
}
void Fle_FloatInputSlider::type(uchar _t)
{
	p_slider->type(_t);
}
uchar Fle_FloatInputSlider::type() const
{
	return p_slider->type();
}
void Fle_FloatInputSlider::value(double _val)
{
	p_slider->value(_val);
	sliderCallback();
}

double Fle_FloatInputSlider::value() const
{
	return p_slider->value();
}

double Fle_FloatInputSlider::minimum() const
{
	return p_slider->minimum();
}

void Fle_FloatInputSlider::minimum(double val)
{
	p_slider->minimum(val);
}

double Fle_FloatInputSlider::maximum() const
{
	return p_slider->maximum();
}

void Fle_FloatInputSlider::maximum(double val)
{
	p_slider->maximum(val);
}

void Fle_FloatInputSlider::bounds(double low, double high)
{
	p_slider->bounds(low, high);
}

void Fle_FloatInputSlider::step(double n)
{
	p_slider->step(n);
}

void Fle_FloatInputSlider::textsize(int n)
{
	p_input->textsize(n);
}
int Fle_FloatInputSlider::textsize() const
{
	return p_input->textsize();
}
void Fle_FloatInputSlider::color(Fl_Color _c)
{
	p_slider->color(_c);
	p_input->color(_c);
}
Fl_Color Fle_FloatInputSlider::color() const
{
	return p_slider->color();
}
void Fle_FloatInputSlider::selection_color(Fl_Color _c)
{
	p_slider->selection_color(_c);
	p_input->selection_color(_c);
}
Fl_Color Fle_FloatInputSlider::selection_color() const
{
	return p_slider->selection_color();
}
void Fle_FloatInputSlider::textcolor(Fl_Color _c)
{
	p_input->textcolor(_c);
}
Fl_Color Fle_FloatInputSlider::textcolor() const
{
	return p_input->textcolor();
}

Fl_Slider* Fle_FloatInputSlider::getSlider() const
{
	return p_slider;
}
Fl_Float_Input* Fle_FloatInputSlider::getInput() const
{
	return p_input;
}