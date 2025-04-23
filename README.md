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
