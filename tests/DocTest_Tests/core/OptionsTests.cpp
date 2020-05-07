#include "doctest/doctest.h"

#include "ApprovalTests/core/Options.h"
#include "ApprovalTests/reporters/QuietReporter.h"

using namespace ApprovalTests;

namespace
{
    void checkSameType(std::type_info const& type1,
                       std::type_info const& type2,
                       const std::string& message)
    {
        CHECK_MESSAGE(std::string(type1.name()) == std::string(type2.name()), message);
    }
}

TEST_CASE("Options - Reporter features")
{
    Options options;
    const Reporter& initialReporter = options.getReporter();

    checkSameType(typeid(initialReporter),
                  typeid(DefaultReporter),
                  "Initial reporter was not expected type");

    // Check that setting the reporter gets back the same object
    {
        QuietReporter new_reporter;
        const Options& options3 = options.withReporter(new_reporter);
        const Reporter& reporter3 = options3.getReporter();
        CHECK(&reporter3 == &new_reporter);
    }
}

TEST_CASE("Options - FileExtension features")
{
    Options options;
    const Reporter& initialReporter = options.getReporter();

    CHECK(options.fileOptions().getFileExtension() == ".txt");
    CHECK(options.fileOptions()
              .withFileExtension(".xyz")
              .fileOptions()
              .getFileExtension() == ".xyz");

    // Check that setting the file extension does not change the reporter instance:
    {
        const Reporter& reporter2 =
            options.fileOptions().withFileExtension(".abc").getReporter();
        CHECK(&initialReporter == &reporter2);
    }
}

TEST_CASE("copying")
{
    // Options.with... returns new Options, containing new FileOptions
    // Options.fileOptions()... returns local FileOptions - but with options poi
    // Options.fileOptions().with... returns new Options containing new FileOptions

    // FileOptions contains a non-owning pointer to its parent Options
    Options o1;
    Options o2 = o1;

    Options::FileOptions fo = Options().fileOptions();
}