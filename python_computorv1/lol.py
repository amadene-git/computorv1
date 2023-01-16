def approx(num, root, n_dec = 10):
    nat_num = 1
    while nat_num**root <= num:
        result = nat_num
        nat_num += 1

    for d in range(1, n_dec+1):
        increment = 10**-d
        count = 1
        before = result

        while (before + increment*count)**root <= num:
            result = before + increment*count
            count += 1
    return result




(− 83571739875 − 3 * √865929162323512275105)/247621636