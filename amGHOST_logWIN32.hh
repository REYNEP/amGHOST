#include "REY_Logger.hh"

#define amG_FAILED(x) \
    DWORD ec = ::GetLastError();           \
    REY_LOG_EX("FAILED:- " << x << "\n"    \
            << "    | \n"                  \
            << "    | ::GetLastError() --> " << ec << " | [HEX:- " << ec << "]");

#define amG_FAILED_hint(x, hint) \
    DWORD ec = ::GetLastError();           \
    REY_LOG_EX("FAILED:- " << x << "\n"    \
            << "    | \n"                  \
            << "    | ::GetLastError() --> " << ec << " | [HEX:- " << ec << "]" \
            << "    | " << hint);

#define amG_PASSED(x) REY_LOG("PASSED:- " << x);

#define REY_LOG_trace(x) REY_LOG(x)