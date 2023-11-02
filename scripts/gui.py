import tkinter as tk
from tkinter import ttk, Text, Scrollbar, filedialog


class ToolTip:
    def __init__(self, widget, text):
        self.widget = widget
        self.text = text
        self.tooltip = None
        self.widget.bind("<Enter>", self.on_enter)
        self.widget.bind("<Leave>", self.on_leave)

    def on_enter(self, event=None):
        x, y, _, _ = self.widget.bbox("insert")
        x += self.widget.winfo_rootx()
        y += self.widget.winfo_rooty() + 50
        self.tooltip = tk.Toplevel(self.widget)
        self.tooltip.wm_overrideredirect(True)
        self.tooltip.wm_geometry(f"+{x}+{y}")
        label = tk.Label(self.tooltip, text=self.text,
                         relief=tk.SOLID, borderwidth=1, background='#ffffe0')
        label.pack()

    def on_leave(self, event=None):
        if self.tooltip:
            self.tooltip.destroy()
            self.tooltip = None


root = tk.Tk()
root.title("MIPS Simulator")

# Global variable to hold the file path of the opened file
current_filepath = None

# Functionality for the Open Button


def open_file():
    global current_filepath
    filepath = filedialog.askopenfilename(
        filetypes=[("ASM Files", "*.asm"), ("All Files", "*.*")])
    if not filepath:
        return

    with open(filepath, 'r') as file:
        editor.delete(1.0, tk.END)  # Clear the current content in the editor
        editor.insert(tk.END, file.read())

    # Update the global variable
    current_filepath = filepath
    # Update the filename display label
    filename_display.config(text=filepath.split('/')[-1])


# Top Toolbar with Buttons
toolbar_frame = ttk.Frame(root)
toolbar_frame.grid(row=0, column=0, columnspan=3, sticky="w")

# Load and resize the icons from the "icons" directory
open_icon = tk.PhotoImage(file="icons/open.png")
open_icon = open_icon.subsample(25, 25)
open_btn = ttk.Button(toolbar_frame, width=0.1,
                      image=open_icon, compound="left", command=open_file)
open_btn.grid(row=0, column=0)

save_icon = tk.PhotoImage(file="icons/save.png")
save_icon = save_icon.subsample(25, 25)
save_btn = ttk.Button(toolbar_frame, width=0.1,
                      image=save_icon, compound="left")
save_btn.grid(row=0, column=1)

build_icon = tk.PhotoImage(file="icons/build.png")
build_icon = build_icon.subsample(25, 25)
build_btn = ttk.Button(toolbar_frame, width=0.1,
                       image=build_icon, compound="left")
build_btn.grid(row=0, column=2)

run_icon = tk.PhotoImage(file="icons/run.png")
run_icon = run_icon.subsample(25, 25)
run_btn = ttk.Button(toolbar_frame, width=0.1,
                     image=run_icon, compound="left")
run_btn.grid(row=0, column=3)

ToolTip(open_btn, "Open file")
ToolTip(save_btn, "Save current file")
ToolTip(build_btn, "Build program")
ToolTip(run_btn, "Run program")

# Add a label to display the name of the currently opened file
filename_display = ttk.Label(
    root, text="No file opened", relief="sunken", anchor="w", padding=(5, 5))
filename_display.grid(row=1, column=0, columnspan=2, sticky="ew")

# Code Editor (updated row to push it down one spot)
editor = Text(root, wrap='word', undo=True, height=20)
editor.grid(row=2, column=0, sticky="nsew")
editor_scroll = Scrollbar(root, command=editor.yview)
editor_scroll.grid(row=1, column=1, sticky='ns')
editor['yscrollcommand'] = editor_scroll.set


# Console Output
console = Text(root, wrap='word', state='disabled', height=8)
console.grid(row=3, column=0, sticky="nsew")
console_scroll = Scrollbar(root, command=console.yview)
console_scroll.grid(row=2, column=1, sticky='ns')
console['yscrollcommand'] = console_scroll.set

# Register Contents (on the right side)
register_list = tk.Listbox(root)
register_list.grid(row=1, rowspan=2, column=2, sticky="ns")
for i in range(32):
    register_list.insert(tk.END, f"Register {i}")

root.grid_columnconfigure(0, weight=1)  # Make editor and console expandable
root.grid_rowconfigure(1, weight=2)     # Give more weight to editor
root.grid_rowconfigure(2, weight=1)

root.mainloop()
