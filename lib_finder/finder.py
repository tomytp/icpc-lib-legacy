from pathlib import Path
import difflib
import sys
from typing import Optional, List, Tuple
import pyperclip

BASE_FOLDER = Path(__file__).parent.parent / 'typst' / 'src'

def find_best_matches(query: str, library_path: str, num_results: int = 3) -> List[Tuple[Path, float]]:
    matches = []
    
    for file in Path(library_path).rglob('*'):
        if file.is_file():
            ratio = difflib.SequenceMatcher(None, query.lower(), file.stem.lower()).ratio()
            matches.append((file, ratio))
            
    return sorted(matches, key=lambda x: x[1], reverse=True)[:num_results]

def copy_to_clipboard(text: str):
    pyperclip.copy(text)

def main():
    if len(sys.argv) < 2:
        print("Usage: script.py <query> [path]")
        sys.exit(1)

    query = sys.argv[1]
    path = sys.argv[2] if len(sys.argv) > 2 else str(BASE_FOLDER)
    matches = find_best_matches(query, path)
    
    if matches[0][1] > 0.9:
        copy_to_clipboard(Path(matches[0][0]).read_text())
        print(f"Copied {matches[0][0].relative_to(BASE_FOLDER)} (score: {matches[0][1]:.2f}) to clipboard")
    else:
        for file, score in matches:
            print(f"{file.relative_to(BASE_FOLDER)} (score: {int(score*100)})")

if __name__ == "__main__":
    main()