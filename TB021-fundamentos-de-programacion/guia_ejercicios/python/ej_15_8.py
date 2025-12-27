def obtener_mayor_elemento(arr):
    if len(arr) == 1:
        return arr[0]
    
    if arr[0] >= arr[1]:
        arr.pop(1)
        return obtener_mayor_elemento(arr)
    
    elif arr[0] < arr[1]:
        arr.pop(0)
        return obtener_mayor_elemento(arr)