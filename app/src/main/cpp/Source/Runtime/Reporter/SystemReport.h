#pragma once

#include <string_view>

class SystemReport {
public:
    SystemReport() = default;
    explicit SystemReport(const std::string_view& report);
    ~SystemReport() = default;

    bool IsExitRequested();

private:
    std::string_view mReport;
};