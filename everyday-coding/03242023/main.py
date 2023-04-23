import concurrent.futures
import dis
import logging
import os
import pathlib
import pprint
import requests as rq
import sys
import typing
import urllib.request


logger = logging.getLogger(__name__)


URLS: typing.List[str] = [
    "https://www.foxnews.com/",
    "https://www.cnn.com/",
    "https://europe.wsj.com/",
    "https://www.bbc.co.uk/",
]


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

    cmd = ["curl", "-sSL"]
    Executioner.request_domain(cmd, URLS)
    # https://docs.python.org/3/library/concurrent.futures.html?highlight=concurrent%20futures%20threadpoolexecutor#concurrent.futures.ThreadPoolExecutor
    Executioner.request_stress_test(5, URLS)


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
    pid: int = 0
    paths: typing.Dict[str, str] = {}

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
        list_dirs_lookup: typing.List[pathlib.Path] = []
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

    def request_response(rq: rq.Response) -> None:
        if (rq.status_code >= 400) and (rq.status_code <= 550):
            print("Failed with status code:", rq.status_code)
        print("Successful with status code:", rq.status_code)

    @classmethod
    def request_domain(
        cls, commands: typing.List[str], urls: typing.List[str]
    ) -> typing.List[rq.Request]:
        list_rq: typing.List[rq.Request] = []
        if urls[0] and not urls[0].isspace():
            for url in urls:
                r = rq.request("GET", url, headers={}, data="")
                cls.request_response(r)
                list_rq.append(r)
        else:
            pprint.pprint(f">> {isinstance(cls.paths, typing.List)}")
            cls.paths["gg"] = "https://google.com"
            cls.paths["cmd"] = "".join(map(lambda opt: opt.upper(), commands[1:]))
            pprint.pprint(f'>> {cls.paths.get("cmd")}')
            r = rq.request("GET", cls.paths.get("gg"), headers={}, data="")
            cls.request_response(r)
            list_rq.append(r)
        return list_rq

    @classmethod
    def load_url(cls, url: str, timeout: int) -> typing.Any:
        with urllib.request.urlopen(url, timeout=timeout) as conn:
            return conn.read()

    @classmethod
    def request_stress_test(
        cls,
        max_threads: int,
        urls: typing.List[str],
    ) -> None:
        with concurrent.futures.ThreadPoolExecutor(max_threads) as executor:
            future_to_url = {
                executor.submit(cls.load_url, url, 60): url
                for url in urls.extend([cls.paths.get("gg")])
            }
            pprint.pprint(future_to_url)
            pprint.pprint(isinstance(future_to_url, typing.Iterator))
            for f in concurrent.futures.as_completed(future_to_url):
                url = future_to_url[f]
                try:
                    data = f.result()
                except Exception as expt:
                    print("%r generated an exception: %s" % (url, expt))
                else:
                    print("%r page is %d bytes" % (url, len(data)))

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
