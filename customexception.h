#ifndef LAB7_CUSTOMEXCEPTION_H
#define LAB7_CUSTOMEXCEPTION_H
#include <exception>

class IOException: public std::exception {
public:
    virtual const char* what() const noexcept{
        return "Couldn't open the file.\n";
    }
};

class AddException: public std::exception{
public:
    virtual const char* what() const noexcept {
        return "Question already added.\n";
    }
};

#endif //LAB7_CUSTOMEXCEPTION_H
