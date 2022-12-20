import subprocess
import unittest

class TestBasicIO(unittest.TestCase):
    def check_output(self, command: str, expected: str):
        result = subprocess.run(["./a.out", command], capture_output=True)
        self.assertEqual(expected, result.stdout.decode())

    def test_letter_h(self):
        command = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."
        self.check_output(command, "H")

    def test_basic_loop(self):
        command = "+++[-]"
        self.check_output(command, "")

    def test_intermediate_loop(self):
        command = "++++++[--]"
        self.check_output(command, "")

    def test_letter_h_loops(self):
        command = ">++++++++[<+++++++++>-]<."
        self.check_output(command, "H")


if __name__ == "__main__":
    unittest.main()