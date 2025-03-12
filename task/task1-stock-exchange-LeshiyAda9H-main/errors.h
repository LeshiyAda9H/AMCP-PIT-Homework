#ifndef ERRORS
#define ERRORS

#include <iostream>

class WrongFormatDate : public std::invalid_argument {
public:
    WrongFormatDate(const char* out) : std::invalid_argument(out) {}
};

class WrongFormatTime : public std::invalid_argument {
public:
    WrongFormatTime(const char* out) : std::invalid_argument(out) {}
};

class WrongValueTime : public std::invalid_argument {
public:
    WrongValueTime(const char* out) : std::invalid_argument(out) {}
};

class WrongValueMonth : public std::invalid_argument {
public:
    WrongValueMonth(const char* out) : std::invalid_argument(out) {}
};

class WrongValueDay : public std::invalid_argument {
public:
    WrongValueDay(const char* out) : std::invalid_argument(out) {}
};

class WrongType : public std::invalid_argument {
public:
    WrongType(const char* out) : std::invalid_argument(out) {}
};



#endif // !ERRORS
