# `ember` — starter skeleton (Lab 1)

Copy this folder to a repository of your own, `git init`, and start from **M1** of
[Lab 01](../lab-01-a-box-of-bytes.md). It builds and runs as-is.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/ember
```

## Why a skeleton exists

Lab 1 is about **bytes and types**. It is not about `while` loops, splitting a
string into words, or `std::setw` — you meet those properly in Labs 4, 5 and 7.
So the parts that need them are given to you, fully written and commented. You
read those. You write the four small things that *are* Lab 1.

## Given — read it, don't rewrite it

| File | What it does |
|---|---|
| `CMakeLists.txt` | C++17, `-Wall -Wextra -Werror`, ASan + UBSan on Debug |
| `src/main.cpp` | the prompt: read a line, split it into words, call your functions |
| `src/memory.hpp` | `Byte`, `MEM_SIZE`, `struct Memory` — the box |
| `src/dump.hpp` | the two declarations |
| `src/dump.cpp` → `dump()` | the hex dump loop |

## Yours — four `TODO(lab-01)` markers

```bash
grep -rn "TODO(lab-01)" src/
```

| # | Where | The job |
|---|---|---|
| 1 | `memory.cpp` → `mem_get` | return the byte, or 0 if the address is outside the box |
| 2 | `memory.cpp` → `mem_set` | write the byte, or return `false` if the address is outside |
| 3 | `dump.cpp` → the ASCII gutter | print the character when the byte is printable |
| 4 | `dump.cpp` → `show_byte` | one byte, four views |

When all four are done:

```txt
ember> set 0 65
ember> set 1 66
ember> get 0
65  0x41  0b01000001  'A'
ember> dump
0000  41 42 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |AB..............|
```

That is M2 and M3 of Lab 1. M4 (the three deliberate breakages) is in the lab.

Until you implement `mem_set`, `set` accepts everything and stores nothing, and
`get` prints `show_byte: not implemented yet`. That is the starting state, not a
bug.

## Later labs

You keep this repository for all eight labs. Every lab adds one `else if` branch
to the dispatcher in `main.cpp` and one or two new files next to these.

---

## Українською

Скопіюйте цю теку у свій репозиторій — вона вже збирається й запускається.

Lab 1 — про **байти й типи**, а не про цикли, розбір рядка на слова чи
форматування виводу (це Labs 4, 5, 7). Тому все, що потребує ще не пройденого,
вам **дано** — з коментарями, щоб читати. Ви пишете чотири маленькі речі, які й
є Lab 1: `mem_get`, `mem_set`, ASCII-колонку в дампі та `show_byte`.

Знайти свою роботу: `grep -rn "TODO(lab-01)" src/`.

Якщо C++ бачите вперше — спочатку
[C++ за годину](../cpp-survival-kit.notes.md), потім
[інструменти й git](../setup.notes.md).




### 1. Переповнення Byte


Після `set 0 255` і `inc 0` значення стало `0`.
`Byte` зберігає значення від 0 до 255, тому збільшення 255 дає перехід
через межу до 0. Переповнення знакового `int` відрізняється: це невизначена
поведінка, яку виявляє UBSan.

```txt
ember> set 0 255
ember> inc 0
ember> get 0
0 0x0 0b00000000 '.'
```

### 2. Float числа

`0.1 + 0.1 + 0.1 == 0.3` повертає `false`, тому що десяткові дроби
на кшталт `0.1` зазвичай неможливо точно представити у двійковому форматі
`double`. Сума виходить дуже близькою до `0.3`, але не обов’язково дорівнює їй.

```txt
c++ -std=c++17 -Wall -Wextra -Werror scratch.cpp -o scratch && ./scratch
result = 0.30000000000000004
result == 0.3: false
```

### 3. C-рядок 
```txt
ember> set 0 65
ember> set 1 66 
ember> set 2 0
ember> dump
0000  41 42 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |AB..............|
0010  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |................|
0020  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |................|
```

### 4. Неініціалізована памʼять 

Після видалення `{}` з `Byte data[MEM_SIZE]{}` команда `dump` pвиводить
невизначені значення. Потім дужки `{}` було повернуто на місце, оскільки
читання неініціалізованої пам’яті є невизначеною поведінкою.

```txt
ember> dump
0000  d0 64 e7 6a 01 00 00 00 40 d3 ba fb 01 00 00 00  |.d.j....@.......|
0010  c0 55 e7 6a 01 00 00 00 14 a6 0a 8f 01 00 00 00  |.U.j............|
0020  f4 87 62 eb 02 00 00 00 e0 b0 62 eb 02 00 00 00  |..b.......b.....|
```



### Чому `Byte` — це `std::uint8_t`, а не `int`

Клітинка пам’яті `ember` має бути рівно одним байтом на кожній машині.
`std::uint8_t` гарантує розмір 8 біт і зберігає значення від 0 до 255.
Розмір `int` стандартом не фіксований: він може відрізнятися на різних
платформах і зазвичай займає більше ніж один байт. Тому `int` не підходить
для представлення однієї клітинки пам’яті.


### Stretch: `set16` і порядок байтів

```txt
ember> set16 0 0x1234
ember> dump
0000  34 12 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |4...............|
```

Число `0x1234` зберігається як `34 12`, тому програма використовує
порядок байтів little-endian: молодший байт записується першим.