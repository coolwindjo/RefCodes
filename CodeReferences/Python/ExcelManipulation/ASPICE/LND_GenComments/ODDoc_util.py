import re


def remove_proceeding_space(str):
    new_str = str
    for i in range(0, len(str)):
        if new_str[0] == ' ':
            new_str = new_str[1:]
        else:
            break

    return new_str


def get_unit(str):
    unit_pattern = r"\sunit:(?P<unit>[a-zA-Z0-9_/]+)"
    unit_found = re.search(unit_pattern, str)
    if (unit_found is not None):
        unit = unit_found.groupdict()['unit']
        str = re.sub(unit_pattern, "", str)
        # print(unit)
    else:
        str = str
        unit = "n/a"

    ret=[]
    ret.append(str)
    ret.append(unit)
    return ret


def get_range(str):
    range_pattern = r"\srange:(?P<range>[()a-zA-Z0-9_/~.+-]+)"
    range_found = re.search(range_pattern, str)
    if (range_found is not None):
        val_range = range_found.groupdict()['range']
        str = re.sub(range_pattern, "", str)
        # print(val_range)
    else:
        str = str;
        val_range = "n/a"

    ret = []
    ret.append(str)
    ret.append(val_range)
    return ret
