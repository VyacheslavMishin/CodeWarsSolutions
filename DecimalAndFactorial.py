def dec_2_fact_string(nb):
    dct_encrypt = {0: "0", 1: "1", 2: "2", 3: "3", 4: "4", 5: "5", 6: "6", 7: "7", 8: "8", 9: "9", 10: "A", 11: "B",
                   12: "C", 13: "D", 14: "E", 15: "F", 16: "G", 17: "H", 18: "I", 19: "J", 20: "K", 21: "L", 22: "M",
                   23: "N", 24: "O", 25: "P", 26: "Q", 27: "R", 28: "S", 29: "T", 30: "U", 31: "V", 32: "W", 33: "X",
                   34: "Y", 35: "Z"}

    curr_divisor, remainders = 2, ""
    while nb != 0:
        remainders = dct_encrypt[nb % curr_divisor] + remainders
        nb //= curr_divisor
        curr_divisor += 1

    return remainders + "0"


def fact_string_2_dec(string):
    dct_decrypt = {"0": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9, "A": 10, "B": 11,
                   "C": 12, "D": 13, "E": 14, "F": 15, "G": 16, "H": 17, "I": 18, "J": 19, "K": 20, "L": 21, "M": 22,
                   "N": 23, "O": 24, "P": 25, "Q": 26, "R": 27, "S": 28, "T": 29, "U": 30, "V": 31, "W": 32, "X": 33,
                   "Y": 34, "Z": 35}
    answer, factorial = 0, 1

    for idx in range(2, len(string) + 1):
        factorial *= (idx - 1)
        answer += factorial * dct_decrypt[string[-idx]]

    return answer
