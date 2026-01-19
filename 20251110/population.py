# generate_random.py
# Writes 5000 random integers < 1000 to the specified file (one per line)

import random
from pathlib import Path

OUT = Path(r"C:\Users\Titus Ticusan\Desktop\Coding\Facultate\20251110\input.in")
OUT.parent.mkdir(parents=True, exist_ok=True)

with OUT.open("w", encoding="utf-8") as f:
    for _ in range(5000):
        f.write(f"{random.randrange(1000)}\n")