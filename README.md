# 📚 Library Book Borrowing System

A multi-threaded simulation of the classic **Reader-Writer problem**, implemented using `pthreads`, `mutexes`, and `semaphores` in **C**. This project models students (readers) accessing a library's book records while librarians (writers) update them — developed as part of our **Operating Systems semester project**.

---

## 🔧 Features

- Simulates concurrent readers and writers
- Reader-Priority synchronization model
- Thread-safe access to shared book records
- Uses POSIX threads, semaphores, and mutexes
- Console-based interface with descriptive output

---

## 🚀 How to Run

```bash
gcc -o library main.c -lpthread
./library

🧠 Concept
This project demonstrates how to solve the Reader-Writer Problem, where:

Multiple readers can read at the same time.

Writers must have exclusive access.

Synchronization is handled using pthread_mutex_t and sem_t.

Library-System-OS-Project/
├── main.c              # Entry point with thread creation
├── book_operations.c   # Functions to add/view/remove books
├── book_operations.h   # Declarations
├── thread_manager.c    # Reader/writer thread logic
├── thread_manager.h
└── README.md

📚 Course Info
Course: Operating Systems
Instructor: Atiya Jokhio
Semester: Spring'25
Institution: Fast NUCES Khi
