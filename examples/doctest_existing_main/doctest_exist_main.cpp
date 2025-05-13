// begin-snippet: doctest_existing_main
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_DOCTEST_EXISTING_MAIN
#include "ApprovalTests.hpp"
// end-snippet

#include "ApprovalTests/Approvals.h"

#if defined(BUILD_MONOLITHIC)
#define main approval_doctest_exist_main
#endif

extern "C" int main(int argc, const char** argv)
{
    auto directoryDisposer =
        ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
    return doctest::Context(argc, argv).run();
}
