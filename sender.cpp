#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "data.h"

int main() {
    const char *name = "data_shm";
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Error opening shared memory" << std::endl;
        return 1;
    }

    if (ftruncate(shm_fd, sizeof(Data) * 10) == -1) {
        std::cerr << "Error truncating shared memory" << std::endl;
        return 1;
    }

    void *ptr = mmap(0, sizeof(Data) * 10, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Error mapping shared memory" << std::endl;
        return 1;
    }

    Data* dataArr = static_cast<Data*>(ptr);

    for (int i = 0; i < 10; ++i) {
        dataArr[i].intValue = i;
        dataArr[i].floatValue = i * 1.1f;
        dataArr[i].stringValue.resize(50); // Allocate memory for the string
        dataArr[i].stringValue = "Data " + std::to_string(i);
        dataArr[i].typeValue = static_cast<Data::Type>(i % 3);
    }

    std::cout << "Data sent to shared memory." << std::endl;

    if (munmap(ptr, sizeof(Data) * 10) == -1) {
        std::cerr << "Error unmapping shared memory" << std::endl;
        return 1;
    }

    if (close(shm_fd) == -1) {
        std::cerr << "Error closing shared memory file descriptor" << std::endl;
        return 1;
    }

    return 0;
}
