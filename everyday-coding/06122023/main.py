import sys
import typing


class TestDict(object):
    def __init__(self, age: typing.Union[str, int]):
        self.author = "Some-unknown-dude"
        self.age = age


# Variance arguments versus keywords arguments demystification:
def explore_args_(*args):
    for arg in args:
        print(arg, end="\n")


# `kwargs`: An arguments list with their precendence named key.
def explore_kwargs_(**kwargs):
    if not isinstance(kwargs, dict):
        print(f"{kwargs.__class__}")
    for k, v in kwargs.items():
        print(f"{k}: {v}", end="\n")


if __name__ == "__main__":
    explore_args_("My", "name", "is...")

    sample_dict: typing.Dict[str, int] = {}
    sample_dict["one"] = 1
    sample_dict["two"] = 2
    sample_dict["three"] = 3
    dict_based = isinstance(sample_dict, dict)
    print(f"{sample_dict.__class__}: {dict_based}", end="\n")
    print(repr(sample_dict), dir(__builtins__), end="\n")

    ageless = TestDict("unknown")
    print(ageless.__dict__)
    print(vars(ageless))
    aged = TestDict(120)
    print(aged.__dict__)
    print(vars(aged))

    explore_kwargs_(one=1, two=2, three=3)
    explore_kwargs_(four=["failover"])

    sys.exit(0)
