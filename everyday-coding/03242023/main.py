import dis
import logging
import os
import pprint
import sys
import typing


logger = logging.getLogger(__name__)


def main() -> None:
  list_int = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  list_int = division_comprehension(list_int)

  os_attrs_dict = convert_os_attributes()

  # NOTE(impcuong): Testing lambda expressions.
  x = (lambda num: num ** 2)(3)
  is_even = lambda num: num % 2 and 'even' or 'odd'
  even_or_not = is_even(1 << 2)

  pprint.pprint(list_int, indent=2, stream=sys.stdout)
  pprint.pprint(os_attrs_dict, indent=2, stream=sys.stdout)
  pprint.pprint(x, indent=2, stream=sys.stdout)

  # NOTE(impcuong): Disassemble library `dis` using to convert ASM expressions into human-readable instructions.
  pprint.pprint(dis.dis(is_even), indent=2, stream=sys.stdout)
  pprint.pprint(even_or_not, indent=2, stream=sys.stdout)


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


# CMD: `python3 main.py`
if __name__ == "__main__":
  main()
  sys.exit(0)
