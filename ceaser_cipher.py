import tkinter as tk
from tkinter import messagebox

def caesar(s, key, mode):
    out = ""
    for ch in s:
        if ch.isalpha():
            a = ord('A') if ch.isupper() else ord('a')
            off = (ord(ch) - a + (key if mode=="enc" else -key)) % 26
            out += chr(a + off)
        else:
            out += ch
    return out

def show_result(result):
    win = tk.Toplevel(root)
    win.title("Result")
    win.geometry("350x150")

    tk.Label(win, text="Output:").pack(anchor="w")

    txt = tk.Text(win, height=4, width=40)
    txt.pack()
    txt.insert("1.0", result)
    txt.config(state="disabled")     # user can’t edit

    def copy_to_clip():
        root.clipboard_clear()
        root.clipboard_append(result)
        messagebox.showinfo("Copied", "Copied to clipboard!")

    tk.Button(win, text="Copy", width=10, command=copy_to_clip).pack(side="left", padx=20, pady=10)
    tk.Button(win, text="Close", width=10, command=win.destroy).pack(side="right", padx=20, pady=10)

def run(mode):
    try:
        key = int(key_entry.get())
    except:
        messagebox.showerror("Error","Key must be a number")
        return
    
    text = text_entry.get("1.0","end-1c")
    result = caesar(text, key, mode)
    show_result(result)

root = tk.Tk()
root.title("Caesar Cipher")

tk.Label(root, text="Text").grid(row=0, column=0, sticky="nw")
text_entry = tk.Text(root, width=40, height=6)
text_entry.grid(row=0,column=1)

tk.Label(root, text="Key (number)").grid(row=1, column=0, sticky="w")
key_entry = tk.Entry(root)
key_entry.grid(row=1, column=1, sticky="w")

tk.Button(root, text="Encrypt", width=12, command=lambda: run("enc")).grid(row=2, column=0, pady=5)
tk.Button(root, text="Decrypt", width=12, command=lambda: run("dec")).grid(row=2, column=1, pady=5)

root.mainloop()

