# utouch - A Simple Yet Powerful File Manager for Linux

`utouch` is a **lightweight and intuitive** command-line utility for managing files on Linux.  
It combines the functionality of `touch`, `rm`, and a **basic text editor** into a single tool!

## Star and Follow
If you like my projects or find `utouch` useful, please **star** this repository and **follow** me for more! Thank you!

---

## Features:
- **Create a file** if it doesn't exist.
- **Read a file** (if it exists).
- **Delete files safely** using `utouch -r`.
- **Edit files interactively** with basic text operations (`utouch -e`).
  - **Type** to add lines.
  - **`-d`** deletes the last line.
  - **`Ctrl+W`** saves and exits.
  - **`Ctrl+Q`** quits without saving.
- **Update file timestamps** (like `touch`) using `utouch -t filename`.

---

## Installation:
```bash
git clone https://github.com/Darky-Github/utouch.git
cd utouch
make
sudo make install
```
## Uninstall
```bash
sudo make uninstall
```


# Usage
Creating and Reading a file:
```bash
utouch file.txt
```
Editing
```bash
utouch -e file.txt
```
Deleting
```bash
utouch -r file.txt
```
Timestamp
```bash
utouch -t file.txt
```
Help menu
```bash
utouch -h
```

## 🔥 Why Use `utouch` Instead of `touch`?

Unlike `touch`, which only creates files and updates timestamps, `utouch` **adds more functionality** without extra commands.

| Feature             | `touch` | `utouch` |
|---------------------|:------:|:--------:|
| Create files        | ✅     | ✅       |
| Read files         | ❌     | ✅       |
| Edit files         | ❌     | ✅       |
| Delete files       | ❌     | ✅       |
| Update timestamps  | ✅     | ✅       |
| Interactive Editing | ❌     | ✅ (`-e`) |
| Help Menu          | ❌     | ✅ (`-h`) |

**`utouch` combines `touch`, `rm`, and `nano` into one simple command!**

# LICENSE
This project is licensed under the MIT license.

# Support me
- Star this project
- Follow me
- Recommend to other users
