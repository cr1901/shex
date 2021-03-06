#ifndef HEX_EDITOR_H
#define HEX_EDITOR_H

#include "events/event_types.h"
#include "selection.h"
#include "rom_buffer.h"
#include "panels/bookmark_panel.h"

class hex_display;
class ascii_display;
class address_display;

class hex_editor : public QWidget
{
	Q_OBJECT
	public:
		explicit hex_editor(QWidget *parent, QString file_name, QUndoGroup *undo_group, bool new_file = false);
		~hex_editor();
		void set_focus();
		void compare(QString file);
		void close_compare();
		void goto_diff(bool direction);
		QString generate_patch();
		bool follow_selection(bool type);
		
		ROM_buffer *get_buffer(){ return buffer; }
		QVector<selection> *get_diff(){ return diffs; }
		QString load_error() { return ROM_error; }
		QString get_file_name() { return buffer->get_file_name(); }
		int get_relative_position(int address){ return cursor_nibble / 2 + address; }
		void save(QString path) { buffer->save(path); update_save_state(-save_state); }
		bool can_save(){ return save_state; }
		bool new_file(){ return is_new; }
		
		bool is_comparing(){ return comparing; }
		bool is_selecting(){ return selection_area.is_active(); }
		bool is_pasteable(){ return buffer->check_paste_data(); }
		
		int get_offset(){ return offset; }
		void set_offset(int o);
		
		int get_cursor_nibble(){ return cursor_nibble; }
		void set_cursor_nibble(int byte){ cursor_nibble = byte; update_window(); }
		
		selection get_selection(){ return selection_area; }
		void set_selection(selection s){ selection_area = s; update_window(); }
		
	signals:
		void update_slider(int position);
		void update_range(int value);
		void update_status_text(QString text);
		void toggle_scroll_mode(bool mode);
		void save_state_changed(bool save);
		void send_disassemble_data(selection selection_area, const ROM_buffer *buffer);
		void send_bookmark_data(int start, int end, const ROM_buffer *buffer);

	public slots:
		void update_window();
		void handle_typed_character(unsigned char key, bool update_byte = false);
		void update_undo_action(bool direction);
		void goto_offset(int address);
		void select_range(int start, int end);
		void slider_update(int position);
		void scroll_mode_changed();
		void context_menu(const QPoint& position);
		void cut();
		void copy();
		void paste(bool raw = false);
		void delete_text();
		void select_all();
		void branch();
		void jump();
		void disassemble();
		void create_bookmark();
		void count(QString find, bool mode);
		void search(QString find, bool direction, bool mode);
		void replace(QString find, QString replace, bool direction, bool mode);
		void replace_all(QString find, QString replace, bool mode);

	protected:
		virtual void keyPressEvent(QKeyEvent *event);
		virtual void wheelEvent(QWheelEvent *event);
		virtual bool event(QEvent *event);

	private:
		ROM_buffer *buffer;
		int offset = 0;
		
		hex_display *hex;
		ascii_display *ascii;
		address_display *address;
		
		bool comparing = false;
		ROM_buffer *compare_buffer = new ROM_buffer();
		address_display *compare_address;
		hex_display *compare_hex;
		ascii_display *compare_ascii;
		QVector<selection> *diffs = nullptr;
		
		QLabel *hex_header = new QLabel("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
		QLabel *address_header = new QLabel("Offset");

		bool scroll_mode = false;
		int save_state = 0;
		bool is_new;
		QString ROM_error = "";
		int cursor_nibble = 0;
		selection selection_area;
		
		static bool wheel_cursor;
		static bool prompt_resize;
		
		void handle_search_result(QString target, int result, bool mode);
		void calculate_diff();
		void update_save_state(int direction);
		QString get_status_text();
		void move_cursor_nibble(int delta);
		void update_nibble(char byte);
		void search_error(int error, QString find = "", QString replace_with = "");
		int get_max_lines();
		bool validate_resize();
};
#endif // HEX_EDITOR_H
