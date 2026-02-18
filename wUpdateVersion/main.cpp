// wUpdateVersion v0.1

/* MIT License
** 
** Copyright(c) 2026 Vladislav Salikov
** 
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files(the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions :
** 
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
*/

#include <iostream>
#include <string>
#include <format>
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>

namespace fs = std::filesystem;

std::wstring wGetLastElem(const std::wstring& str) {
    std::vector<std::wstring> result {};
    std::wstringstream ss(str);
    std::wstring item;
    while (getline(ss, item, L' ')) result.push_back(item);
    return result.back();
}

std::wstring wToUpper(const std::wstring& str) {
    std::wstring us { str };
    std::transform(us.begin(), us.end(), us.begin(), ::toupper);
    return us;
}

std::wstring wTrim(const std::wstring& str) {
    std::wstring ts { str };
    ts.erase(std::remove(ts.begin(), ts.end(), '"'), ts.end());
    ts.erase(std::remove(ts.begin(), ts.end(), '\''), ts.end());
    return ts;
}

bool wReplace(std::wstring& str, const std::wstring& find_what, const std::wstring& replace_by) {
    if (str.empty() || find_what.empty()) return false;
    size_t pos { 0 };
    while ((pos = str.find(find_what, pos)) != std::wstring::npos) {
        str.replace(pos, find_what.length(), replace_by);
        pos += replace_by.length();
    }
    return true;
}

bool wContains(const std::wstring& str, const std::wstring& c) {
    if (str.find(c) == std::wstring::npos) return false;
    return true;
}

int wmain(int argc, wchar_t* argv[]) {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::wcout << L"Starting wUpdateVersion..." << std::endl;

    if (argc < 3) {
        std::wcout << L"Error! Too few arguments!\n";
        std::wcout << L"Usage: wUpdateVersion <VersionFile> <ResourceFile>\n";
        std::wcout << L"Where <VersionFile> - The file with defined macro APP_VERSION \"1.0\"\n";
        std::wcout << L"      <ResourceFile> - The *.rc file with VS_VERSION_INFO structure defined\n";
        std::wcout << std::endl;
        return 1;
    }

    if (!fs::exists(argv[1])) {
        std::wcout << std::format(L"ERROR! File {} does not exist!", argv[1]) << std::endl;
        return 2;
    }
    if (!fs::exists(argv[2])) {
        std::wcout << std::format(L"ERROR! File {} does not exist!", argv[2]) << std::endl;
        return 2;
    }

    fs::path fileVersion = argv[1];
    fs::path fileRC = argv[2];
    fs::path fileRCBak = fileRC;
    fileRCBak += L".bak";

    const std::vector<std::wstring> vFindWhat { L"FILEVERSION", L"PRODUCTVERSION" };
    std::vector<std::wstring> vStrings {};
    std::wstring line {}, newVersion {}, newVersionStr {}, newVersionNum {};

    std::wifstream sFileV(fileVersion);
    if (sFileV.is_open()) {
        while (std::getline(sFileV, line)) {
            if (line.find(L"APP_VERSION") != std::wstring::npos) {
                newVersion = wTrim(wGetLastElem(line));
                break;
            }
        }
        sFileV.close();
    }
    else {
        std::wcout << std::format(L"ERROR! Can't open file {}!", fileVersion.native()) << std::endl;
        return 3;
    }

    if (newVersion.empty()) {
        std::wcout << L"ERROR! Parsing APP_VERSION macro failed!" << std::endl;
        return 4;
    }

    if (wContains(newVersion, L".")) {
        newVersionStr = newVersion;
        wReplace(newVersion, L".", L",");
        newVersionNum = newVersion;
    }
    else if (wContains(newVersion, L",")) {
        newVersionNum = newVersion;
        wReplace(newVersion, L",", L".");
        newVersionStr = newVersion;
    }
    else newVersionStr = newVersionNum = newVersion;

    std::wifstream sFileRC_in(fileRC);
    if (sFileRC_in.is_open()) {
        while (std::getline(sFileRC_in, line)) {
            vStrings.push_back(line);
        }
        sFileRC_in.close();
    }
    else {
        std::wcout << std::format(L"ERROR! Can't read file {}!", fileRC.native()) << std::endl;
        return 5;
    }

    std::wstring oldVersion {};
    for (const auto& what : vFindWhat) {
        for (auto& line : vStrings) {
            if (wToUpper(line).find(wToUpper(what)) != std::wstring::npos) {
                oldVersion = wTrim(wGetLastElem(line));
                if (wContains(oldVersion, L".")) wReplace(line, oldVersion, newVersionStr);
                else if (wContains(oldVersion, L",")) wReplace(line, oldVersion, newVersionNum);
                else wReplace(line, oldVersion, newVersion);
            }
        }
    }

    fs::rename(fileRC, fileRCBak);

    std::wofstream sFileRC_out(fileRC);
    if (sFileRC_out.is_open()) {
        for (const auto& line : vStrings) {
            sFileRC_out << line << std::endl;
        }
        sFileRC_out.close();
    }
    else {
        std::wcout << std::format(L"ERROR! Can't write to file {}!", fileRC.native()) << std::endl;
        return 6;
    }

    std::wcout << L"End of wUpdateVersion." << std::endl;
    return 0;
}
