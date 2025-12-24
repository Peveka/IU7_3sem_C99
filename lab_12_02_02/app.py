import ctypes
import tkinter as tk
from tkinter import ttk, messagebox

lib = ctypes.CDLL('./libs/libsource.so')

lib.fill_fibonacci.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
lib.fill_fibonacci.restype = ctypes.c_int

lib.add_unique_elements.argtypes = [
    ctypes.POINTER(ctypes.c_int),
    ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_int),
    ctypes.POINTER(ctypes.c_size_t)
]
lib.add_unique_elements.restype = ctypes.c_int


def fill_fib(n: int):
    if n < 0:
        raise ValueError("n должно быть неотрицательным")
    out_count = ctypes.c_size_t()
    if n == 0:
        err = lib.fill_fibonacci(None, 0, ctypes.byref(out_count))
    else:
        arr = (ctypes.c_int * n)()
        err = lib.fill_fibonacci(arr, n, ctypes.byref(out_count))
        if err != 0:
            raise ValueError(f"Ошибка в fill_fibonacci: {err}")
        if out_count.value != n:
            raise ValueError("Несоответствие размера в fill_fibonacci")
        return list(arr)
    if err != 0:
        raise ValueError(f"Ошибка в fill_fibonacci: {err}")
    return []


def get_unique(src_list: list[int], method: int):
    src_size = len(src_list)
    src_arr = (ctypes.c_int * src_size)(*src_list) if src_list else None
    if src_size == 0:
        return []

    if method == 1:  # Выделить с запасом
        dst = (ctypes.c_int * src_size)()
        out_count = ctypes.c_size_t()
        err = lib.add_unique_elements(src_arr, src_size, dst, ctypes.byref(out_count))
        if err != 0:
            raise ValueError(f"Ошибка в add_unique_elements: {err}")
        return list(dst[:out_count.value])

    else:  # Сначала получить размер, потом только выделить размер памяти и опять вызвать с достаточным размером
        temp_dst = (ctypes.c_int * src_size)()
        out_count = ctypes.c_size_t()
        err = lib.add_unique_elements(src_arr, src_size, temp_dst, ctypes.byref(out_count))
        if err != 0:
            raise ValueError(f"Ошибка в add_unique_elements: {err}")
        count = out_count.value
        if count == 0:
            return []
        dst = (ctypes.c_int * count)()
        err = lib.add_unique_elements(src_arr, src_size, dst, ctypes.byref(out_count))
        if err != 0:
            raise ValueError(f"Ошибка в add_unique_elements: {err}")
        if out_count.value != count:
            raise ValueError("Несоответствие размера в add_unique_elements")
        return list(dst)


root = tk.Tk()

notebook = ttk.Notebook(root)
notebook.pack(pady=10, expand=True)

tab_fib = ttk.Frame(notebook)
notebook.add(tab_fib, text="Числа Фибоначчи")

tk.Label(tab_fib, text="Количество чисел (n):").pack(pady=5)
entry_fib = tk.Entry(tab_fib, width=20)
entry_fib.pack(pady=5)

result_fib = tk.Text(tab_fib, height=8, width=60)
result_fib.pack(pady=5)

def calc_fib():
    result_fib.delete(1.0, tk.END)
    try:
        n = int(entry_fib.get())
        res = fill_fib(n)
        result_fib.insert(tk.END, " ".join(map(str, res)))
    except ValueError as e:
        messagebox.showerror("Ошибка", str(e))

tk.Button(tab_fib, text="Сгенерировать", command=calc_fib).pack(pady=5)

tab_unique = ttk.Frame(notebook)
notebook.add(tab_unique, text="Уникальные элементы")

tk.Label(tab_unique, text="Элементы массива (через запятую):").pack(pady=5)
entry_unique = tk.Entry(tab_unique, width=60)
entry_unique.pack(pady=5)

result_unique = tk.Text(tab_unique, height=8, width=60)
result_unique.pack(pady=10)

def calc_unique(method: int):
    result_unique.delete(1.0, tk.END)
    try:
        text = entry_unique.get().strip()
        src = [int(x.strip()) for x in text.split(',')] if text else []
        res = get_unique(src, method)
        result_unique.insert(tk.END, f"Способ {method}: {' '.join(map(str, res))}")
    except ValueError as e:
        messagebox.showerror("Ошибка", str(e))

frame_buttons = tk.Frame(tab_unique)
frame_buttons.pack(pady=5)

tk.Button(frame_buttons, text="Способ 1 (с запасом)",
          command=lambda: calc_unique(1)).pack(side=tk.LEFT, padx=20)
tk.Button(frame_buttons, text="Способ 2 (узнать размер сначала)",
          command=lambda: calc_unique(2)).pack(side=tk.LEFT, padx=20)

root.mainloop()