/// A Simple program to extract the current Day, Month, Year and Time in UTC and Local time.

#include <chrono>
#include <iostream>

int main()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm utc_tm = *gmtime(&tt);
    tm local_tm = *localtime(&tt);

    std::cout << "UTC time:" << std::endl;
    std::cout << "==========" << std::endl;

    std::cout << utc_tm.tm_year + 1900 << '-';
    std::string year = std::to_string(utc_tm.tm_year + 1900);
    std::cout << utc_tm.tm_mon + 1 << '-';
    std::string month = std::to_string(utc_tm.tm_mon + 1); 
    std::cout << utc_tm.tm_mday << ' ';
    std::string day = std::to_string(utc_tm.tm_mday);

    std::cout << utc_tm.tm_hour << ':';
    std::cout << utc_tm.tm_min << ':';
    std::cout << utc_tm.tm_sec << '\n';

    std::cout << "Year: " << year << ", Month: " << month << ", Day: " << day << std::endl;

    std::cout << "\nLocal time:" << std::endl;
    std::cout << "==========" << std::endl;
    std::cout << local_tm.tm_year + 1900 << '-';
    year = std::to_string(local_tm.tm_year + 1900);
    std::cout << local_tm.tm_mon + 1 << '-';
    month = std::to_string(local_tm.tm_mon + 1); 
    std::cout << local_tm.tm_mday << ' ';
    day = std::to_string(local_tm.tm_mday);

    std::cout << local_tm.tm_hour << ':';
    std::cout << local_tm.tm_min << ':';
    std::cout << local_tm.tm_sec << '\n';

    std::cout << "Year: " << year << ", Month: " << month << ", Day: " << day << std::endl;
}
