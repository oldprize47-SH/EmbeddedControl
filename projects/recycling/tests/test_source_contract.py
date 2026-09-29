import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
REPO = ROOT.parents[1]
SHARED = REPO / "lib"
EXPECTED_COUNTS = {"board-1": 22, "board-2": 21}
BOARD2_SUPPORT = (
    "ecADC2.h ecEXTI2.h ecGPIO2.c ecGPIO2.h ecICAP2.c ecICAP2.h "
    "ecPWM2.c ecPWM2.h ecPinNames.c ecPinNames.h ecRCC2.c ecRCC2.h "
    "ecSTM32F4v2.h ecStepper2.h ecSysTick2.c ecSysTick2.h "
    "ecTIM2.c ecTIM2.h ecUART2.c ecUART2.h"
).split()


def board_sources(board):
    if board == "board-1":
        return sorted((ROOT / "firmware" / board).rglob("*.[ch]"))
    return [ROOT / "firmware/board-2/app/main.c"] + [SHARED / name for name in BOARD2_SUPPORT]


class SourceContractTests(unittest.TestCase):
    def test_board_source_sets_and_local_include_closure(self):
        for board, expected_count in EXPECTED_COUNTS.items():
            root = ROOT / "firmware" / board
            support = root / "support" if board == "board-1" else SHARED
            sources = board_sources(board)
            self.assertEqual(expected_count, len(sources), board)
            missing = []
            for path in sources:
                text = path.read_text(encoding="utf-8")
                for include in re.findall(r'^\s*#include\s+"([^"]+)"', text, re.MULTILINE):
                    if include.startswith("ec") and not (support / include).is_file() and not (path.parent / include).is_file():
                        missing.append(f"{path.relative_to(REPO)} -> {include}")
            self.assertEqual([], missing, board)

    def test_support_comments_do_not_expose_student_name(self):
        hits = []
        for path in board_sources("board-1") + board_sources("board-2"):
            if path.suffix in {".c", ".h"} and re.search(r"Junhyeok(?:_|\s+)Bang", path.read_text(encoding="utf-8"), re.I):
                hits.append(str(path.relative_to(REPO)))
        self.assertEqual([], hits)

    def test_headers_have_no_markdown_bracketed_function_declarations(self):
        hits = []
        for path in board_sources("board-1") + board_sources("board-2"):
            if path.suffix != ".h":
                continue
            if re.search(r"\b(?:void|int|float|double|char|uint\w*)\s+\[[A-Za-z_]\w*\]\s*\(", path.read_text(encoding="utf-8")):
                hits.append(str(path.relative_to(REPO)))
        self.assertEqual([], hits)

    def test_only_one_maintained_recycling_application_and_board2_support(self):
        self.assertFalse((REPO / "LAB/final_first_board.c").exists())
        self.assertFalse((REPO / "LAB/final_second_board.c").exists())
        self.assertFalse((ROOT / "firmware/board-2/support").exists())
        for name in BOARD2_SUPPORT:
            self.assertTrue((SHARED / name).is_file(), name)

    def test_shared_support_keeps_sanitized_comments(self):
        for name in BOARD2_SUPPORT:
            text = (SHARED / name).read_text(encoding="utf-8")
            self.assertNotIn("2180" + "0275", text, name)
            self.assertNotIn("2210" + "0333", text, name)

    def test_known_student_ids_are_absent(self):
        text = "\n".join(path.read_text(encoding="utf-8") for path in ROOT.rglob("*") if path.suffix in {".c", ".h", ".md"})
        self.assertNotIn("2180" + "0275", text)
        self.assertNotIn("2210" + "0333", text)


if __name__ == "__main__":
    unittest.main()
