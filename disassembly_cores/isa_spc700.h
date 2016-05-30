#ifndef ISA_SPC700_H
#define ISA_SPC700_H

#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QSet>

#include "disassembler_core.h"

class isa_spc700 : public disassembler_core
{
		friend class isa_spc700_ui;
	public:
		using disassembler_core::disassembler_core;

	protected:
		QString decode_name_arg(const char arg, int &size);
		QString address_to_label(int address);
		QString format_data_value(int size, int value, bool is_pointer);
		opcode get_opcode(int op);
		int get_base();
		bool is_unlikely_opcode(int op);
		void update_state(){}
		void set_flags(bookmark_data::types type){ Q_UNUSED(type); }
	private:		
		bool error_stop = false;

		static const QList<disassembler_core::opcode> opcode_list;
		static const QSet<unsigned char> unlikely;
		
		unsigned int base = 0x0500;
		
};

class isa_spc700_ui : public disassembler_core_ui
{
		Q_OBJECT
		friend class isa_spc700;
	public:
		explicit isa_spc700_ui(QObject *parent = 0);
		~isa_spc700_ui();
		QGridLayout *core_layout();

	public slots:
		void toggle_error_stop(bool state){ ((isa_spc700 *)disassembler())->error_stop = state; }
		void update_base(QString new_base);

	private:		
		QCheckBox *stop = new QCheckBox("Stop on unlikely");
		QLineEdit *base_input = new QLineEdit("0500");
		QLabel *base_text = new QLabel("Base address");
		
};

class isa_spc700_options : public disassembler_core_options
{
	using disassembler_core_options::disassembler_core_options;
};

struct isa_spc700_factory : public disassembler_core_factory
{
	using disassembler_core_factory::disassembler_core_factory;
	virtual disassembler_core *get_core(QObject *parent) { return new isa_spc700(parent); }
	virtual disassembler_core_ui *get_ui(QObject *parent) { return new isa_spc700_ui(parent); }
	virtual disassembler_core_options *get_options(QObject *parent) { return new isa_spc700_options(parent); }
};

static isa_spc700_factory factory("isa_spc700");

#endif // ISA_SPC700_H
