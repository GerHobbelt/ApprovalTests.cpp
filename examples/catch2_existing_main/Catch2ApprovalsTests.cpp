#include "catch2/catch.hpp"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

CATCH_TEST_CASE("TestStreamableObject")
{
    Approvals::verify(42);
}
