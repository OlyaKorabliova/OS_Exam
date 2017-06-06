#include <iostream>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;
size_t get_file_size(const char* filename) {
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;
}

int main() {
    DIR *dir = opendir(".");
    struct dirent* entry;
    int total_size = 0;
    while((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".") != 0) {
            int descriptor = open(entry->d_name, O_RDONLY);
            if (descriptor != -1) {
                int file_size = get_file_size(entry->d_name);
                cout << entry->d_name << " - " << file_size << " bytes" << endl;
                total_size += file_size;
            }
            else {
                cerr << "Error! Descriptor = -1" << endl;
                return -1;
            }
        }
    }
    cout << "---------------------------------" << endl;
    cout << "Total size in current directory = " << total_size << " bytes" << endl;
    closedir(dir);
    return EXIT_SUCCESS;
}