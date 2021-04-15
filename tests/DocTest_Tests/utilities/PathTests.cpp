#include "doctest/doctest.h"
#include "ApprovalTests/utilities/Path.h"

using namespace ApprovalTests;

TEST_CASE("Should append to paths")
{
    Path path(".");
    CHECK("." == path.toString("/"));

    path = path / "file.txt";
    CHECK("./file.txt" == path.toString("/"));
    CHECK(".\\file.txt" == path.toString("\\"));
}

TEST_CASE("Should handle multiple separators")
{
    auto location = "tmp" + SystemUtils::getDirectorySeparator();
    Path path = Path(location);
    path = path / (SystemUtils::getDirectorySeparator() + "subdirectory");
    CHECK("tmp/subdirectory" == path.toString("/"));
    CHECK("tmp\\subdirectory" == path.toString("\\"));
}
