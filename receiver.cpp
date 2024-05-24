#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "data.h"

int main() {
    const char *name = "data_shm";
    int shm_fd = shm_open(name, O_RDONLY, 0666);
    void *ptr = mmap(0, sizeof(Data) * 10, PROT_READ, MAP_SHARED, shm_fd, 0);

    Data* dataArr = (Data*) ptr;

    for (int i = 0; i < 10; ++i) {
        std::string typeStr;
        switch (dataArr[i].typeValue) {
            case Data::type1: typeStr = "type1"; break;
            case Data::type2: typeStr = "type2"; break;
            case Data::type3: typeStr = "type3"; break;
        }
        std::cout << "int: " << dataArr[i].intValue 
                  << ", float: " << dataArr[i].floatValue 
                  << ", string: " << dataArr[i].stringValue 
                  << ", enum: " << typeStr << std::endl;
    }

    munmap(ptr, sizeof(Data) * 10);
    close(shm_fd);
    shm_unlink(name);

    return 0;
}
