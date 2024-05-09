#pragma once

#include <iostream>
#include <vector>

struct Memory {
  std::vector<char> mem;
};

class Allocator {
private:
  Memory m_mem;
  size_t m_available;

public:
  Allocator(Memory &mem) : m_mem(mem), m_available(size(mem.mem)) {}

  void *allocate(size_t to_allocate) {
    std::cout << "Trying to allocate " << to_allocate << " byte(s)"
              << std::endl;
    if (to_allocate > this->m_available) {
      return nullptr;
    }

    for (size_t i = 0; i < this->m_mem.mem.size(); i++) {
      // '0' means not allocated
      if (this->m_mem.mem.at(i) == '0') {
        bool is_starter = true;
        for (size_t x; x < to_allocate; x++) {
          if (this->m_mem.mem.size() >= (i + x) ||
              this->m_mem.mem.at(i + x) == '1') {
            is_starter = false;
            break;
          }
        }
        // if we found a good starter
        // we now allocate
        if (is_starter) {
          for (size_t x = 0; x < to_allocate; x++) {
            this->m_mem.mem.at(i + x) = '1';
          }
          this->m_available -= to_allocate;
          return &this->m_mem.mem.at(i);
        }
      }
    }
    return nullptr;
  }

  void deallocate(void *ptr, size_t size) {
    char *start = static_cast<char *>(ptr);

    // L'opération de soustraction entre deux pointeurs donne la différence en
    // termes d'éléments entre les deux adresses.
    // Donc, (start - &this->m_mem.mem.at(0)) donne le nombre d'éléments entre
    // start et le début du vecteur de mémoire.
    size_t startIndex = start - &this->m_mem.mem.at(0);

    for (size_t i = startIndex; i < startIndex + size; ++i) {
      this->m_mem.mem.at(i) = '0';
    }
    this->m_available += size;
  }

  size_t getMemAvailable() { return this->m_available; }
};
