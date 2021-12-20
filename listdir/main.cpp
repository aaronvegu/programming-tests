#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>

namespace fs = std::filesystem;

int main()
{
    std::fstream file("dir.json", std::ios::out);

    std::string path = "/Users/aaronvegu/Downloads";

    file << "{ \"files\": [" << std::endl;
    for (const auto & entry : fs::directory_iterator(path)) {
        if (entry.symlink_status().type() != fs::file_type::directory) {
            file << "\t{\"name\":" << entry.path().filename() << ",\"size\":" 
            << fs::file_size(entry.path()) << "}," << std::endl;
        }
    }
    file << "\t]\n}" << std::endl;
    file.close();

    //std::string line;

    //file.open("files.json", std::ios::in);
    //file.seekg(-1, std::ios_base::end);
    //line = file.getline();
    //line[line.size()-1] = "\0";
    //line = line + "]}" << std::endl;
    

    return 0;
}