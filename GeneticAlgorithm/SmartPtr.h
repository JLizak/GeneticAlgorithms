// SmartPointer.h
#ifndef CSMARTPOINTER_H
#define CSMARTPOINTER_H
#include "RefCounter.h"

namespace GA {
    template <typename T>
    class SmartPointer {
    public:
        // Default constructor
        SmartPointer() : pc_pointer(nullptr), pc_counter(nullptr) {}

        // Constructor from raw pointer
        explicit SmartPointer(T* pcPointer) {
            pc_pointer = pcPointer;
            pc_counter = new RefCounter();
            pc_counter->iAdd();
        }

        // Copy constructor
        SmartPointer(const SmartPointer<T>& other) {
            pc_pointer = other.pc_pointer;
            pc_counter = other.pc_counter;
            if (pc_counter) {
                pc_counter->iAdd();
            }
        }

        // Move constructor
        SmartPointer(SmartPointer<T>&& other) noexcept {
            pc_pointer = other.pc_pointer;
            pc_counter = other.pc_counter;
            other.pc_pointer = nullptr;
            other.pc_counter = nullptr;
        }

        // Destructor
        ~SmartPointer() {
            release();
        }

        // Copy assignment
        SmartPointer& operator=(const SmartPointer<T>& other) {
            if (this != &other) {
                release();
                pc_pointer = other.pc_pointer;
                pc_counter = other.pc_counter;
                if (pc_counter) {
                    pc_counter->iAdd();
                }
            }
            return *this;
        }

        // Move assignment
        SmartPointer& operator=(SmartPointer<T>&& other) noexcept {
            if (this != &other) {
                release();
                pc_pointer = other.pc_pointer;
                pc_counter = other.pc_counter;
                other.pc_pointer = nullptr;
                other.pc_counter = nullptr;
            }
            return *this;
        }

        // Dereference operators
        T& operator*() const { return *pc_pointer; }
        T* operator->() const { return pc_pointer; }

        // Get raw pointer (if needed)
        T* get() const { return pc_pointer; }

    private:
        RefCounter* pc_counter;
        T* pc_pointer;

        void release() {
            if (pc_counter) {
                if (pc_counter->iDec() == 0) {
                    delete pc_counter;
                    delete pc_pointer;
                }
                pc_counter = nullptr;
                pc_pointer = nullptr;
            }
        }
    };
}

#endif //CSMARTPOINTER_H
