#include "StackTrace.hpp"

#ifdef DEBUG
#include <backtrace-supported.h>
#include <backtrace.h>
#include <cassert>
#include <cstring>

//#include "Bob.hpp"
#include "String.hpp"
#include "easylogging++.h" // 3rd Party Easy Logging++

#ifndef ATTRIBUTE_UNUSED
#define ATTRIBUTE_UNUSED __attribute__((__unused__))
#endif

struct StackTrace::info StackTrace::all[MAX_LINES];

StackTrace::StackTrace() {
    backTraceState = backtrace_create_state(appFileName, BACKTRACE_SUPPORTS_THREADS, backTraceErrorCallback, nullptr);

    data.all = &all[0];
    data.index = 0;
    data.max = MAX_LINES;
    data.failed = 0;

    int i = backtrace_full(backTraceState, 0, backtraceFullCallback, backTraceErrorCallback, &data);
    if ((i < 0 || i > 1) || data.failed) {
        LOG(ERROR) << "test1: unexpected return value " << i << " or data.failed " << data.failed << endl;
        data.failed = 1;
    }
}

StackTrace::~StackTrace() {}

void StackTrace::backTraceErrorCallback(void *data ATTRIBUTE_UNUSED, const char *msg, int errnum) {
    String eMsg;

    eMsg.append(msg);
    eMsg.append("(");
    eMsg.append(strerror(errnum));
    eMsg.append(")");

    LOG(ERROR) << eMsg << endl;

    // This is primarily called from an Exception and a StackTrace is not that vital to the program
    // so do not exit.  Besides the Exception may be exiting anyway.  We also do not want to be caught
    // in a recursive loop so do not throw an Exception.
    // exit (EXIT_FAILURE);
}

int StackTrace::backtraceFullCallback(void *vdata, uintptr_t pc ATTRIBUTE_UNUSED, const char *filename, int lineno, const char *function) {
    // bdata &data = reinterpret_cast<bdata &>(vdata); // dosn't work, why?
    bdata &data = *(reinterpret_cast<bdata *>(vdata));
    struct info &p = data.all[data.index];

    if (filename == nullptr && lineno == 0 && function == nullptr) {
        return 1;
    }

    if (data.index >= data.max) {
        LOG(ERROR) << "callback_one: callback called too many times" << endl;
        data.failed = 1;
        return 1;
    }

    if (filename == NULL) {
        p.filename = NULL;
    } else {
        const std::array<std::string, 2> names = { "StackTrace." , "Exception." };
        const auto fname = std::string(filename);

        for (const auto &name: names) {
            if (fname.find(name) != std::string::npos) {
                return 0;
            }
        }
        p.filename = strdup(filename);
        assert(p.filename != NULL);
    }
    p.lineno = lineno;
    if (function == NULL) {
        p.function = NULL;
    } else {
        p.function = strdup(function);
        assert(p.function != NULL);
    }
    ++data.index;

    return 0;
}

String StackTrace::getStackTrace() {
    String retVal;

    for (size_t i = 0; i < data.index; i++) {
        info inf = data.all[i];
        String functionName = demangle(inf.function);

        if (inf.filename != nullptr) {
            retVal.append("\n\tat ");
            retVal.append(functionName);
            retVal.append(" (");
            retVal.append(String(inf.filename));
            retVal.append(" : ");
            retVal.append(std::to_string(inf.lineno));
            retVal.append(")");
        }
        if (functionName == "main") break;
    }
    retVal.append("\n");

    return retVal;
}

#ifdef __GNUG__ // gnu C++ compiler
#include <cxxabi.h>
String StackTrace::demangle( const char* mangled_name ) {
    std::size_t len = 0 ;
    int status = 0 ;
    std::unique_ptr< char, decltype(&std::free) > ptr(__cxxabiv1::__cxa_demangle( mangled_name, nullptr, &len, &status ), &std::free ) ;
    if (ptr == nullptr) {
        return mangled_name;
    }
    return ptr.get() ;
}
#elif __MSVC__
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")

String StackTrace::demangle( const char* mangled_name ) {
    int status = 0 ;

    char undecorated_name[1024];
    UnDecorateSymbolName(undecorated_name, mangled_name, 1024, malloc, free, UNDNAME_COMPLETE); //...0x2800); //#define UNDNAME_COMPLETE (0x0000)

    if (!status) {
        return mangled_name;
    }
    return undecorated_name;
}
#else
String StackTrace::demangle( const char* name ) { return name ; }
#endif // _GNUG_

#endif //DEBUG

StackTrace &StackTrace::getInstance() {
    static StackTrace stackTrace;
    return stackTrace;
}
