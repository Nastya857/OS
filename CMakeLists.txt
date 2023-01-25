cmake_minimum_required(VERSION 3.23)
project(os_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(os_2 pci_dev_app.c vm_area_app.c my_pci_dev.c my_vm_area.c)
