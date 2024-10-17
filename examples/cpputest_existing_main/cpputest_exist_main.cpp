// begin-snippet: cpputest_existing_main
// main.cpp:

// 1. Add these two lines to your main:
#define APPROVALS_CPPUTEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

#if defined(BUILD_MONOLITHIC)
#define main approval_cputest_exist_main
#endif

extern "C"
int main(int argc, const char** argv)
{
    // 2. Add this line to your main:
    ApprovalTests::initializeApprovalTestsForCppUTest();

    int result = CommandLineTestRunner::RunAllTests(argc, argv);
    TestRegistry::getCurrentRegistry()->resetPlugins();
    return result;
}
// end-snippet
