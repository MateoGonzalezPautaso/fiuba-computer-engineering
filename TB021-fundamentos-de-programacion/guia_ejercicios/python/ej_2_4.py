import ej_2_3

def main():
    for far in range (0, 121, 10):
        cel = ej_2_3.far_to_cel(far)
        print(f"{far} °F = {cel} °C")

main()