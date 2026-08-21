import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
EXPECTED_COUNTS = {"board-1": 22, "board-2": 21}


class SourceContractTests(unittest.TestCase):
    def test_board_source_sets_and_local_include_closure(self):
        for board, expected_count in EXPECTED_COUNTS.items():
            root = ROOT / "firmware" / board
            support = root / "support"
            sources = sorted(path for path in root.rglob("*") if path.suffix in {".c", ".h"})
            self.assertEqual(expected_count, len(sources), board)
            missing = []
            for path in sources:
                text = path.read_text(encoding="utf-8")
                for include in re.findall(r'^\s*#include\s+"([^"]+)"', text, re.MULTILINE):
                    if include.startswith("ec") and not (support / include).is_file() and not (path.parent / include).is_file():
                        missing.append(f"{path.relative_to(ROOT)} -> {include}")
            self.assertEqual([], missing, board)

    def test_support_comments_do_not_expose_student_name(self):
        hits = []
        for path in (ROOT / "firmware").rglob("*"):
            if path.suffix in {".c", ".h"} and re.search(r"Junhyeok(?:_|\s+)Bang", path.read_text(encoding="utf-8"), re.I):
                hits.append(str(path.relative_to(ROOT)))
        self.assertEqual([], hits)

    def test_headers_have_no_markdown_bracketed_function_declarations(self):
        hits = []
        for path in (ROOT / "firmware").rglob("*.h"):
            if re.search(r"\b(?:void|int|float|double|char|uint\w*)\s+\[[A-Za-z_]\w*\]\s*\(", path.read_text(encoding="utf-8")):
                hits.append(str(path.relative_to(ROOT)))
        self.assertEqual([], hits)

    def test_known_student_ids_are_absent(self):
        text = "\n".join(path.read_text(encoding="utf-8") for path in ROOT.rglob("*") if path.suffix in {".c", ".h", ".md"})
        self.assertNotIn("2180" + "0275", text)
        self.assertNotIn("2210" + "0333", text)


if __name__ == "__main__":
    unittest.main()
