#ifndef SDLEXCEPTION_HPP
#define SDLEXCEPTION_HPP

#include <exception>
#include <string>

class SDLException : public std::exception {

public:
  explicit SDLException(const std::string &msg);

  const char *what() const noexcept override;

private:
  const std::string msg;
};

#endif // SDLEXCEPTION_HPP