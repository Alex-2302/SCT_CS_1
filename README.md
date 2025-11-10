# Caesar Cipher GUI — README

A small, single-file Python app with a simple Tkinter GUI that encrypts and decrypts text using the classic Caesar cipher.
When you click **Encrypt** or **Decrypt**, a result popup appears with **Copy** and **Close** buttons so you can copy the output to your clipboard instantly.

---

## Features

* Encrypt and decrypt text using a numeric key (shift).
* Preserves letter case and leaves non-letter characters unchanged.
* Result appears in a small popup window with:

  * Read-only output field
  * **Copy** button (copies result to clipboard)
  * **Close** button
* No external libraries required — pure `tkinter`.

---

## Requirements

* Python 3.7+ (should work on any Python 3.x)
* `tkinter` (usually included with standard Python installations)
* Works on Windows, macOS, and Linux (provided `tkinter` is available)

---

## Installation

1. Make sure Python 3 is installed. Check with:

```bash
python --version
```

2. Save the script to a file, for example:

```
caesar_gui.py
```

---

## Usage

Run the script:

```bash
python caesar_gui.py
```

How to use the GUI:

1. Type or paste the text you want to encrypt/decrypt into the **Text** box.
2. Enter an integer in **Key (number)** (commonly 0–25).
3. Click **Encrypt** to shift letters forward by the key, or **Decrypt** to shift letters backward.
4. A small popup shows the result. Click **Copy** to copy the output to your clipboard, or **Close** to dismiss.

### Example

* Input text: `Hello, World!`
* Key: `3`
* Encrypt → `Khoor, Zruog!`
* Decrypt `Khoor, Zruog!` with key `3` → `Hello, World!`

---

## Code overview

Main parts of the script:

* `caesar(s, key, mode)` — core function that applies the Caesar shift; handles uppercase/lowercase and non-letters.
* `run(mode)` — reads UI inputs, validates key, calls `caesar()` and displays the result popup.
* `show_result(result)` — custom popup (Toplevel) with read-only text, **Copy**, and **Close** buttons.
* Tkinter layout — main window with a `Text` widget for input, `Entry` for key, and buttons.

---

## Customization ideas

* Add a “Brute force / Auto-detect key” button to show all 26 possible decryptions.
* Automatically place the result into the input box for chaining operations.
* Add keyboard shortcuts (e.g., Ctrl+Enter to encrypt).
* Save results to a file or automatically copy on popup open.
* Add more cipher options (Vigenère, Rot13, etc.).

---

## Troubleshooting

* **`tkinter` not found**: On some Linux distributions you may need to install `tk` / `python3-tk` via your package manager, e.g.:

  * Debian/Ubuntu: `sudo apt install python3-tk`
  * Fedora: `sudo dnf install python3-tkinter`
* **Key must be a number** error: Ensure you entered an integer (no letters, decimals, or blank).
* If the window appears very small or fonts look odd, try resizing the window or running the script with a different system theme.

---

