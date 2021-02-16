#include "SDLException.hpp"

SDLException::SDLException(const std::string &msg) : msg(msg) {}

const char *SDLException::what() const noexcept {
	return msg.c_str();
}