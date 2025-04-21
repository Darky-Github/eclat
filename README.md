# eclat - A Simple Yet Powerful File Manager for Linux

`eclat` is a **lightweight and intuitive** command-line utility for managing files on Linux.  
It combines the functionality of `touch`, `rm`, and a **basic text editor** into a single tool!

## Star and Follow
If you like my projects or find `eclat` useful, please **star** this repository and **follow** me for more! Thank you!

---

## Features:
- **Create a file** if it doesn't exist.
- **Read a file** (if it exists).
- **Delete files safely** using `eclat -r`.
- **Edit files interactively** with basic text operations (`eclat -e`).
  - **Type** to add lines.
  - **`-d`** deletes the last line.
  - **`Ctrl+W`** saves and exits.
  - **`Ctrl+Q`** quits without saving.
- **Update file timestamps** (like `touch`) using `eclat -t filename`.

---

## Installation:
```bash
git clone https://github.com/Darky-Github/eclat.git
cd eclat
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
eclat file.txt
```
Editing
```bash
eclat -e file.txt
```
Deleting
```bash
eclat -r file.txt
```
Timestamp
```bash
eclat -t file.txt
```
Help menu
```bash
eclat -h
```

## Why Use `eclat` Instead of `touch`?

Unlike `touch`, which only creates files and updates timestamps, `eclat` **adds more functionality** without extra commands.

| Feature             | `touch` | `eclat` |
|---------------------|:------:|:--------:|
| Create files        | ✅     | ✅       |
| Read files         | ❌     | ✅       |
| Edit files         | ❌     | ✅       |
| Delete files       | ❌     | ✅       |
| Update timestamps  | ✅     | ✅       |
| Interactive Editing | ❌     | ✅ (`-e`) |
| Help Menu          | ❌     | ✅ (`-h`) |

**`eclat` combines `touch`, `rm`, and a simple `nano-like' into one simple command!**

# LICENSE
This project is licensed under the MIT license.

# Support me
- Star this project
- Follow me
- Recommend to other users

Old name: utouch
