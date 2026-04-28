/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_
#include <exception>
#include <string>

namespace {
    class Exception : public std::exception {
        public:
            Exception(const std::string &message) : _message(message) {}
            virtual ~Exception() noexcept = default;
            virtual const char* what() const noexcept override {
                return _message.c_str();
            }
        private:
            std::string _message;
    };

    class WarningException : public Exception {
        public:
            WarningException(const std::string &message) : Exception(message) {}
    };

    class ErrorException : public Exception {
        public:
            ErrorException(const std::string &message) : Exception(message) {}
    };

    class CrashException : public Exception {
        public:
            CrashException(const std::string &message) : Exception(message) {}
    };
}

#endif /* !EXCEPTION_HPP_ */
