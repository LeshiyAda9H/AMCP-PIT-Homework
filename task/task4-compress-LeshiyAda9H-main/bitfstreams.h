#ifndef BITFSTREAMS
#define BITFSTREAMS

#include <fstream>

class ibitfstream : public std::ifstream {
    unsigned char buffer;
    unsigned char bitcount;
public:
    ibitfstream(const char* filename) : buffer(0), bitcount(0),
        std::ifstream(filename, std::ios_base::binary){}
   
    int getbit() {
        if (bitcount == 8) { 
            bitcount = 0;
        }
        if (bitcount == 0) { 
            buffer = get();
        }
        int result = ((buffer & (1 << (7 - bitcount))) != 0) ? 1 : 0;

        ++bitcount;
        return result;
    }
   
    bool eof() {
        if (bitcount > 0 && bitcount < 8) { 
            return false;
        }
        
        if (peek() != EOF) {
            return false;
        }
        return true;
    }
};

class obitfstream : public std::ofstream {
    unsigned char buffer;
    unsigned char bitcount;
public:
    obitfstream(const char* filename) : std::ofstream(filename, std::ios_base::binary),
        bitcount(0), buffer(0) {}
    
    void putbit(bool x) {
        unsigned char ch = static_cast<unsigned char> (x);
        buffer |= (ch << (7 - bitcount));
        ++bitcount;
        if (bitcount == 8) {
            put((char)buffer); 
            buffer = 0;
            bitcount = 0;
        }
    }

    void cleanBuf(){
        if (bitcount > 0) { 
            put((char)buffer); 
        }
        bitcount = 0;
        buffer = 0;
    }

    void close() {
        cleanBuf();
        std::ofstream::close();
    }
};

#endif