#define APPROVALS_DOCTEST
#include "ApprovalTests.hpp"

#include "DocTestReporter.h"

#include <filesystem>

using namespace ApprovalTests;

//auto defaultReporterDisposer =
//    Approvals::useAsDefaultReporter(std::make_shared<TextDiffReporter>());

//auto defaultReporterDisposer =
//    Approvals::useAsDefaultReporter(std::make_shared<DocTestReporter>());

auto configChange = ApprovalTestNamer::setCheckBuildConfig(false);

auto default_namer_disposer = Approvals::useAsDefaultNamer(
    []()
    {
        std::string args =
            "{TestFileName}.{TestCaseName}.{ApprovedOrReceived}.{FileExtension}";
        ApprovalTestNamer namer;
        auto path1 = std::filesystem::canonical(std::filesystem::path(".")).string();
        std::cout << namer.getDirectory() << '\n' << path1 << '\n';

        bool is_build_environment =
            StringUtils::endsWith(path1, "examples/out_of_source");
        if (is_build_environment)
        {
            args = "{TestSourceDirectory}/" + args;
        }
        return std::make_shared<TemplatedCustomNamer>(args);
    });