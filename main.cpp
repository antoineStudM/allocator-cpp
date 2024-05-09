#include <iostream>
#include <vector>

#include "allocator.h"

using namespace std;

void printOrNot(void *ptr, size_t mem) {
  if (ptr != nullptr)
    cout << "Memory available : " << mem << "\n" << endl;
  else
    cerr << "Not enough memory available !\n" << endl;
}

int main(int argc, char *argv[]) {

  Memory block_mem = Memory{.mem = vector(100, '0')};
  cout << "Creation of a memory block. Size = 100\n" << endl;

  Allocator allocator(block_mem);

  void *ptr1 = allocator.allocate(70);
  printOrNot(ptr1, allocator.getMemAvailable());

  void *ptr2 = allocator.allocate(70);
  printOrNot(ptr2, allocator.getMemAvailable());

  void *ptr3 = allocator.allocate(30);
  printOrNot(ptr3, allocator.getMemAvailable());
 
  allocator.deallocate(ptr1, 70);
  cout << "Deallocate : 70\n" << endl;


  void *ptr4 = allocator.allocate(70);
  printOrNot(ptr4, allocator.getMemAvailable());

  return 0;
}
