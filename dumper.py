import os

OUTPUT_FILE = "tree_dump.txt"

# Az ignorálandó mappák listája
IGNORE_DIRS = {"venv", "__pycache__"}

TEXT_EXTENSIONS = {
    ".py", ".txt", ".c", ".h", ".ld", ".asm"
}

def write(line, file):
    print(line)
    file.write(line + "\n")

def is_text_file(filename):
    _, ext = os.path.splitext(filename.lower())
    return ext in TEXT_EXTENSIONS

def print_tree(path, file, prefix=""):
    try:
        items = sorted(os.listdir(path))
    except PermissionError:
        return

    for i, item in enumerate(items):
        item_path = os.path.join(path, item)
        
        # 🛡️ Itt ellenőrizzük, hogy a mappa benne van-e az ignorálandó listában
        if os.path.isdir(item_path) and item in IGNORE_DIRS:
            continue

        is_last = i == len(items) - 1
        connector = "└── " if is_last else "├── "
        write(prefix + connector + item, file)

        if os.path.isdir(item_path):
            new_prefix = prefix + ("    " if is_last else "│   ")
            print_tree(item_path, file, new_prefix)
        else:
            # Csak engedélyezett szövegfájlok tartalma
            if not is_text_file(item):
                continue

            try:
                with open(item_path, "r", encoding="utf-8", errors="ignore") as f:
                    new_prefix = prefix + ("    " if is_last else "│   ")
                    for line in f:
                        line = line.rstrip()
                        if not line:
                            continue
                        if len(line) > 120:
                            line = line[:117] + "..."
                        write(new_prefix + "| " + line, file)
            except Exception:
                continue

if __name__ == "__main__":
    # Az aktuális munkakönyvtár használata (vagy ahol a script van)
    root_folder = os.getcwd()

    with open(OUTPUT_FILE, "w", encoding="utf-8") as out:
        write(f"Directory tree of: {root_folder}\n", out)
        print_tree(root_folder, out)

    print(f"\n✔ Kimenet elmentve: {OUTPUT_FILE}")