# 🏦 ATM Banking System (C++)

A **console-based ATM Banking System** developed using **modern C++** and **Object-Oriented Programming (OOP)** principles.  
This project simulates real-world ATM operations with a strong focus on **security, reliability, and clean system design**.

---

## 🗂️ Project Structure

atm-banking-system-cpp/
│
├── .gitignore
├── LICENSE
├── README.md
└── main.cpp

---

## 📌 Overview

The ATM Banking System provides a realistic simulation of core banking operations such as secure authentication, balance management, cash transactions, and transaction history tracking.  
It demonstrates how a structured and maintainable C++ application can accurately model real-world financial workflows.

This project is ideal for **academic submission**, **resume projects**, and **technical interviews**.

---

## ❓ Problem Statement

Understanding ATM workflows theoretically often lacks hands-on exposure to secure system design and transaction validation.  
This project bridges that gap by implementing a **practical ATM simulation** that enforces authentication rules, validates transactions, and maintains system integrity using Object-Oriented Programming principles.

---

## 🎯 Objectives

- Simulate real-world ATM operations
- Apply Object-Oriented Programming in C++
- Implement secure user authentication
- Ensure accurate transaction handling
- Build a clean, modular, and maintainable codebase

---

## ✨ Features

### 🔐 Security & Authentication
- Secure **4-digit PIN verification**
- Automatic **account lock after three failed login attempts**
- Protection against unauthorized access

### 💳 Banking Operations
- **Balance Inquiry** — View real-time account balance
- **Cash Deposit** — Safely deposit funds
- **Cash Withdrawal** — Includes insufficient balance checks
- **Mini Statement** — Displays the last five transactions with date and time

### 📊 Transaction Management
- Tracks **Credit / Debit** transactions
- Maintains per-user transaction history
- Time-stamped records for transparency

### 🧱 System Design
- Fully **Object-Oriented Architecture**
- Proper encapsulation of account data
- Modular and reusable components

### 🖥️ Platform Compatibility
- Cross-platform support for **Windows** and **Linux**
- Automatic handling of console clearing and system delays

---

## 🛠️ Technologies & Concepts Used

- **Programming Language:** C++
- **Concepts & Tools:**
  - Object-Oriented Programming (OOP)
  - STL Containers (`vector`, `unordered_map`)
  - Input validation and error handling
  - Date and time handling
  - Cross-platform system calls

---

## ▶️ Compilation & Execution

- **Linux / macOS**
  - g++ main.cpp -o atm
  - ./atm

- **Windows (MinGW)**
  - g++ main.cpp -o atm.exe
  - atm.exe

---

## 📄 License

  - This project is licensed under the MIT License, allowing free use, modification, and distribution for educational and personal purposes.

---