"""
Data augmentation using Groq (free tier) to generate synthetic Spanish product reviews.
Model: llama-3.1-8b-instant

Usage:
    GROQ_API_KEY=gsk_... python3 data/augment_data_llm.py

Goal: match train_augmented_eda_balanced.csv distribution:
    Label 0 (negative): 20400 → 22400  (+2000)
    Label 1 (neutral):  10200 → 22200  (+12000)
    Label 2 (positive): 20400 → 22400  (+2000)
"""
import csv
import os
import random
import re
import time
from collections import Counter, defaultdict

from groq import Groq, AuthenticationError, RateLimitError

DATA_PATH = "data/train.csv"
OUTPUT_PATH = "data/train_augmented_llm_balanced.csv"
MODEL = "llama-3.1-8b-instant"
BATCH_SIZE = 25

GENERATE_COUNTS = {
    "0": 2000,
    "1": 12000,
    "2": 2000,
}

LABEL_DESCRIPTIONS = {
    "0": "NEGATIVA — el cliente está insatisfecho: el producto llegó dañado, tardó mucho, no funciona, mala calidad, no cumplió expectativas, problemas con el vendedor, etc.",
    "1": "NEUTRAL — opinión mixta: algo bueno y algo malo, o descripción sin entusiasmo ni rechazo marcado, por ejemplo menciona la calidad aceptable pero la entrega tardó, o viceversa.",
    "2": "POSITIVA — el cliente está satisfecho: buen producto, lo recomendaría, cumplió o superó expectativas, buena relación calidad-precio, entrega rápida, repetirá la compra, etc.",
}


def load_data(path: str) -> tuple[list[dict], dict[str, list[str]]]:
    rows = []
    by_label: dict[str, list[str]] = defaultdict(list)
    with open(path, encoding="utf-8") as f:
        for row in csv.DictReader(f):
            rows.append(row)
            by_label[row["label"]].append(row["text"])
    return rows, by_label


def generate_batch(client: Groq, label: str, examples: list[str], batch_size: int) -> list[str]:
    example_block = "\n".join(f"- {e}" for e in random.sample(examples, min(8, len(examples))))

    prompt = f"""Eres un generador de reseñas de productos en español para Amazon España.

Genera exactamente {batch_size} reseñas NUEVAS con sentimiento {LABEL_DESCRIPTIONS[label]}

Ejemplos reales del dataset (solo como referencia de estilo y vocabulario, NO los copies):
{example_block}

Reglas:
- Cada reseña en una línea separada, sin numeración ni prefijos
- Varía productos: electrónica, ropa, hogar, cocina, deportes, libros, juguetes, etc.
- Varía longitud: entre 1 y 4 oraciones
- Usa lenguaje natural con errores ocasionales como escribiría un usuario real
- Devuelve SOLO las {batch_size} reseñas, nada más"""

    response = client.chat.completions.create(
        model=MODEL,
        messages=[{"role": "user", "content": prompt}],
        max_tokens=3000,
        temperature=0.9,
    )

    text = response.choices[0].message.content.strip()
    lines = [l.strip() for l in text.split("\n") if l.strip()]
    cleaned = [re.sub(r"^\d+[\.\)\-]\s*", "", l) for l in lines]
    return [l for l in cleaned if len(l) > 10][:batch_size]


def main():
    api_key = os.environ.get("GROQ_API_KEY")
    if not api_key:
        print("Error: set GROQ_API_KEY before running.")
        print("  export GROQ_API_KEY=gsk_...")
        raise SystemExit(1)

    client = Groq(api_key=api_key)
    random.seed(42)

    original_rows, by_label = load_data(DATA_PATH)
    max_id = max(int(r["id"]) for r in original_rows)
    next_id = max_id + 1
    new_rows = []

    for label, total in GENERATE_COUNTS.items():
        source = by_label[label]
        print(f"\n=== Generating {total} reviews for label {label} ===")
        generated = []

        while len(generated) < total:
            remaining = total - len(generated)
            batch_size = min(BATCH_SIZE, remaining)
            try:
                batch = generate_batch(client, label, source, batch_size)
                generated.extend(batch)
                print(f"  [{len(generated)}/{total}]")
                time.sleep(0.3)
            except AuthenticationError:
                print("Auth error: check your GROQ_API_KEY.")
                raise SystemExit(1)
            except RateLimitError:
                print("  Rate limit hit, waiting 60s...")
                time.sleep(60)
            except Exception as e:
                print(f"  Error: {e}, retrying in 10s...")
                time.sleep(10)

        for text in generated[:total]:
            new_rows.append({"id": next_id, "text": text, "label": label})
            next_id += 1

    all_rows = original_rows + new_rows
    with open(OUTPUT_PATH, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["id", "text", "label"])
        writer.writeheader()
        writer.writerows(all_rows)

    dist = Counter(r["label"] for r in all_rows)
    print(f"\nDone! Written {len(all_rows)} rows to {OUTPUT_PATH}")
    print("Final distribution:", dict(sorted(dist.items())))

    print("\n--- Sample generated reviews ---")
    for r in new_rows[:3]:
        print(f"  [{r['label']}] {r['text'][:120]}")


if __name__ == "__main__":
    main()
