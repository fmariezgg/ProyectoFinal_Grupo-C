#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdarg>

//Emilio se hizo su propia libreria para hacer un monton de cosas, incluyendo darle colores a la consola sin usar windows.h
//link del resto de la libreria: https://github.com/LemonpieGBS/LemonLib

#ifdef _WIN32
#include <windows.h>
void CSB_VIRTUAL_PROCESSING() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

namespace LLC
{

    enum COLORS
    {

        cBLACK = 0,
        cDARK_RED = 88,
        cRED = 196,
        cBLUE = 4,
        cDARK_BLUE = 18,
        cPURPLE = 129,
        cDARK_PUPLE = 55,
        cCYAN = 51,
        cTEAL = 33,
        cWHITE = 15,
        cGRAY = 8,
        cYELLOW = 226,
        cDARK_YELLOW = 142,
        cORANGE = 214,
        cDARK_ORANGE = 202,
        cPINK = 197,
        cDARK_PINK = 125,
        cGREEN = 46,
        cDARK_GREEN = 28,
        cAQUA = 47,
        cDARK_AQUA = 29

    };

    enum BACKGROUNDS
    {

        bgBLACK = 0,
        bgDARK_RED = 88,
        bgRED = 196,
        bgBLUE = 4,
        bgDARK_BLUE = 18,
        bgPURPLE = 129,
        bgDARK_PUPLE = 55,
        bgCYAN = 51,
        bgTEAL = 33,
        bgWHITE = 15,
        bgGRAY = 8,
        bgYELLOW = 226,
        bgDARK_YELLOW = 142,
        bgORANGE = 214,
        bgDARK_ORANGE = 202,
        bgPINK = 197,
        bgDARK_PINK = 125,
        bgGREEN = 46,
        bgDARK_GREEN = 28,
        bgAQUA = 47,
        bgDARK_AQUA = 29

    };

    enum STATES
    {

        stBOLD = 1,
        stITALIC = 3,
        stUNDERLINE = 4,
        stSTRIKETHROUGH = 9

    };

    enum RESET_TYPES
    {

        rtFULL = 0,
        rtCOLOR = 1,
        rtSTATES = 2,
        rtBACKGROUND = 3

    };

    void _colSET(COLORS col) { printf("\033[38;5;%dm", col); }
    void _colRESET() { std::cout << "\033[39m"; }

    void _stateSET(STATES st) { printf("\033[%dm", st); }
    template <typename... ARGS> void _stateSET(STATES first, ARGS ... stargs) {
        _stateSET(first); _stateSET(stargs ...);
    }

    void _stateRESET()
    {

        std::cout << "\033[22m"; // Reset bold
        std::cout << "\033[23m"; // Reset italics
        std::cout << "\033[24m"; // Reset underline
        //std::cout << "\033[25m"; // Reset blink
        std::cout << "\033[27m"; // Reset reverse
        std::cout << "\033[29m"; // Reset strikethrough
    }

    void _backgroundSET(BACKGROUNDS bg) { printf("\033[48;5;%dm", bg); }
    void _backgroundRESET() { std::cout << "\033[49m"; }

    void _csbRESET() { printf("\033[0m"); }

    std::string _cTAG(COLORS col)
    {
        return ("\033[38;5;" + std::to_string(col) + "m");
    }

    std::string _cTAG(STATES st)
    {
        return ("\033[" + std::to_string(st) + "m");
    }

    std::string _cTAG(BACKGROUNDS bg)
    {
        return ("\033[48;5;" + std::to_string(bg) + "m");
    }

    template <typename T, typename... Args>
    std::string _cTAG(T first, Args... arglist)
    {

        std::string result = _cTAG(first);
        result += _cTAG(arglist...);

        return result;
    }

    std::string _rTAG(RESET_TYPES reset = rtFULL)
    {

        std::string return_tag = "";

        if (reset == rtCOLOR || reset == rtFULL)
            return_tag += "\033[39m"; // Reset color
        if (reset == rtBACKGROUND || reset == rtFULL)
            return_tag += "\033[49m"; // Reset Background
        if (reset == rtSTATES || reset == rtFULL)
        {
            return_tag += "\033[22m"; // Reset bold
            return_tag += "\033[23m"; // Reset italics
            return_tag += "\033[24m"; // Reset underline
            //return_tag += "\033[25m"; // Reset blink
            //return_tag += "\033[27m"; // Reset reverse
            return_tag += "\033[29m"; // Reset strikethrough
        }

        return return_tag;
    }

    /*
    template <typename... Args>
    std::string TAG(Args&&... args) {
        static_assert(sizeof...(args) > 0, "At least one argument is required");

        std::string result;
        (void)std::initializer_list<int>{(result += TAG(std::forward<Args>(args)), 0)...};

        return result;
    }
    */

    // ======================================
    // Special Functions (USING RGB)

    void _colSET(int r, int g, int b)
    {
        printf("\033[38;2;%d;%d;%dm", r, g, b);
    }

    void _backgroundSET(int r, int g, int b)
    {
        printf("\033[48;2;%d;%d;%dm", r, g, b);
    }
}

#ifdef NAMESPACE_TOTALITY
using namespace LLC;
#endif