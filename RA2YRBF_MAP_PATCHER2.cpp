#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

// Check for allowed extensions
bool isValidExtension(const std::string& filename) {
    const std::string allowedExtensions[] = { ".yrm", ".map", ".mpr" };
    for (const std::string& ext : allowedExtensions) {
        if (filename.size() >= ext.size() && filename.compare(filename.size() - ext.size(), ext.size(), ext) == 0) {
            return true;
        }
    }
    return false;
}


int main(int argc, char* argv[]) {

    SetConsoleTitle(TEXT("RA2YRBF Map Patcher -- mbnq.pl"));

    // Check the path
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_file>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];

    // Check extension if path given
    if (!isValidExtension(filePath)) {
        std::cerr << "Invalid file extension. Allowed extensions are .yrm, .map, .mpr" << std::endl;
        return 1;
    }

    // payload
    const std::string textToAppend = "\n[Events]\n01000002=1,13,0,0\n01000004=1,13,0,777\n01000006=1,13,0,20\n\n"
        "[Actions]\n01000002=3,27,0,777,0,0,0,0,A,23,0,0,0,0,0,0,A,103,4,mission:c21timer,0,0,0,0,A\n"
        "01000004=13,27,0,777,0,0,0,0,A,23,0,0,0,0,0,0,A,108,0,1,0,0,0,0,A,108,0,1,0,0,0,0,B,21,6,EVA_ReinforcementsHaveArrived,0,0,0,0,A,103,4,mission:c21timer,0,0,0,0,A,108,0,1,0,0,0,0,C,108,0,1,0,0,0,0,D,108,0,1,0,0,0,0,E,108,0,1,0,0,0,0,F,108,0,1,0,0,0,0,F,108,0,1,0,0,0,0,G,108,0,1,0,0,0,0,H\n"
        "01000006=10,108,0,1,0,0,0,0,A,108,0,1,0,0,0,0,B,19,7,CrateFreeUnit,0,0,0,0,A,21,6,EVA_ReinforcementsReady,0,0,0,0,A,108,0,1,0,0,0,0,C,108,0,1,0,0,0,0,D,108,0,1,0,0,0,0,E,108,0,1,0,0,0,0,F,108,0,1,0,0,0,0,G,108,0,1,0,0,0,0,H\n\n"
        "[Tags]\n01000003=0,start_timer 1,01000002\n01000005=2,Paczki 1,01000004\n01000007=0,Paczki_na_start 1,01000006\n\n"
        "[Triggers]\n01000002=Neutral,<none>,start_timer,0,1,1,1,0\n01000004=Neutral,<none>,Paczki,0,1,1,1,0\n01000006=Neutral,<none>,Paczki_na_start,0,1,1,1,0\n";

    // Open the file
    std::ofstream fileStream(filePath, std::ios::app);
    if (!fileStream.is_open()) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return 1;
    }

    // Add payload
    fileStream << textToAppend;

    // Close the file
    fileStream.close();

    std::cout << "File patched successfully! " << filePath << std::endl;

    // Wait for user to press Enter
    std::cin.ignore();
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
