from collections import defaultdict


def is_palindrom(string: str) -> bool:
    size = len(string)
    for i in range(size):
        if string[i] != string[-(1 + i)]:
            return False
    return True


def get_palindrom_dict(string: str) -> dict:
    palindrom = defaultdict(list)
    size = len(string)
    for i in range(size):
        for j in range(size - i):
            mini_str = string[j: j + i + 1]
            if is_palindrom(mini_str):
                palindrom[i + 1] += [mini_str]
    return palindrom


def check_match(string: str) -> bool:
    if len(string) == 0:
        return True
    even_str = string[0::2]
    add_str = string[1::2]
    if len(even_str) != len(add_str):
        return False
    dict_match_even_key = {}
    for i in range(len(add_str)):
        if even_str[i] not in dict_match_even_key.keys():
            dict_match_even_key[even_str[i]] = add_str[i]
            continue
        else:
            if dict_match_even_key[even_str[i]] == add_str[i]:
                continue
            else:
                return False
    return True
