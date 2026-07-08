# 🗺️ Development Roadmap

This roadmap tracks the development progress of the Bank Management System. Every version represents a stable milestone that compiles successfully, passes manual testing, and is committed to GitHub.

---

# ✅ Completed Milestones

## v0.1.0 — Project Initialization

**Status:** ✅ Completed

### Objectives

* Initialize Git repository
* Create GitHub repository
* Configure project workspace

### Completed

* Git repository initialized
* GitHub repository connected
* Initial commit completed

---

## v0.2.0 — Project Structure

**Status:** ✅ Completed

### Completed

* Professional folder structure
* Makefile
* README.md
* LICENSE
* `database/`
* `docs/`
* `include/`
* `screenshots/`
* `src/`

---

## v0.3.0 — Project Skeleton

**Status:** ✅ Completed

### Completed

Created source modules:

* main.c
* account.c
* database.c
* transaction.c
* admin.c
* utility.c

Created header files:

* account.h
* database.h
* transaction.h
* admin.h
* utility.h

Implemented modular project architecture.

---

## v0.4.0 — Main Menu

**Status:** ✅ Completed

### Completed

Implemented the main navigation menu:

```text
1. Create Account
2. Customer Login
3. Administrator Login
4. Exit
```

Navigation between modules established.

---

## v0.5.0 — Account Creation System

**Status:** ✅ Completed

### Completed

Implemented complete customer account creation.

Features:

* Full Name
* Father's Name
* Address
* Phone Number
* Email Address
* Account Type
* 4-digit PIN
* Initial Deposit

Additional work:

* Input validation
* Empty input handling
* PIN validation
* Deposit validation
* Account preview screen
* Clean console formatting

---

## v0.6.0 — Binary Database System

**Status:** ✅ Completed

### Completed

Database layer fully implemented.

Implemented functions:

* `saveAccount()`
* `accountExists()`
* `generateAccountNumber()`
* `findAccount()`
* `findAccountPosition()`
* `updateAccount()`

Implemented binary storage:

* `accounts.dat`
* `transactions.dat` (prepared for future use)

Architecture improvements:

* Created dedicated `database.c`
* Created dedicated `database.h`
* Moved all database logic out of `account.c`
* Separated UI logic from database logic
* Improved modularity and maintainability

Testing completed:

* Account creation
* Persistent storage
* Reading binary records
* Updating binary records
* Automatic account number generation

Current project architecture is stable and ready for feature development.

---

# 🚧 Upcoming Milestones

---
 
## v0.7.0 — Customer Authentication
 
**Status:** ✅ Completed
 
### Completed
 
Implemented complete customer authentication system.
 
Features:
 
* Customer Login
* Account Number verification
* PIN verification
* Password verification (optional)
* Authentication system
* Customer session
* Logout functionality
* View Balance (in dashboard)
 
### Technical Changes
 
* Updated `customerLogin()` to use Account Number instead of Phone
* Added `verifyPIN()` function in account.c
* Added `verifyPassword()` function in account.c
* Implemented `customerDashboard()` with menu navigation
* Removed phone-based authentication functions
* Clean console formatting maintained
 
---
 
## v0.8.0 — Deposit System
 
**Status:** ✅ Completed
 
### Completed
 
Implemented complete deposit system.
 
Features:
 
* Deposit money
* Amount validation
* Update account balance
* Save updated account
* Record transaction history
 
### Technical Changes
 
* Created `Transaction` struct in transaction.h
* Implemented `saveTransaction()` in transaction.c
* Implemented `getTransactions()` in transaction.c
* Implemented `depositMoney()` in transaction.c
* Added deposit functionality in customerDashboard()
* Transaction records stored in `transactions.dat`
 
---
 
# v0.9.0 — Withdraw System

**Status:** ⏳ Planned

### Features

* Withdraw money
* Insufficient balance checking
* Update database
* Record transaction

---

# v1.0.0 — Customer Dashboard

**Status:** ⏳ Planned

### Features

Customer menu after successful login:

```text
1. Check Balance
2. Deposit
3. Withdraw
4. Transaction History
5. Change PIN
6. Logout
```

---

# v1.1.0 — Transaction Management

**Status:** ⏳ Planned

### Features

* Transaction history
* Deposit records
* Withdrawal records
* Date & time logging
* Mini statement

---

# v1.2.0 — Account Management

**Status:** ⏳ Planned

### Features

* Search account
* Update customer information
* Delete account
* Change PIN

---

# v1.3.0 — Administrator Module

**Status:** ⏳ Planned

### Features

Administrator authentication

Administrator dashboard

View all accounts

Search accounts

Delete accounts

Customer statistics

Database statistics

---

# v1.4.0 — Banking Operations

**Status:** ⏳ Planned

### Features

* Money transfer
* Internal transaction processing
* Atomic balance updates
* Transfer history

---

# v1.5.0 — Reporting System

**Status:** ⏳ Planned

### Features

* Customer reports
* Financial reports
* Total deposits
* Total withdrawals
* Total bank balance

---

# v1.6.0 — Database Utilities

**Status:** ⏳ Planned

### Features

* Database backup
* Database restore
* Export data
* Import data
* Integrity verification

---

# v2.0.0 — Stable Release

**Status:** 🎯 Final Goal

Complete banking system with:

* Full customer management
* Administrator management
* Transaction management
* Reporting
* Database utilities
* Professional documentation
* Clean modular architecture
* Portfolio-ready GitHub repository

---

# 📊 Current Progress

| Milestone | Status        |
| --------- | ------------- |
| v0.1.0    | ✅ Completed   |
| v0.2.0    | ✅ Completed   |
| v0.3.0    | ✅ Completed   |
| v0.4.0    | ✅ Completed   |
| v0.5.0    | ✅ Completed   |
| v0.6.0    | ✅ Completed   |
| v0.7.0    | ✅ Completed   |
| v0.8.0    | ✅ Completed   |
| v0.9.0    | ⏳ Next        |
| v1.0.0    | ⏳ Pending     |
| v1.1.0    | ⏳ Pending     |
| v1.2.0    | ⏳ Pending     |
| v1.3.0    | ⏳ Pending     |
| v1.4.0    | ⏳ Pending     |
| v1.5.0    | ⏳ Pending     |
| v1.6.0    | ⏳ Pending     |
| v2.0.0    | 🎯 Final Goal |
 
---
 
# 🎯 Current Development Target
 
**Current Stable Version:** **v0.8.0**
 
**Next Development Version:** **v0.9.0 – Withdraw System**

The project foundation is now complete. All future development will build upon the stable modular architecture and binary database layer implemented through v0.6.0.
