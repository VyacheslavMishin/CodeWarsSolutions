def validate_battlefield(field):
    ships_amount = {4: 0, 3: 0, 2: 0, 1: 0}
    for raw in range(len(field) - 1):
        for column in range(len(field[0]) - 1):
            if (field[raw][column] == 1 and field[raw + 1][column + 1] == 1) or \
                    (field[raw][column + 1] == 1 and field[raw + 1][column] == 1):
                return False

    revealed_ship_length = 0
    for raw in range(len(field)):
        for column in range(len(field[0])):
            if field[raw][column] == 1:
                revealed_ship_length += 1
                for idx in range(raw + 1, len(field)):
                    if field[idx][column]:
                        revealed_ship_length += 1
                        field[idx][column] = "*"
                    else:
                        break
                for idx in range(column + 1, len(field[0])):
                    if field[raw][idx]:
                        revealed_ship_length += 1
                        field[raw][idx] = "*"
                    else:
                        break

                try:
                    ships_amount[revealed_ship_length] += 1
                except KeyError:
                    return False
                
                revealed_ship_length = 0

    for number in range(1, 5):
        if ships_amount[number] != 5 - number:
            return False

    return True
