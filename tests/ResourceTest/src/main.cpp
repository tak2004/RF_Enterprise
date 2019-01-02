#include <RadonFramework/Radon.hpp>

namespace ApplicationOptions
{
    enum Type
    {
        ApplicationDirectory,
        RunSpecificTestSuite,
        MAX
    };
}

int main(int argc, const char **argv)
{
    RadonFramework::Radon framework;

    RF_Mem::AutoPointer<RF_Diag::Appender> console(new RF_IO::LogConsole);
    RF_IO::Log::AddAppender(console);
    RF_Mem::AutoPointer<RF_Diag::Appender> debugger(new RF_IO::LogDebuggerOutput);
    RF_IO::Log::AddAppender(debugger);

    RF_Test::TestResultCollector results;
    RF_Test::BriefProgressCollector progress;
    RF_Pattern::Singleton<RF_Test::UnitTest>::GetInstance().AddCollector(results);
    RF_Pattern::Singleton<RF_Test::UnitTest>::GetInstance().AddCollector(progress);
    RF_Pattern::Singleton<RF_Test::UnitTest>::GetInstance().SetSequentialTestExecution(10);

    RF_Mem::AutoPointerArray<RF_IO::OptionRule> rules(new RF_IO::OptionRule[ApplicationOptions::MAX], ApplicationOptions::MAX);
    rules[ApplicationOptions::ApplicationDirectory].Init(0, 0, RF_IO::StandardRuleChecker::Text, 0, RF_IO::OptionRule::Required);
    rules[ApplicationOptions::RunSpecificTestSuite].Init(0, "run", RF_IO::StandardRuleChecker::Text, "Run the specified test suite.", RF_IO::OptionRule::Optional);
    RF_IO::Parameter param;
    if(param.ParsingWithLogging(argv, argc, rules))
    {
        if(param.Values()[ApplicationOptions::RunSpecificTestSuite].IsSet())
        {
            RF_Pattern::Singleton<RF_Test::UnitTest>::GetInstance().RunSuiteWithName(param.Values()[ApplicationOptions::RunSpecificTestSuite].Value());
        }
        else
        {
            RF_Pattern::Singleton<RF_Test::UnitTest>::GetInstance().Run();
        }
    }

    RF_Test::JUnitOutput output;
    output.WriteToFile(RF_IO::Uri(RF_SysFile::ApplicationDirectory()).GetComponents() + "/PerformanceTest.xml", results);

    RF_Type::Bool res=results.WasSuccessful();
    if (res)
    {
        RF_IO::LogInfo("Test was successful.");
    }
    else
        RF_IO::LogError("Test failed.");

    RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().DisableAndWaitTillDone();
    return res;
}
