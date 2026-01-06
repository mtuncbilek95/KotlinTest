#include "SystemReport.h"

#include <Log/Log.h>

SystemReport::SystemReport(const std::string_view &report) : m_report(report) {

}

bool SystemReport::IsExitRequested() {
    if(!m_report.empty())
    {
        Log::Fatal("{}", m_report);
        return true;
    }

    return false;
}
