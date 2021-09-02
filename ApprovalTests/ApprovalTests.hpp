#ifndef APPROVAL_TESTS_CPP_APPROVALS_HPP
#define APPROVAL_TESTS_CPP_APPROVALS_HPP

// This file is machine-generated. Do not edit.

#include "ApprovalTests/ApprovalTestsVersion.h"
#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/reporters/ReporterFactory.h"
#include "ApprovalTests/reporters/DiffInfo.h"
#include "ApprovalTests/reporters/DiffPrograms.h"
#include "ApprovalTests/reporters/ConvertForCygwin.h"
#include "ApprovalTests/launchers/CommandLauncher.h"
#include "ApprovalTests/reporters/CommandReporter.h"
#include "ApprovalTests/ApprovalsMacroDefaults.h"
#include "ApprovalTests/utilities/Macros.h"
#include "ApprovalTests/utilities/EmptyFileCreatorFactory.h"
#include "ApprovalTests/utilities/EmptyFileCreatorDisposer.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/WinMinGWUtils.h"
#include "ApprovalTests/utilities/StringMaker.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/launchers/SystemLauncher.h"
#include "ApprovalTests/reporters/GenericDiffReporter.h"
#include "ApprovalTests/reporters/QuietReporter.h"
#include "ApprovalTests/reporters/TextDiffReporter.h"
#include "ApprovalTests/utilities/Blocker.h"
#include "ApprovalTests/utilities/MachineBlocker.h"
#include "ApprovalTests/reporters/AutoApproveReporter.h"
#include "ApprovalTests/utilities/Path.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/namers/SectionNameDisposer.h"
#include "ApprovalTests/namers/NamerFactory.h"
#include "ApprovalTests/ApprovalUtils.h"
#include "ApprovalTests/core/ApprovalComparator.h"
#include "ApprovalTests/comparators/ComparatorDisposer.h"
#include "ApprovalTests/comparators/ComparatorFactory.h"
#include "ApprovalTests/core/ApprovalWriter.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/core/FileApprover.h"
#include "ApprovalTests/integrations/fmt/FmtToString.h"
#include "ApprovalTests/namers/FileNameSanitizerFactory.h"
#include "ApprovalTests/namers/FileNameSanitizerDisposer.h"
#include "ApprovalTests/namers/SubdirectoryDisposer.h"
#include "ApprovalTests/reporters/DefaultReporterFactory.h"
#include "ApprovalTests/reporters/DefaultReporterDisposer.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"
#include "ApprovalTests/reporters/DefaultFrontLoadedReporter.h"
#include "ApprovalTests/reporters/FrontLoadedReporterFactory.h"
#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"
#include "ApprovalTests/namers/DefaultNamerFactory.h"
#include "ApprovalTests/core/Options.h"
#include "ApprovalTests/namers/ExistingFileNamer.h"
#include "ApprovalTests/writers/ExistingFile.h"
#include "ApprovalTests/namers/DefaultNamerDisposer.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"
#include "ApprovalTests/integrations/google/GoogleCustomizationsFactory.h"
#include "ApprovalTests/utilities/MoreHelpMessages.h"
#include "ApprovalTests/utilities/CartesianProduct.h"
#include "ApprovalTests/reporters/DefaultReporter.h"
#include "ApprovalTests/CombinationApprovals.h"
#include "ApprovalTests/Storyboard.h"
#include "ApprovalTests/comparators/TextFileComparator.h"
#include "ApprovalTests/core/ApprovalException.h"
#include "ApprovalTests/integrations/FrameworkIntegrations.h"
#include "ApprovalTests/integrations/boost_test/BoostTestApprovals.h"
#include "ApprovalTests/integrations/catch/Catch2Approvals.h"
#include "ApprovalTests/integrations/cpputest/CppUTestApprovals.h"
#include "ApprovalTests/integrations/doctest/DocTestApprovals.h"
#include "ApprovalTests/integrations/fmt/FmtApprovals.h"
#include "ApprovalTests/integrations/google/GoogleConfiguration.h"
#include "ApprovalTests/integrations/google/GoogleTestApprovals.h"
#include "ApprovalTests/integrations/ut/UTApprovals.h"
#include "ApprovalTests/namers/HelpMessages.h"
#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/reporters/AutoApproveIfMissingReporter.h"
#include "ApprovalTests/reporters/BlockingReporter.h"
#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"
#include "ApprovalTests/reporters/CIBuildOnlyReporterUtils.h"
#include "ApprovalTests/reporters/ClipboardReporter.h"
#include "ApprovalTests/reporters/CombinationReporter.h"
#include "ApprovalTests/reporters/CustomReporter.h"
#include "ApprovalTests/reporters/DiffReporter.h"
#include "ApprovalTests/reporters/EnvironmentVariableReporter.h"
#include "ApprovalTests/reporters/LinuxReporters.h"
#include "ApprovalTests/reporters/MacReporters.h"
#include "ApprovalTests/reporters/WindowsReporters.h"
#include "ApprovalTests/utilities/DateUtils.h"
#include "ApprovalTests/utilities/ExceptionCollector.h"
#include "ApprovalTests/utilities/FileUtilsSystemSpecific.h"
#include "ApprovalTests/utilities/Grid.h"

#ifdef APPROVAL_TESTS_INCLUDE_CPPS
// Cpp files will be included in the single-header file here
#endif // APPROVAL_TESTS_INCLUDE_CPPS

#endif // APPROVAL_TESTS_CPP_APPROVALS_HPP
