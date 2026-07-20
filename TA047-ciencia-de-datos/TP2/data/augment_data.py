"""
Data augmentation using EDA (Easy Data Augmentation) for Spanish product reviews.
Techniques: synonym replacement, random swap, random deletion, random insertion.
Goal: balance label 1 (neutral, 10200) with labels 0 and 2 (20400 each),
      then add extra samples for all labels.

Reference: Wei & Zou, 2019 — "EDA: Easy Data Augmentation Techniques for
Boosting Performance on Text Classification Tasks"
"""
import csv
import random
import re
import string
from collections import defaultdict

import nltk
from nltk.corpus import wordnet as wn, stopwords

nltk.download("wordnet", quiet=True)
nltk.download("omw-1.4", quiet=True)
nltk.download("stopwords", quiet=True)

DATA_PATH = "data/train.csv"
OUTPUT_PATH = "data/train_augmented.csv"

GENERATE_COUNTS = {
    "0": 2000,   # 20400 → 22400
    "1": 12000,  # 10200 → 22200  (main balancing target)
    "2": 2000,   # 20400 → 22400
}

SPANISH_STOPWORDS = set(stopwords.words("spanish"))

# ── EDA primitives ────────────────────────────────────────────────────────────

def get_synonyms(word: str) -> list[str]:
    synonyms = set()
    for syn in wn.synsets(word, lang="spa"):
        for lemma in syn.lemmas("spa"):
            candidate = lemma.name().replace("_", " ")
            if candidate.lower() != word.lower():
                synonyms.add(candidate)
    return list(synonyms)


def synonym_replacement(words: list[str], n: int) -> list[str]:
    """Replace n random non-stopword words with a synonym."""
    eligible = [i for i, w in enumerate(words) if w.lower() not in SPANISH_STOPWORDS]
    random.shuffle(eligible)
    result = words[:]
    replaced = 0
    for idx in eligible:
        syns = get_synonyms(result[idx])
        if syns:
            result[idx] = random.choice(syns)
            replaced += 1
            if replaced >= n:
                break
    return result


def random_insertion(words: list[str], n: int) -> list[str]:
    """Insert n random synonyms at random positions."""
    result = words[:]
    for _ in range(n):
        eligible = [w for w in result if w.lower() not in SPANISH_STOPWORDS]
        if not eligible:
            break
        syns = get_synonyms(random.choice(eligible))
        if syns:
            result.insert(random.randint(0, len(result)), random.choice(syns))
    return result


def random_swap(words: list[str], n: int) -> list[str]:
    """Swap n random pairs of words."""
    result = words[:]
    for _ in range(n):
        if len(result) < 2:
            break
        i, j = random.sample(range(len(result)), 2)
        result[i], result[j] = result[j], result[i]
    return result


def random_deletion(words: list[str], p: float) -> list[str]:
    """Delete each word with probability p (keep at least one word)."""
    if len(words) == 1:
        return words[:]
    result = [w for w in words if random.random() > p]
    return result if result else [random.choice(words)]


# ── Augmentation orchestrator ─────────────────────────────────────────────────

def tokenize(text: str) -> list[str]:
    return text.split()


def detokenize(words: list[str]) -> str:
    return " ".join(words)


def eda(text: str, alpha_sr=0.1, alpha_ri=0.1, alpha_rs=0.1, p_rd=0.1) -> str:
    """Apply one random EDA operation and return the augmented text."""
    words = tokenize(text)
    n = max(1, int(len(words) * alpha_sr))

    op = random.choice(["sr", "ri", "rs", "rd"])
    if op == "sr":
        words = synonym_replacement(words, n)
    elif op == "ri":
        words = random_insertion(words, n)
    elif op == "rs":
        words = random_swap(words, max(1, int(len(words) * alpha_rs)))
    else:
        words = random_deletion(words, p_rd)

    return detokenize(words)


# ── Main ──────────────────────────────────────────────────────────────────────

def load_rows(path: str) -> tuple[list[dict], dict[str, list[str]]]:
    rows = []
    by_label: dict[str, list[str]] = defaultdict(list)
    with open(path) as f:
        for row in csv.DictReader(f):
            rows.append(row)
            by_label[row["label"]].append(row["text"])
    return rows, by_label


def main():
    random.seed(42)
    original_rows, by_label = load_rows(DATA_PATH)
    max_id = max(int(r["id"]) for r in original_rows)

    new_rows = []
    next_id = max_id + 1

    for label, total in GENERATE_COUNTS.items():
        source = by_label[label]
        print(f"\n=== Generating {total} augmented reviews for label {label} "
              f"(source pool: {len(source)}) ===")

        generated = []
        attempts = 0
        max_attempts = total * 5

        while len(generated) < total and attempts < max_attempts:
            text = random.choice(source)
            aug = eda(text)
            if aug != text and len(aug.strip()) > 5:
                generated.append(aug)
            attempts += 1

            if len(generated) % 500 == 0 and len(generated) > 0:
                print(f"  {len(generated)}/{total}")

        print(f"  Done: {len(generated)} reviews generated")
        for text in generated[:total]:
            new_rows.append({"id": next_id, "text": text, "label": label})
            next_id += 1

    all_rows = original_rows + new_rows
    with open(OUTPUT_PATH, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["id", "text", "label"])
        writer.writeheader()
        writer.writerows(all_rows)

    from collections import Counter
    dist = Counter(r["label"] for r in all_rows)
    print(f"\nWritten {len(all_rows)} rows to {OUTPUT_PATH}")
    print("Final distribution:", dict(sorted(dist.items())))

    # Print a few examples
    print("\n--- Sample augmented reviews (label 1) ---")
    for r in new_rows:
        if r["label"] == "1":
            print(f"  {r['text'][:120]}")
            break


if __name__ == "__main__":
    main()
