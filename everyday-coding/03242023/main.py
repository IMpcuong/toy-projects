import dis
import logging
import os
import pathlib
import pprint
import sys
import typing


logger = logging.getLogger(__name__)


def main() -> None:
    list_int = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    list_int = division_comprehension(list_int)

    os_attrs_dict = convert_os_attributes()

    # NOTE(impcuong): Testing lambda expressions.
    x = (lambda num: num**2)(3)
    is_even = lambda num: num % 2 and "even" or "odd"
    even_or_not = is_even(1 << 2)

    pprint.pprint(list_int, indent=2, stream=sys.stdout)
    pprint.pprint(os_attrs_dict, indent=2, stream=sys.stdout)
    pprint.pprint(x, indent=2, stream=sys.stdout)

    # NOTE(impcuong): Disassemble library `dis` using to convert ASM expressions into human-readable instructions.
    pprint.pprint(dis.dis(is_even), indent=2, stream=sys.stdout)
    pprint.pprint(even_or_not, indent=2, stream=sys.stdout)

    butcher = Executioner(None, "**/*", {})
    butcher.print_paths()
    butcher.print_paths_class()
    Executioner.print_paths_class()
    butcher.print_paths_static("Welcome to the hotel hell!")


def division_comprehension(list_int: typing.List[int]) -> typing.List[int]:
    list_int = [v for i, v in enumerate(list_int) if v % 2 or v % 4 == 0]
    return list_int


def convert_os_attributes() -> typing.Dict[str, str]:
    result = {}
    env_dict = os.environ.copy()
    # NOTE(impcuong): https://stackoverflow.com/questions/152580/whats-the-canonical-way-to-check-for-type-in-python
    if not isinstance(env_dict, dict):
        env_dict = dict(env_dict)

    for attr in env_dict:
        value = env_dict[attr] or env_dict.get(attr)
        result[attr] = value
    return result


class Executioner(object):
    # Global fields/attributes:
    pid = 0
    paths = []

    def __init__(
        self,
        pid: int,
        lookup_path_pattern: str,
        paths: typing.Dict[str, typing.List[pathlib.Path]],
    ) -> None:
        if pid is None:
            pid = os.getpid()
        self.pid = pid

        cur_dir_path = "."
        if not lookup_path_pattern:
            self.lookup_path_pattern = cur_dir_path

        parent_dir_path = "../.."
        glob = "*"
        list_dirs_lookup = []
        if lookup_path_pattern.__contains__(glob):
            list_dirs_lookup = sorted(
                pathlib.Path(parent_dir_path).rglob(lookup_path_pattern)
            )

        if not paths:
            for dir_path in list_dirs_lookup:
                # NOTE(impcuong): Bypass the `.git` directory.
                if dir_path.is_file() or str(dir_path).__contains__(".git"):
                    continue
                dirs = [d for d in dir_path.iterdir() if d.is_dir()]
                for cur_dir in dirs:
                    paths[cur_dir.resolve()] = [
                        p for p in cur_dir.iterdir() if p.is_file()
                    ]
        self.paths = paths

    def __eq__(self, __other: object) -> bool:
        return len(self.paths) == len(__other.paths)

    # NOTE: https://stackoverflow.com/a/1669524/12535617
    def print_paths(self) -> None:
        # NOTE(impcuong): `self.paths` == `Executioner(...).paths`.
        pprint.pprint(f"{vars(self)}, {self}")

    @classmethod
    def print_paths_class(cls) -> None:
        # NOTE(impcuong): `cls.paths` == `Executioner.paths`.
        #     With classmethods, the class of the object instance is implicitly passed
        #     as the first argument instead of self.
        pprint.pprint(f"{cls}, {cls.paths}")

    @staticmethod
    def print_paths_static(greeting: str) -> None:
        # NOTE(impcuong): With staticmethods, neither self (the object instance) nor cls (the class)
        #     is implicitly passed as the first argument. They behave like plain functions
        #     except that you can call them from an instance or the class.
        pprint.pprint(f"{greeting}")


# CMD: `python3 main.py`
if __name__ == "__main__":
    main()
    sys.exit(0)
