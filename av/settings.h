#ifndef SETTINGS_H
#define SETTINGS_H

#include <cassert>
#include <map>
#include <string>
#include <vector>

#include <tclap/Arg.h>

/* arg variant */
template <typename T>
class FancyArg : protected TCLAP::Arg {
	enum Kind { MULTI, SWITCH, VALUE } kind;
	union Result {
		std::vector<T> *multiple_values;
		int switches;
		T *single_value;
	} value;
public:
	typedef Result wrapper_type;
	FancyArg() : Arg("", "", "", false, false, NULL), kind(SWITCH) { }
	explicit FancyArg(const Arg &base) :
		Arg(base._flag, base._name, base._description, base._required, base._valueRequired, base._visitor),
		kind(SWITCH)
	{
		value.switches = 0;
	}
	FancyArg(const FancyArg<T> &rhs) : Arg(rhs), kind(rhs.kind), value(rhs.value) { }
	virtual ~FancyArg(void) {
		switch (kind) {
		case MULTI:
			delete value.multiple_values;
			break;
		case VALUE:
			delete value.single_value;
			break;
		default:
			break;
		}
	}
	operator bool() {
		assert(kind == SWITCH);
		return (value.switches != 0);
	}
	bool processArg(int *, std::vector<std::string> &) {
		return true;
	}
};

class Settings {
	typedef FancyArg<std::string> arg_t;
	typedef std::map<std::string, arg_t> map_t;
	map_t arguments;
public:
	explicit Settings() { }
	virtual ~Settings() { }
	void add_switch(const std::string&, const std::string&);
	void parse(int, char *[]);
	template <typename T> const T* value(const std::string &);
};

#endif /* SETTINGS_H */
