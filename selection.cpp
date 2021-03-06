#include <QtAlgorithms>

#include "selection.h"
#include "debug.h"

selection selection::create_selection(int start, int size)
{
	selection s;
	s.set_start(start * 2);
	s.set_end((start + size) * 2);
	return s;
}

void selection::set_start(int s)
{
	start = s;
}

void selection::set_end(int e)
{
	end = e + 1;
	active = true;
}

int selection::get_start()
{
	return start > end ? end : start;
}

int selection::get_end()
{
	return start < end ? end : (start + 2);
}

int selection::get_start_byte()
{
	return get_start() / 2;
}

int selection::get_end_byte()
{
	return get_end() / 2;
}

int selection::get_start_aligned()
{
	return get_start() & ~1;
}


int selection::get_end_aligned()
{
	return get_end() & ~1;
}

void selection::move_end(int amount)
{
	end += amount;
}

int selection::range()
{
	return end - start + 1; //selections are inclusive of the last byte
}

int selection::byte_range()
{
	return (end - start + 1) / 2; //selections are inclusive of the last byte
}

bool selection::is_active()
{
	return active && get_start_byte() != get_end_byte();
}

void selection::set_active(bool a)
{
	active = a;
	if(!active){
		dragging = false;
	}
}

bool selection::is_dragging()
{
	return dragging;
}

void selection::set_dragging(bool d)
{
	dragging = d;
}
