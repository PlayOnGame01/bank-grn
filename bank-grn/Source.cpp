#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <codecvt>
#pragma comment(lib, "urlmon.lib")

using namespace std;
void FindPrintJSON(const wstring&, const wstring&);

int main()
{
    setlocale(LC_ALL, "Rus");
    const char* textovi_file = "rate.txt";
    const char* site = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";
    if (S_OK == URLDownloadToFileA(NULL, site, textovi_file, 0, NULL))
    {
        wcout << "Information about money in the world:" << textovi_file;
    }
    wcout << endl << endl;
    wifstream document(textovi_file, ios::in);
    document.imbue(locale(std::locale::empty(), new codecvt_utf8<wchar_t>));
    if (document.is_open())
    {
        wstring buff;
        while (!document.eof())
        {
            getline(document, buff, L'\n');
            FindPrintJSON(buff, L"txt\":");
            FindPrintJSON(buff, L"rate\":");
        }
        document.close();
    }
}

void FindPrintJSON(const wstring& sours, const wstring& find)
{
    int position = -1;
    while (true)
    {
        position = sours.find(find, position + 1);
        if (position == wstring::npos) break;

        for (auto i = sours.begin() + position + find.length(); i != sours.end(); ++i)
        {
            if (*i == ',') break;
            wcout << *i;
        }
        wcout << endl;
    }
}