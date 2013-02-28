#include <tclap/Arg.h>
#include <tclap/SwitchArg.h>

#include "settings.h"

using std::string;

void
Settings::add_switch(const string &text, const string &desc)
{
	map_t::iterator itr = arguments.find(text);
	if (itr == arguments.end()) {
		char c = text.empty() ? '-' : text[0];
		TCLAP::SwitchArg arg(c, text, desc);
		arguments[text] = arg_t(arg);
	}
}

template <typename T> const T *
Settings::value(const string &key)
{
	map_t::iterator itr = arguments.find(key);
	if (itr != arguments.end()) {
		// somehow extract the correct type
	}
	return NULL;
}

#include <tclap/CmdLine.h>
#include "log.h"

#define AV_NAME    "compo$er"
#define AV_VERSION "v0.0.1"

void
Settings::parse(int argc, char *argv[])
{
	try {
		TCLAP::CmdLine parser(AV_NAME, ' ', AV_VERSION, true);
		/* Stage 1: Inform parser */
		map_t::iterator itr = arguments.begin();
		while (itr != arguments.end()) {
			parser.add(itr->second);
		}
		/* Stage 2: Extract options */
		parser.parse(argc, argv);
	} catch (TCLAP::ArgException &e) {
		/* TODO better error messages? */
		LOGE("%s (invalid argument)", e.what());
	}
}
