#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <csignal>
#include <dirent.h>


void endProcByName(std::string str) {
    int numTerminatedProcess = 0;
    pid_t PID;
    size_t i, j;
    char *s = new char[264];
    char buf[128];
    FILE *st;
    DIR *dir = opendir("/proc");
    if (dir == NULL) {
        free(s);
    }
    struct dirent *f;
    while ((f = readdir(dir)) != NULL) {
        //std::cout << f->d_name << '\n';
        if (f->d_name[0] == '.')
            continue;

        for (i = 0; std::isdigit(f->d_name[i]); ++i);
        if (i < strlen(f->d_name)) continue;
        strcpy(s, "/proc/");
        strcat(s, f->d_name);
        strcat(s, "/status");
        st = fopen(s, "r");
        if (st == NULL)
            continue;
        if (fgets(buf, 128, st) == NULL) {
            continue;
        }
        fclose(st);

        for (j = 5; std::isspace(buf[j]); j++);
        *strchr(buf, '\n') = 0;
        std::string bufStr(&(buf[j]));
        //std::cout << bufStr << '\n';
        auto result = std::mismatch(bufStr.begin(), bufStr.end(), str.begin());
        //std::cout << buf << ' ' << strcmp(&(buf[j]), processName.c_str()) << '\n';
        if (result.first == bufStr.end()) {
            sscanf(&(s[6]), "%d", &PID);
            //std::cout << PID << '\n';
            kill(PID, SIGKILL);
        }
    }
}

int main(int argc, char* argv[]) {
    int mode = 3;
    std::string str;
    //std::cin >> mode >> str;
    wchar_t wcstr[1000];
    char *cstr = std::getenv("PROC_TO_KILL");
    std::string str1(cstr);
    std::regex regex{R"([,]+)"}; // split on space and comma
    std::sregex_token_iterator it{str1.begin(), str1.end(), regex, -1};
    std::vector<std::string> names{it, {}};
    for (auto i: names) {
        endProcByName(i);
    }
    //int mode = atoi(argv[1]);
    if (mode == 1) {

        int n = str.length();
        char char_array[100 + 1];
        strcpy(char_array, str.c_str());

        int procID = atoi(char_array);
        kill(procID, SIGKILL);
        return 0;
    }
    if (mode == 2) {
        endProcByName(str);
    }
    return 0;
}