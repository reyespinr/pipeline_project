import tkinter as tk
from tkinter import Menu, Text, Scrollbar

root = tk.Tk()
root.title("MIPS Simulator")

# Top Toolbar
menu_bar = Menu(root)
root.config(menu=menu_bar)
file_menu = Menu(menu_bar)
menu_bar.add_cascade(label="File", menu=file_menu)
file_menu.add_command(label="Open")
file_menu.add_command(label="Run")
file_menu.add_command(label="Save")

# Code Editor
editor = Text(root, wrap='word', undo=True, height=20)
editor.grid(row=0, column=1, sticky="nsew")
editor_scroll = Scrollbar(root, command=editor.yview)
editor_scroll.grid(row=0, column=2, sticky='ns')
editor['yscrollcommand'] = editor_scroll.set

# Console Output
console = Text(root, wrap='word', state='disabled', height=8)
console.grid(row=1, column=1, sticky="nsew")
console_scroll = Scrollbar(root, command=console.yview)
console_scroll.grid(row=1, column=2, sticky='ns')
console['yscrollcommand'] = console_scroll.set

# Register Contents (Placeholder Listbox for demonstration)
register_list = tk.Listbox(root)
register_list.grid(row=0, rowspan=2, column=0, sticky="ns")
for i in range(32):
    register_list.insert(tk.END, f"Register {i}")

root.grid_columnconfigure(1, weight=1) # Make editor and console expandable
root.grid_rowconfigure(0, weight=2)    # Give more weight to editor
root.grid_rowconfigure(1, weight=1)

root.mainloop()
