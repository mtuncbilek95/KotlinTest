#include "SystemReport.h"

#include <Log/Log.h>

SystemReport::SystemReport(const std::string_view &report) : mReport(report) {

}

bool SystemReport::IsExitRequested() {
    if(!mReport.empty())
    {
        Log::Fatal("{}", mReport);
        return true;
    }

    return false;
}
