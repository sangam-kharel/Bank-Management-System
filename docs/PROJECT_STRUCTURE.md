# 📁 Project Structure

```
Bank-Management-System/
│
├── src/                        # C source implementation files
│   ├── main.c                  # Entry point — menus and program flow
│   ├── account.c               # Account creation, login, profile management
│   ├── transaction.c           # Deposit, withdrawal, transfer logic
│   ├── admin.c                 # Admin login and management features
│   └── utility.c               # Shared helper functions (validation, formatting)
│
├── include/                    # Header files (structs, prototypes, constants)
│   ├── account.h
│   ├── transaction.h
│   ├── admin.h
│   └── utility.h
│
├── database/                   # Binary data files (auto-created on first run)
│   ├── accounts.dat            # Stores all customer account records
│   └── transactions.dat        # Stores all transaction history
│
├── docs/                       # Project documentation
│   ├── PROJECT_STRUCTURE.md    # This file
│   ├── ROADMAP.md              # Planned features and milestones
│   └── CHANGELOG.md            # Version history and release notes
│
├── screenshots/                # UI screenshots (added after UI is complete)
│
├── Makefile                    # Build automation (make / make clean)
├── LICENSE                     # MIT License
└── README.md                   # Project overview and getting started guide
```

---

## 🗂 Directory Purposes

| Directory / File | Purpose |
|-----------------|---------|
| `src/` | All `.c` implementation files — where the logic lives |
| `include/` | All `.h` header files — structs, constants, and function prototypes |
| `database/` | Binary `.dat` files for persistent storage; auto-generated at runtime |
| `docs/` | Markdown documentation files for the project |
| `screenshots/` | UI screenshots to be added once the interface is complete |
| `Makefile` | Compiles the project with a single `make` command |
| `README.md` | Top-level project introduction and usage guide |
