# 🖐️ utouch - A Simple Yet Powerful File Manager for Linux

`utouch` is a **lightweight and intuitive** command-line utility for managing files on Linux.  
It combines the functionality of `touch`, `rm`, and a **basic text editor** into a single tool!

## ✨ Features:
- 📁 **Create a file** if it doesn't exist.
- 📖 **Read a file** (if it exists).
- ❌ **Delete files safely** using `utouch -r`.
- 📝 **Edit files interactively** with basic text operations (`utouch -e`).
  - **Type** to add lines.
  - **`-d`** deletes the last line.
  - **`Ctrl+W`** saves and exits.
  - **`Ctrl+Q`** quits without saving.

## 🚀 Installation:
```bash
git clone https://github.com/yourusername/utouch.git
cd utouch
make
sudo cp utouch /usr/local/bin/

