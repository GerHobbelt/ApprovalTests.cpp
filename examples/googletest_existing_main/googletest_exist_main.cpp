// begin-snippet: googletest_existing_main
// main.cpp:

// 1. Add these two lines to your main:
#define APPROVALS_GOOGLETEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

#if defined(BUILD_MONOLITHIC)
#define main approval_googletest_exist_main
#endif

extern "C" int main(int argc, const char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // 2. Add this line to your main:
    ApprovalTests::initializeApprovalTestsForGoogleTests();

    return RUN_ALL_TESTS();
}
// end-snippet

// begin-snippet: do_not_report_on_named_machine
// main.cpp
auto frontLoadedReportDisposer = ApprovalTests::Approvals::useAsFrontLoadedReporter(
    ApprovalTests::BlockingReporter::onMachineNamed("MyCIMachineName"));
// end-snippet
