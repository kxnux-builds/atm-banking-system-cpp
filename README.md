# ATM Banking System in C++

A console-based ATM simulation built in modern C++ with a focus on secure authentication, account validation, transaction handling, and clear object-oriented design.

This project demonstrates how a banking workflow can be modeled in a compact terminal application using classes, STL containers, input validation, and cross-platform console behavior.

## Overview

The application simulates a real ATM machine with:

- User login using a unique ID and 4-digit PIN
- Account lock after repeated failed login attempts
- Balance inquiry
- Cash deposits
- Cash withdrawals with insufficient-funds checks
- Mini statement showing recent transactions
- Date and time tracking for each transaction
- Cross-platform support for Windows and Linux/macOS

The project is intentionally simple and beginner-friendly while still showing strong OOP and practical software design patterns.

## Features

### Authentication and security

- Secure PIN verification
- Account lockout after 3 failed attempts
- Guarded access to user session
- Validation of user existence before login

### Banking operations

- Check account balance
- Deposit money into an account
- Withdraw money with balance validation
- Transaction history with credit/debit tracking

### User experience

- Clear terminal-based menu system
- Prompt-driven keyboard input
- Real-time transaction feedback
- Mini statement listing the most recent transactions
- Safe exit flow with logout handling

### Implementation quality

- Encapsulation through `BankAccount` and `AtmMachine` classes
- Use of `std::vector` for transaction records
- Use of `std::unordered_map` for account lookup
- Cross-platform console and sleep handling
- Input sanitization for invalid user entries

## Project structure

```text
atm-banking-system-cpp/
├── .gitignore
├── LICENSE
├── README.md
└── main.cpp
```

## Main code architecture

The application is structured around two core classes:

- `BankAccount`
  - Stores user details like ID, name, PIN, balance, lock status, and transaction history
  - Validates PIN input
  - Handles deposit and withdrawal logic
  - Tracks recent transactions with timestamps

- `AtmMachine`
  - Maintains the in-memory database of users
  - Provides ATM session flow
  - Displays menu options and handles user interaction
  - Loads sample accounts and starts the service loop

## How the program works

1. The program registers demo bank accounts in memory.
2. The user enters a customer ID.
3. If the user exists, the user is asked for a PIN.
4. If the PIN matches, the ATM opens the user session.
5. The user can choose from:
   - Check balance
   - Deposit cash
   - Withdraw cash
   - View mini statement
   - Logout
6. After 3 incorrect PIN attempts, the account is locked.
7. The session continues until the user logs out or exits the application.

## Default demo accounts

The project includes sample users for demonstration purposes:

- User ID: `arjun`
  - Name: `Arjun Das`
  - PIN: `3331`
  - Balance: `47000.50`

- User ID: `sneha`
  - Name: `Sneha Roy`
  - PIN: `9876`
  - Balance: `92000.00`

- User ID: `admin`
  - Name: `Kishanu Mondal`
  - PIN: `0000`
  - Balance: `500000.00`

These are hardcoded in `main()` for demo and learning purposes.

## Requirements

To compile this project, you need:

- A C++ compiler such as `g++`
- A terminal or command prompt
- A Linux, macOS, or Windows environment

## Build and run

### Linux / macOS

```bash
g++ -std=c++17 main.cpp -o atm
./atm
```

### Windows (MinGW / MSYS2 / Git Bash)

```bash
g++ main.cpp -o atm.exe
atm.exe
```

## Example interaction

```text
==================================================
ICICI BANK - WELCOME
==================================================
Please insert your card details below.

Enter User ID (or 'exit'): arjun
Enter 4-Digit PIN: 3331

Welcome, Arjun Das

1. Check Balance
2. Deposit Cash
3. Withdraw Cash
4. Mini Statement
5. Logout
```

## Transaction behavior

The program validates every transaction before execution:

- Deposit amounts must be greater than zero
- Withdrawal amounts must be greater than zero
- Withdrawal cannot exceed the current balance
- Invalid inputs are rejected cleanly
- Recent transactions are stored with a date and time stamp

## Mini statement example

The mini statement shows the latest five transaction entries with:

- Date
- Transaction type (`Credit` or `Debit`)
- Amount

This gives the user a concise summary of recent account activity.

## Notes on the implementation

This repository is a compact educational project and does not currently include:

- Persistent database storage
- Real banking backend connectivity
- Multi-user account files
- Encryption of PINs
- Networked ATM server/client architecture

The app stores account data in memory only while the program is running.

## Security considerations

This is a simulation and not a production-grade banking system. In a real environment, the following would be required:

- Secure password/PIN hashing
- Encrypted data storage
- Role-based access control
- Audit logging
- Database persistence
- Secure money transfer logic

## Potential improvements

Possible enhancements for future versions:

- Persistent account storage using files or a database
- Support for multiple accounts per customer
- Transfer money between accounts
- Change PIN feature
- Detailed full transaction history
- Better menu navigation and validation
- Graphical interface version

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Summary

The ATM Banking System project is a clean and practical C++ demonstration of core banking operations, user authentication, secure transaction control, and OOP-based design. It is suitable for learning, coding practice, academic projects, and portfolio showcases.

If you want to extend it further, this project is a strong starting point for building a more complete banking management system.
