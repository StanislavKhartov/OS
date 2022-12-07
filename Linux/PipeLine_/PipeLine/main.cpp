#include <string>
#include <vector>
#include <unistd.h>

int main() {
    int p[3], pid;
    std::vector<std::string> paths = {"/home/stanislave/CLionProjects/ProcM/cmake-build-debug/ProcM",
                                      "/home/stanislave/CLionProjects/ProcA/cmake-build-debug/ProcA",
                                      "/home/stanislave/CLionProjects/ProcP/cmake-build-debug/ProcP",
                                      "/home/stanislave/CLionProjects/ProcS/cmake-build-debug/ProcS"};

    for (int i = 0; i < paths.size() - 1; i++) {
        pipe(p);
        pid = fork();
        if (!pid) {
            dup2(p[1], STDOUT_FILENO);
            system(paths[i].c_str());
            exit(0);
        }
        dup2(p[0], 0);
        close(p[0]);
        close(p[1]);
    }
    system(paths[paths.size() - 1].c_str());
    return 0;
}