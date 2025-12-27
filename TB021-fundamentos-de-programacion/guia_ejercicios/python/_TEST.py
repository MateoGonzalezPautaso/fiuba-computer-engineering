def replicar(arr, n):
    if len(arr) == 0:
        return arr
    else:
        return [arr[0]] * n + replicar(arr[1:], n)