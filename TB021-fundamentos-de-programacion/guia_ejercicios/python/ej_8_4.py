def generar_factura(lista_productos, lista_factura):
    '''
    Hay una lista ordenada de productos con tuplas (identificador,
    descripcion, precio) y una lista de factura con tuplas (identificador,
    cantidad). Generar una factura.
    '''
    total = 0
    ticket = [["Cantidad", "Descripcion", "Precio unitario", "Precio total"]]

    for producto in lista_productos:
        for factura in lista_factura:
            
            descripcion = producto[1]
            precio_unitario = producto[2]
            identificador = factura[0]
            cantidad = factura[1]
            total_producto = precio_unitario * cantidad

            if identificador == producto[0]:
                total += total_producto
                fila = [str(cantidad), descripcion, str(precio_unitario), str(total_producto)]
                ticket.append(fila)

    for fila in ticket:
        print("{: <20} {: <20} {: <20} {: <20}".format(*fila))
    print(f"La cantidad a pagar es {total}")

lista_productos = [
    (1234, 'Sopa', 58), 
    (1239, 'Nesquik', 88), 
    (2348, 'Queso', 23), 
    (3298, 'Agua', 15), 
    (3426, 'Galletitas', 89), 
    (3457, 'Fideos', 66), 
    (5462, 'Yerba', 44), 
    (5649, 'Vainillas', 78), 
    (7689, 'Leche', 66), 
    (9784, 'Sticker', 35)
    ]

lista_factura = [
    (1239, 8), 
    (2348, 3), 
    (3426, 9), 
    (5462, 4), 
    (5649, 8), 
    (9784, 5)
    ]

generar_factura(lista_productos, lista_factura)