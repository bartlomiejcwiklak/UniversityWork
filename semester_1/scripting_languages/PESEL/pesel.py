PESEL_LENGTH = 11
PESEL_WEIGHT = (1, 3, 7, 9, 1, 3, 7, 9, 1, 3)


# Functions
def check_length(pesel): return len(pesel) == PESEL_LENGTH


def check_digits_only(pesel): return pesel.isdigit()


def check_birth_date(pesel):
    year = int(pesel[:2])
    month = int(pesel[2:4])
    day = int(pesel[4:6])

    if 1 <= month <= 12:
        year += 1900
    elif 21 <= month <= 32:
        year += 2000
        month -= 20
    elif 41 <= month <= 52:
        year += 2100
        month -= 40
    elif 61 <= month <= 72:
        year += 2200
        month -= 60
    elif 81 <= month <= 92:
        year += 1800
        month -= 80
    else:
        return False

    if month < 1 or month > 12:
        return False

    if day < 1:
        return False
    if month in {1, 3, 5, 7, 8, 10, 12} and day > 31:  # Months with 31 days
        return False
    if month in {4, 6, 9, 11} and day > 30:  # Months with 30 days
        return False
    if month == 2:  # February
        # Check if it is leap year
        is_leap = (year % 4 == 0 and (year % 100 != 0 or year % 400 == 0))
        if (is_leap and day > 29) or (not is_leap and day > 28):
            return False

    return True


def check_control_sum(pesel):
    # Calculate control sum
    control_sum = sum(int(pesel[i]) * PESEL_WEIGHT[i] for i in range(10))
    control_digit = (10 - (control_sum % 10)) % 10
    return control_digit == int(pesel[10])


def check_sex(pesel):
    if int(pesel[9]) % 2 == 0:
        return True  # Female
    else:
        return False  # Male


# Counters
total = correct = male = female = 0
invalid_length = invalid_digit = invalid_date = invalid_checksum = 0

# Main processing loop
file = open("1e6_2.dat", 'r')
for pesel in file:
    Pesel = pesel.strip()
    total += 1
    if check_length(Pesel) is False:
        invalid_length += 1
        continue
    if check_digits_only(Pesel) is False:
        invalid_digit += 1
        continue
    if check_birth_date(Pesel) is False:
        invalid_date += 1
        continue
    if check_control_sum(Pesel) is False:
        invalid_checksum += 1
        continue
    if check_sex(Pesel) is False:
        male += 1
    else:
        female += 1
    correct += 1

file.close()

# Show results
print(total, correct, female, male)
print(invalid_length, invalid_digit, invalid_date, invalid_checksum)
