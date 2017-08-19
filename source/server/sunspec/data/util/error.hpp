//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (C) 8/18/17 Carlos Brito
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

//<editor-fold desc="Description">
/**
 * @file ${HEADER_FILENAME}
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 8/18/17.
 * 
 * @brief No description available.
 *
 */
//</editor-fold>
#ifndef SERVER_ERROR_HPP
#define SERVER_ERROR_HPP

#include <exception>
#include <string>

namespace sunspec
{
    namespace data
    {
        /**
         * @class DataPoint
         * @author Carlos Brito (carlos.brito524@gmail.com)
         * @date 8/17/17.
         *
         * @brief General class for an Error.
         */
        class Error : std::exception
        {
            std::string message;

        public:
            Error() = default;
            Error(const char* message) : message(message) {}
            Error(std::string message) : message(message) {}

            virtual const char* what() const throw()
            {
                return message.c_str();
            }
        };

        class XMLError : public Error
        {
        public:
            XMLError(std::string message) : Error(message) {}
        };
    }
}


#endif //SERVER_ERROR_HPP