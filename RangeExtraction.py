def solution(args):
    if len(args) == 0:
        return ""
    if len(args) == 1:
        return str(args[0])
    answer, first = "", args[0]
    for idx in range(len(args) - 1):
        if args[idx + 1] - args[idx] != 1:
            if args[idx] - first == 1:
                answer += str(first) + "," + str(args[idx]) + ","
                first = args[idx + 1]

            elif args[idx] == first:
                answer += str(first) + ","
                first = args[idx + 1]

            else:
                answer += str(first) + "-" + str(args[idx]) + ","
                first = args[idx + 1]

    if first == args[-1]:
        answer += str(args[-1])
    elif args[-1] - first == 1:
        answer += str(first) + "," + str(args[-1])
    else:
        answer += str(first) + "-" + str(args[-1])

    return answer
