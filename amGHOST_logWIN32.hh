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

#define amG_PASSED(x)  REY_LOG("PASSED:- " << x);
#define amG_PASSED1(x) REY_LOG("    PASSED:- " << x);
#define amG_PASSED2(x) REY_LOG("        PASSED:- " << x);
#define amG_PASSED3(x) REY_LOG("            PASSED:- " << x);
#define amG_PASSED4(x) REY_LOG("                PASSED:- " << x);
#define amG_PASSED5(x) REY_LOG("                    PASSED:- " << x);

#define amG_FAILED1(x) amG_FAILED("    " << x);
#define amG_FAILED2(x) amG_FAILED("        " << x);
#define amG_FAILED3(x) amG_FAILED("            " << x);
#define amG_FAILED4(x) amG_FAILED("                " << x);
#define amG_FAILED5(x) amG_FAILED("                    " << x);

#define REY_LOG_status(x) REY_LOG(x)
#define REY_LOG_notfound(x) REY_LOG_EX("NotFound:- " << x);