#ifndef UTIL_HPP
#define UTIL_HPP

#include <SDL.h>
#include <array>
#include <boost/program_options.hpp>
#include <fstream>
#include <string>

std::string getPath(const std::string &subDir, const std::string &dir);

std::string getResourcePath(const std::string &subDir = "");

std::string getMapsPath(const std::string &subDir = "");

std::string getBasePath(const std::string &subDir);

template <typename T>
T getArg(const std::string &name) {
	namespace po = boost::program_options;

	std::string level;
	std::string drawMode;
	po::options_description config("Configuration");
	config.add_options()("drawBoundingBox", po::value<bool>()->default_value(false))(
	    "showStatus", po::value<bool>()->default_value(false))("SPDLOG_LEVEL",
	                                                           po::value<std::string>(&level)->default_value("info"))(
	    "drawMode", po::value<std::string>(&drawMode)->default_value("full"))(
	    "sound", po::value<bool>()->default_value(true))("godMode", po::value<bool>()->default_value(false));

	po::variables_map values;
	std::string settings = getBasePath("") + "settings.ini";
	std::ifstream iniFile(settings);
	po::store(parse_config_file(iniFile, config), values);
	notify(values);

	return values[name].as<T>();
}

int randomInt(int lower, int upper);

#endif
