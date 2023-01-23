import tkinter as tk
from tkinter import filedialog
import subprocess

def on_submit():
    folder_path = folder_entry.get()
    string_value = string_entry.get()
    if folder_path == "" or string_value == "":
        label.config(text="Por favor, preencha todos os campos", fg="red")
    else:
        subprocess.run(["powershell.exe", ".\\teste.ps1", "-folderPath", folder_path, "-folderName", string_value])
        label.config(text="Arquivos criados com sucesso!", fg="green")

def browse_folder():
    folder_path = filedialog.askdirectory()
    folder_entry.delete(0, tk.END)
    folder_entry.insert(0, folder_path)

root = tk.Tk()
root.geometry("450x150")
root.configure(bg="white")
root.title("Criar Pasta e Arquivos")

folder_label = tk.Label(root, text="Caminho da pasta:", bg="white")
folder_label.pack()
folder_entry = tk.Entry(root, bd=1, relief="solid", width=60)
folder_entry.pack()
folder_button = tk.Button(root, text="Procurar", command=browse_folder, bg="#009688", fg="white", borderwidth=0, width=51)
folder_button.pack()

string_label = tk.Label(root, text="Nome da pasta:", bg="white")
string_label.pack()
string_entry = tk.Entry(root, bd=1, relief="solid", width=60)
string_entry.pack()

submit_button = tk.Button(root, text="Enviar", command=on_submit, bg="#009688", fg="white", borderwidth=0, width=51)
submit_button.pack()

label = tk.Label(root, bg="white")
label.pack()

root.mainloop()