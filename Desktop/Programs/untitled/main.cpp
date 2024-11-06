#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <utility>
#include <vector>

bool findPair(std::vector<std::pair<char, int>>& pr, char& temp) {
    for (auto &elem: pr) {
        if (elem.first == temp) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        exit(0);
    }
    char buffer[1024];

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        perror("Error");
        exit(0);
    }

    int size = 0;
    while (true) {
        int readbytes = read(fd, buffer, 50);
        if (readbytes == 0) {
            break;
        }
        else if (readbytes < 0) {
            perror("Error!");
            exit(0);
        }
        size += readbytes;
    }

    std::vector<std::pair<char, int>> Pair;
    for (int i = 0; i < size - 1; i++) {
        char temp = buffer[i];
        std::pair<char, int> elem(temp, 1);
        if (!findPair(Pair, temp)) {
            Pair.push_back(elem);
        }
        else {
            for (auto &pr : Pair) {
                if (temp == pr.first) {
                    pr.second++;
                }
            }
        }
    }

    for (auto &pr: Pair) {
        std::cout << pr.first << " - " << pr.second << "\n";
    }

    return 0;
}
