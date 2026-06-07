# 🏦 Bank Management System

A console-based Bank Management System developed in C++ that simulates core banking operations such as account creation, deposits, withdrawals, transfers, interest calculation, and account management. The project demonstrates the practical application of Object-Oriented Programming (OOP) concepts while implementing real-world banking rules and validations.

## ✨ Features

### Account Management

* Create Savings Accounts
* Create Checking Accounts
* Create Business Accounts
* Prevent duplicate account creation
* Validate account details during registration

### Banking Operations

* Deposit money
* Withdraw money
* Transfer funds between accounts
* Calculate interest for all accounts
* Display account information

### Account-Specific Functionality

#### 💰 Savings Account

* Minimum balance requirement
* Monthly withdrawal limit
* Interest calculation

#### 🏧 Checking Account

* Overdraft facility
* Overdraft fee handling
* Overdraft limit validation

#### 🏢 Business Account

* Monthly transaction tracking
* Free transaction limit
* Transaction fee after limit is exceeded

### Reports & Analytics

* Display all accounts
* Bank statistics dashboard
* Account type distribution
* Total funds across all accounts

### Validation & Security

* Duplicate account number prevention
* Negative balance validation
* Invalid deposit/withdrawal protection
* Account existence verification

---

## 🛠️ Technologies Used

* C++
* Object-Oriented Programming (OOP)
* Standard Template Library (STL)
* Dynamic Memory Management

---

## 🏗️ OOP Concepts Implemented

* Encapsulation
* Inheritance
* Abstraction
* Polymorphism
* Function Overriding
* Runtime Polymorphism
* Virtual Destructors

---

## 📂 Class Structure

```text
Account (Abstract Base Class)
│
├── SavingsAccount
├── CheckingAccount
└── BusinessAccount

BankSystem
│
└── Manages all accounts and banking operations
```

---

## 🚀 How to Run

### Compile

```bash
g++ main.cpp -o bank
```

### Execute

```bash
./bank
```

---

## 🎯 Learning Outcomes

This project strengthened my understanding of:

* Object-Oriented Design
* Runtime Polymorphism
* Class Relationships
* Business Logic Implementation
* Input Validation
* Dynamic Memory Management
* Software Design Principles

---

## 📈 Future Improvements

* File Handling (Save & Load Account Data)
* Transaction History
* Account Deletion
* Monthly Statements
* Smart Pointers (`std::unique_ptr`)
* Multi-file Project Structure
* Database Integration
