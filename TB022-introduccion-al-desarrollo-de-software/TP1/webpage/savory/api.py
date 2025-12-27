from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine, text
from sqlalchemy.exc import SQLAlchemyError
import json
from base64 import b64encode

app = Flask(__name__)

# Parametros de conexion
USUARIO = "root"
CONTRASEÑA = "codigofiuba"
HOST = "localhost"
DATABASE = "tp_ids"

# URI (Uniform Resource Identifier) para conectar con la databse
URI = f"mysql+mysqlconnector://{USUARIO}:{CONTRASEÑA}@{HOST}/{DATABASE}"

# Funcion para conectarse a la base de datos
engine = create_engine(URI)


@app.route('/listado_recetas', methods=['GET'])
def listado_recetas():
    '''
    Devuelve un JSON con los nombres de todas las recetas de la base de datos
    '''
    conn = engine.connect() # Creamos la conexión con la base de datos
    query = "SELECT nombre FROM recetas;" # Generamos la query para obtener los nombres de las recetas

    try:
        result = conn.execute(text(query)) # Usamos text para poder usar un string como query y que execute la interprete
        conn.close() #Cerramos la conexion con la base de datos

    except SQLAlchemyError as err: # Agarramos cualquier excepcion que SQLAlchemy pueda tener
        return jsonify(str(err.__cause__)), 500
    
    data = [] # Armamos una lista para agregar diccionarios con todos los datos

    for row in result: # Recorremos las lineas del resultado de la query
        data.append(row.nombre)

    return jsonify(data), 200 # Devolvemos la informacion obtenida


@app.route('/platos', methods = ['GET'])
def platos():
    '''
    Devuelve el nombre, descripcion e imagen de los platos para poder ser mostrados en el template del menu
    '''
    conn = engine.connect() # Creamos la conexión con la base de datos
    query = "SELECT nombre, descripcion, imagen FROM recetas;" # Generamos la query para obtener los nombres, descripciones e imagenes de las recetas

    try:
        result = conn.execute(text(query)) # Usamos text para poder usar un string como query y que execute la interprete
        conn.close() #Cerramos la conexion con la base de datos

    except SQLAlchemyError as err: # Agarramos cualquier excepcion que SQLAlchemy pueda tener
        return jsonify(str(err.__cause__)), 500
    
    data = [] # Armamos una lista para agregar diccionarios con todos los datos

    for row in result: # Recorremos las lineas del resultado de la query
        entity = {}
        entity['nombre'] = row.nombre
        entity['descripcion'] = row.descripcion
        entity['imagen'] = row.imagen
        data.append(entity)

    return jsonify(data), 200 # Devolvemos la informacion obtenida


@app.route('/ingredientes/<lista_platos>', methods = ['GET'])
def ingredientes(lista_platos):
    '''
    Devuelve los ingredientes de los platos para poder armar la lista de compra
    PRECONDICION: lista_platos es una tupla de nombres de comidas
    '''
    conn = engine.connect() # Creamos la conexión con la base de datos
    query = f"SELECT ingredientes FROM recetas WHERE nombre in {lista_platos};" # Generamos la query para obtener los ingredientes de las recetas

    try:
        result = conn.execute(text(query)) # Usamos text para poder usar un string como query y que execute la interprete
        conn.close() #Cerramos la conexion con la base de datos

    except SQLAlchemyError as err: # Agarramos cualquier excepcion que SQLAlchemy pueda tener
        return jsonify(str(err.__cause__)), 500
    
    data = [] # Armamos una lista para agregregar los diccionaros

    for row in result: # Recorremos las lineas del resultado de la query
        data.append(json.loads(row.ingredientes)) # Convierte row.ingredientes a un diccionario, sin esto queda como un str

    return jsonify(data), 200 # Devolvemos la informacion obtenida


@app.route('/login/<username>', methods = ['GET'])
def get_password(username):
    '''Devuelve la contraseña del usuario pasado por la ruta en formato de string.
    En caso de que el usuario no exista en la base de datos devuelve una cadena vacia'''
    conn = engine.connect()
    query = f"SELECT password FROM usuarios WHERE username = '{username}';"

    try:
        result = conn.execute(text(query)) # Usamos text para poder usar un string como query y que execute la interprete
        row = result.fetchone() # Obtenemos solo 1 fila, porque los usuarios son unicos en la database
        conn.close() #Cerramos la conexion con la base de datos

    except SQLAlchemyError as err: # Agarramos cualquier excepcion que SQLAlchemy pueda tener
        return jsonify(str(err.__cause__)), 500
    
    if not row:
        return jsonify(""), 200 # Si el usuario no existe, devuelve una cadena vacia

    else:
        return jsonify(row[0]), 200 # Devuelvo un json con el primer (y unico) elemento de la row que es la password ("password",)


@app.route('/cambiar_password/<usuario>', methods = ['PATCH'])
def cambiar_password(usuario):
    '''Permite cambiar la contraseña de un usuario'''
    conn = engine.connect()
    nuevos_datos = request.get_json() # Los nuevos datos de la contraseña se envian en el body de la request

    assigned_password = nuevos_datos["password"].encode() # Transformamos el string a bytes
    assigned_password_bytes = b64encode(assigned_password) # Ciframos la contraseña
    assigned_password = assigned_password_bytes.decode() # Convertimos los bytes a un string para poder ser agregado a la database

    query = f"""UPDATE usuarios 
    SET 
        password = '{assigned_password}'
    WHERE username = '{usuario}';
    """
    validation_query = f"SELECT * FROM usuarios WHERE username = '{usuario}';"
    
    try:
        val_result = conn.execute(text(validation_query))

        if val_result.rowcount!=0:
            result = conn.execute(text(query))
            conn.commit()
            conn.close()
        else:
            conn.close()
            return jsonify({'message': "el usuario no existe"}), 404
        
    except SQLAlchemyError as err:
        return jsonify({'message': str(err.__cause__)}), 500
    
    return jsonify({'message': 'se ha modificado correctamente' + query}), 200


@app.route('/borrar_usuario/<usuario>', methods = ['DELETE'])
def borrar_usuario(usuario):
    """
    Permite borrar un usuario de la base de datos, pero como este es una clave foranea primero
    debemos pasar sus recetas a un usuario main para que no tenga valores asociados
    """
    if usuario == "main":
        return jsonify({"message": "el usuario main no puede borrarse"}), 404

    conn = engine.connect()
    comida_usuario = f"SELECT nombre FROM recetas WHERE duenio = '{usuario}';"
    comidas = conn.execute(text(comida_usuario))
    
    for row in comidas:
        comida = row[0] # ("comida", )

        cambiar_usuario = f"""UPDATE recetas 
        SET 
            duenio = 'main'
        WHERE nombre = '{comida}';
        """

        cambio = conn.execute(text(cambiar_usuario))
        conn.commit()    

    erasement_query = f"DELETE FROM usuarios WHERE username = '{usuario}';" # query para borrar
    validation_query = f"SELECT * FROM usuarios WHERE username = '{usuario}';" # query para verificar que el usuario exista
    
    try:
        val_result = conn.execute(text(validation_query))

        if val_result.rowcount != 0 :
            result = conn.execute(text(erasement_query))
            conn.commit()
            conn.close()
        else:
            conn.close()
            return jsonify({"message": "el usuario no existe"}), 404
    
    except SQLAlchemyError as err:
        return jsonify({'message': 'Se ha producido un error' + str(err.__cause__)}), 500
    
    return jsonify({'message': 'se ha eliminado correctamente'}), 202


@app.route('/crear_receta', methods = ['POST'])
def crear_receta():
    """
    Crea una receta en la base de datos con lo que recibe del template de sugerencias
    """
    conn = engine.connect()
    receta = request.get_json()

    json_ingredientes = json.dumps(receta['ingredientes'])  # Se maneja automaticamante el formato JSON para espaciar caracteres especiales

    # Se crea la query en base a los datos pasados por el endpoint.
    # Los mismos deben viajar en el body en formato JSON raw
    query = f"""INSERT INTO recetas (nombre, ingredientes, duenio, descripcion, imagen) 
    VALUES ('{receta['nombre']}',
            '{json_ingredientes}',
            '{receta["duenio"]}',
            '{receta["descripcion"]}',
            '{receta["imagen"]}'
            );"""
    
    try:
        result = conn.execute(text(query))    # Se ejecuta la query
        conn.commit()   # Se aplica a la base de datos
        conn.close()      # Se cierra la conexion con la database

    except SQLAlchemyError as err:
        return jsonify({'message': 'Se ha producido un error' + str(err.__cause__)}), 500
    
    return jsonify({'message': 'se ha agregado correctamente' + query}), 201


@app.route('/borrar_receta/<nombre>', methods = ['DELETE'])
def borrar_receta(nombre):
    """
    Nos permite borrar una receta y todos los datos relacionados a ella
    """
    conn = engine.connect()
    query = f"DELETE FROM recetas WHERE nombre = '{nombre}';" # query para borrar
    validation_query = f"SELECT * FROM recetas WHERE nombre = '{nombre}';" # query para verificar que el plato exista
    
    try:
        val_result = conn.execute(text(validation_query))

        if val_result.rowcount != 0 :
            result = conn.execute(text(query))
            conn.commit()
            conn.close()
        else:
            conn.close()
            return jsonify({"message": "La receta no existe"}), 404
    
    except SQLAlchemyError as err:
        return jsonify({'message': 'Se ha producido un error' + str(err.__cause__)}), 500
    
    return jsonify({'message': 'se ha eliminado correctamente'}), 202


@app.route('/cambiar_receta/<nombre>', methods = ['PATCH'])
def cambiar_receta(nombre):
    '''Permite cambiar los ingredientes, la descripcion y la imagen de una receta'''
    conn = engine.connect()
    nuevos_datos = request.get_json() # Los nuevos datos de la receta se envian en el body de la request

    nuevo_json_ingredientes = json.dumps(nuevos_datos['ingredientes'])

    query = f"""UPDATE recetas 
    SET 
        imagen = '{nuevos_datos['imagen']}',
        descripcion = '{nuevos_datos['descripcion']}',
        ingredientes = '{nuevo_json_ingredientes}'
    WHERE nombre = '{nombre}';
    """
    validation_query = f"SELECT * FROM recetas WHERE nombre = '{nombre}';"

    try:
        val_result = conn.execute(text(validation_query))

        if val_result.rowcount!=0:
            result = conn.execute(text(query))
            conn.commit()
            conn.close()
        else:
            conn.close()
            return jsonify({'message': "la receta no existe"}), 404
        
    except SQLAlchemyError as err:
        return jsonify({'message': str(err.__cause__)}), 500
    
    return jsonify({'message': 'se ha modificado correctamente' + query}), 200


if __name__ == "__main__":
    app.run("127.0.0.1", port="5000", debug=True)