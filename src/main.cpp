#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "DataVector.h" // it includes <vector>
#include "Equation.h"
#include <ctime>
#include <cstdio> // #include <stdio.h> and sprintf_s() or #define _CRT_SECURE_NO_WARNINGS and sprintf()

double fun(double x);	// Как и fun_(...) содержит функцию, корень которой будет необходимо определить.
double D1fun(double x); // Как и D1fun_(...) содержит производную функции, корень которой будет необходимо определить.
double fun_(const double& x);
double D1fun_(const double& x);

std::string getTime(const char* = "%4i_%#02i_%#02i_time_%#02i_%#02i_%#02i"); // Имеет формат вывода даты, установленный по умолчанию.

int main(int argc, char* argv[]) {

    bool outputFlag = true;

    if (argc > 1) {
        if (strcmp(argv[1], "-v") == 0) {
            std::string versionString;
            std::string buildString;

            std::ifstream configFile("resources/config.txt");
            std::string configLine;
            while (std::getline(configFile, configLine)) {
                if (configLine.find("version=") == 0)
                    versionString = configLine.substr(8);
                else if (configLine.find("build=") == 0)
                    buildString = configLine.substr(6);
            }

            std::cout << "Version: " << versionString << "\n";
            std::cout << "Build Date: " << buildString << "\n";

            outputFlag = false;
        }
    }

    if (outputFlag) {
        std::ifstream outputFile("resources/output.txt");
        if (outputFile.is_open()) {
            std::string outputText;
            getline(outputFile, outputText);
            std::cout << outputText;

            // 0. Установка пути для сохранения данных:
            const std::string way = "../resources/";
            const std::string filename = "data_" + getTime();
            const std::string fullwayname = way + filename + ".txt";

            // 1. Инциализация пустых векторов данных для хранения результатов рассчёта:
            DataVector x_data_Newton("array of roots Newton's method");
            DataVector delta_data_Newton("array of error estimates Newton's method");

            DataVector x_data_NewtonFinite("array of roots of finite Newton's method");
            DataVector delta_data_NewtonFinite("array of error estimates of finite Newton's method");

            // 2. Задание параметров для процесса уточнения корня меодом Ньютона:
            const double x_start = 179.0156;
            const unsigned int mantissa_size = 64;
            const double delta_max = 1e-32;
            const unsigned int iter_max = 1e2;

            // 3. Вызов метода Ньютона:
            const double root_Newton = solveNewton(x_start, fun_, D1fun_, x_data_Newton, delta_data_Newton, delta_max, iter_max);

            // 4. Вызов конечно-разностного метода Ньютона:
            const double root_NewtonFinite = solveNewtonFinite(x_start, fun_, x_data_NewtonFinite, delta_data_NewtonFinite, delta_max, iter_max);

            // 5. Вывод результатов:
            std::printf("\n\nNewton's method :\n		root is %1.15e\n		iteration number is %i\n", root_Newton, x_data_Newton.size());
            std::printf("\n\nfinite Newton's method :\n		root is %1.15e\n		iteration number is %i\n", root_NewtonFinite, x_data_NewtonFinite.size());
            std::printf("\n||x_Newton - x_Newton.f|| = %1.31e\n", std::abs(root_Newton - root_NewtonFinite));

            // 6. Сохранение результатов в файл:
            x_data_Newton.Save(fullwayname, mantissa_size);
            delta_data_Newton.Save(fullwayname, mantissa_size);
            x_data_NewtonFinite.Save(fullwayname, mantissa_size);
            delta_data_NewtonFinite.Save(fullwayname, mantissa_size);
        }
        else {
            std::cout << "Error: " << outputFile.rdstate();
        }
    }

    return 0;
}

double fun(const double x) { return (x * x - 1.0)/1000.0; }
double D1fun(const double x) { return 2.0 * x / 1000.0; }

double fun_(const double& x) {	return (x * x - 1.0) / 1000.0;}
double D1fun_(const double& x) { return 2.0 * x / 1000.0; }

std::string getTime(const char* format)
{
    time_t now = time(nullptr);
    struct tm newtime{};
    localtime_r(&now, &newtime);

    const int year = 1900 + newtime.tm_year;
    const int month = 1 + newtime.tm_mon;
    const int day = newtime.tm_mday;
    const int hour = newtime.tm_hour;
    const int minute = newtime.tm_min;
    const int second = newtime.tm_sec;

    char date[256];

    sprintf(date, format, year, month, day, hour, minute, second);

    return {date};
}