#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

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
        }
        else {
            std::cout << "Error: " << outputFile.rdstate();
        }
    }

    return 0;
}