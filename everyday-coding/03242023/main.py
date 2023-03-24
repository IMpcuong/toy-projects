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

  pprint.pprint(list_int, indent=2, stream=sys.stdout)
  pprint.pprint(os_attrs_dict, indent=2, stream=sys.stdout)


def division_comprehension(list_int: typing.List[int]) -> typing.List[int]:
  list_int = [v for i, v in enumerate(list_int) if v % 2 or v % 4 == 0]
  return list_int


def convert_os_attributes() -> typing.Dict[str, str]:
  result = {}
  env_dict = os.environ.copy()
  if not isinstance(env_dict, dict):
    env_dict = dict(env_dict)

  for attr in env_dict:
    value = env_dict[attr] or env_dict.get(attr)
    result[attr] = value
  return result


# CMD: `python main.py`
if __name__ == "__main__":
  main()
  sys.exit(0)
