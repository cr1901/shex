#ifndef SELECTION_H
#define SELECTION_H

class selection{
	public:
		void set_start(int s);
		void set_end(int e);
		int get_start();
		int get_end();
		void move_end(int amount);
		int drag_direction();
		int range();
		bool is_active();
		void set_active(bool a);
		bool is_dragging();
		void set_dragging(bool d);
	private:
		int start = 0;
		int end = 0;
		bool active = false;
		bool dragging = false;
};

#endif // SELECTION_H