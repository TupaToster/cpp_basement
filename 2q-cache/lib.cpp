/**
 * @file config.cpp
 * @author TupaToster
 * @brief source file for some universal things that proved so essential to the project, that they where included to every file
 * @version 1.1
 * @date 2024-03-26
 */

#include "lib.hpp"

// ---------- Everywhere-wide constants here ------------

/**
 * @brief precision to compare doubles with in cmp
 */
const double EPS = 0.001;

/**
 * @brief name of file where logs go
 */
const char logFileName[] = "logs_out.html";

/**
 * @brief used inside a define as a variable (also to store already opened log file)
 */
FILE* LogFilePtr = NULL;

/**
 * @brief multiplier for counting hash
 */
const unsigned int HashMult = 107u;

// ------------------------------------------------------

/**
 * @brief compares 2 doubles
 *
 * @param par1 first double
 * @param par2 second double
 * @return int how 2 numers are related with EPS@config.hpp precision
 * @retval -1 par1 is less
 * @retval 0 equal
 * @retval 1 par1 is more
 */
int cmp (const double par1, const double par2) {

    if (par1 - EPS >= par2) return 1;
    else if (par1 + EPS <= par2) return -1;
    else return 0;
}

/**
 * @brief counts hash of any array style data
 *
 * @param from where to start
 * @param to before where to end
 * @return unsigned int - calculated hash value
 */
unsigned int cntHash (void* from, void* to) {

    assert (from != NULL);
    assert (to != NULL);
    assert (from <= to);

    unsigned int hash = 0;

    for (; from < to; from = (char*) from + 1) {

        hash *= HashMult;
        hash += *(unsigned char*) from;
    }

    return hash;
}

/**
 * @brief Internal mechanism for log
 *
 * @param val ptr to what to log
 * @param varType type of variable
 * @param varName name of variable
 * @param varSize size in bytes
 * @param fileName where it is located
 * @param funcName in which function
 * @param line on which line (!)
 */
void logIntern (const void* val, const char* varType, const char* varName, size_t varSize, const char* fileName, const char* funcName, size_t line) {

    assert (val != NULL);
    assert (varType != NULL);
    assert (varName != NULL);
    assert (varSize > 0);
    assert (fileName != NULL);
    assert (line > 0);

    /// default beginning with general data
    fprintf (LogFilePtr, "<pre>In file %s, function %s, line %u : %s = ", fileName, funcName, line, varName);

    /// This prints using corresponding fprintf or as char* if type is undefined
    /// @warning super janky!! works bad with char* and char[] (fix needed)
    if (!strcmp (varType, "Pc") || !strcmp (varType, "PKc")) fprintf (LogFilePtr, "<%s>", *((const char**) val));
    else if (varType[0] == 'P') fprintf (LogFilePtr, "0x%p", *(void**)val);

    else if (!strcmp (varType, "i") || !strcmp (varType, "Ki")) fprintf (LogFilePtr, "%d"   , *( ( const int*)                val));
    else if (!strcmp (varType, "x") || !strcmp (varType, "Kx")) fprintf (LogFilePtr, "%lld" , *( ( const long long*)          val));
    else if (!strcmp (varType, "c") || !strcmp (varType, "Kc")) fprintf (LogFilePtr, "%hhd" , *( ( const char*)               val));
    else if (!strcmp (varType, "f") || !strcmp (varType, "Kf")) fprintf (LogFilePtr, "%g"   , *( ( const float*)              val));
    else if (!strcmp (varType, "d") || !strcmp (varType, "Kd")) fprintf (LogFilePtr, "%lg"  , *( ( const double*)             val));
    else if (!strcmp (varType, "j") || !strcmp (varType, "Kj")) fprintf (LogFilePtr, "%u"   , *( ( const unsigned int*)       val));
    else if (!strcmp (varType, "y") || !strcmp (varType, "Ky")) fprintf (LogFilePtr, "%llu" , *( ( const unsigned long long*) val));
    else if (!strcmp (varType, "h") || !strcmp (varType, "Kh")) fprintf (LogFilePtr, "%hhu" , *( ( const unsigned char*)      val));
    else {
        for (int i = 0; i < varSize; i++) fprintf (LogFilePtr, "%hhX", *((char*) val + i));
        fprintf (LogFilePtr, " :: UNDEFINED_FORMAT : sizeof() = %u", varSize);
    }
    fprintf (LogFilePtr, ";<br></pre>\n");
}

/**
 * @brief returns format string for printf (basically std::cout but dumber)
 *
 * @param varType type from macros
 * @return const char* format string for printf
 */
const char* getFormatIntern (const char* varType) {

    assert (varType != NULL);

    if (!strcmp (varType, "Pc") || !strcmp (varType, "PKc"))    return "%s";
    else if (varType[0] == 'P') return "%p";

    else if (!strcmp (varType, "i") || !strcmp (varType, "Ki")) return "%d"  ;
    else if (!strcmp (varType, "x") || !strcmp (varType, "Kx")) return "%lld";
    else if (!strcmp (varType, "c") || !strcmp (varType, "Kc")) return "%hhd";
    else if (!strcmp (varType, "f") || !strcmp (varType, "Kf")) return "%g"  ;
    else if (!strcmp (varType, "d") || !strcmp (varType, "Kd")) return "%lg" ;
    else if (!strcmp (varType, "j") || !strcmp (varType, "Kj")) return "%u"  ;
    else if (!strcmp (varType, "y") || !strcmp (varType, "Ky")) return "%llu";
    else if (!strcmp (varType, "h") || !strcmp (varType, "Kh")) return "%hhu";
    else return "%p";
}
