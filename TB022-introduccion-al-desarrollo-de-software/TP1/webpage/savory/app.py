from flask import Flask, request, render_template, redirect, url_for, send_from_directory, session
import requests
import os
from base64 import b64decode

app = Flask(__name__)
app.secret_key = os.urandom(15) # La secret_key es necesaria para validar sesiones de usuarios


def cant_ingredientes(list_dicc):
    """
    Funcion para sumar los ingredientes de multiples recetas y poder generar la lista de compra
    """
    res = {} 

    for dicc in list_dicc:
        for ingrediente, cantidad in dicc.items():
            numero, unidad = cantidad.split()
            numero = int(numero)

            if ingrediente not in res:
                res[ingrediente] = [numero, unidad]
            else:
                res[ingrediente][0] += numero

    for ingrediente in res:
        numero, unidad = res[ingrediente]
        res[ingrediente] = f"{numero} {unidad}"

    return res


@app.route('/')
def index():
    return render_template('index.html')


@app.route("/favicon.ico")
def favicon():
	return send_from_directory(os.path.join(app.root_path, 'static'),'favicon.ico',mimetype='image/vnd.microsof.icon')


@app.route('/menu')
def menu():
    """
    Template de la galeria de fotos con nombre y descripcion de los platos
    """
    api_url = f'http://127.0.0.1:5000/platos' # endpoint platos de la api
    response = requests.get(api_url)
    lista_platos = response.json() # Nombre, descripcion e imagen de los platos de la database

    return render_template('menu.html', platosjson=lista_platos)


@app.route("/seleccion", methods=["GET", "POST"])
def seleccion():
    """
    Template de checkboxes de recetas para seleccionar y luego redirigir al listado de compra
    """
    api_url_nombres = 'http://127.0.0.1:5000/listado_recetas' # endpoint listado_recetas
    response = requests.get(api_url_nombres)       
    lista_recetas = response.json() # Nombre de los platos de la database

    if request.method == "POST":
        recetas_elegidas = tuple(request.form.getlist("recetas")) # Recibe las recetas seleccionadas en los checkbox
        api_url_ingredientes = f'http://127.0.0.1:5000/ingredientes/{recetas_elegidas}' # endpoint ingredientes
        response = requests.get(api_url_ingredientes)
        
        json_ingredientes_desarmado = response.json() # Nombre e ingredientes de los platos de la database
        json_ingredientes_ordenado = cant_ingredientes(json_ingredientes_desarmado) # Ordena las cantidades y unidades del diccionario de ingredientes

        return render_template("lista_compra.html",dicc = json_ingredientes_ordenado)
    
    return render_template("lista_recetas.html", lista_recetas=lista_recetas)


@app.route('/login', methods = ['GET','POST'])
def login():
    """
    Template de login para validar usuarios y luego redireccionar al template de sugerencias
    """
    if request.method == 'POST':
        username_form = request.form.get('username_form')
        password_form = request.form.get('password_form')

        # Realiza la solicitud a la API de backend
        api_url = f'http://127.0.0.1:5000/login/{username_form}' # endpoint get_password
        response = requests.get(api_url)
        response_str = response.json()  # Contraseña asignada al usuario en la database

        assigned_password_bytes = b64decode(response_str) # Decodificacion a bytes
        assigned_password = assigned_password_bytes.decode("utf-8") # Casteo de bytes a str

        if password_form == assigned_password:
            session['auth'] = True # Autentica la sesion del usuario
            session['user'] = username_form # Asigna el username autenticado en la sesion
            
            return redirect(url_for('suggest'))

    return render_template('login.html')


@app.route('/suggest', methods=["GET","POST"])
def suggest():
    """
    Template de sugerencias de recetas
    """
    if not session.get('auth'):
        return redirect(url_for('login'))

    if request.method == "POST":         #Si es metodo post(ya se completo el primer form), guarda la cantidad de campos a usar
        cantidad = int(request.form.get("numIngredientes"))
        nombre = request.form.get("namePlato")      #Estos 2 datos tienen que ser enviados a la api pra meterlos en la BBDD
        descripcion = request.form.get("descPlato")

        return redirect(url_for('suggest_ingredientes', cantidad=cantidad, nombre=nombre, descripcion=descripcion))    #Redirecciona a el forms de ingredientes, pasando la cantidad de camposcl

    return render_template("form_receta.html", username=session.get('user'))


@app.route('/suggest/ingredientes', methods=["GET","POST"])
def suggest_ingredientes():
    """
    Recibe la informacion de la sugerencia para subirlo a la database y redirecciona a un template aceptado
    """
    if not session.get('auth'):
        return redirect(url_for('login'))

    cantidad = int(request.args.get('cantidad'))   #Recibe cantidad como argumento
    nombre = str(request.args.get('nombre'))
    descripcion = str(request.args.get('descripcion'))

    duenio = session.get('user')

    if request.method == "POST":
        dict_ingredientes = {}   #Crea el diccionario para que puedas ser jsonificado

        for i in range(cantidad):
            ingrediente = request.form.get(f"producto{i}")
            cant = request.form.get(f"cantidad{i}")   #Ingresa los datos en el dict
            tipo = request.form.get(f"tipo{i}")
            valor = f"{cant} {tipo}"
            dict_ingredientes[ingrediente] = valor

        link_imagen = request.form.get("link_imagen")

        body = {
            'nombre': nombre,
            'ingredientes': dict_ingredientes,
            'duenio': duenio,
            'descripcion': descripcion,
            'imagen': link_imagen
        }

        # Realiza la solicitud a la API de backend
        api_url = f'http://127.0.0.1:5000/crear_receta' # endpoint crear_receta
        response = requests.post(api_url, json = body)

        return render_template("aceptado.html")

    return render_template('form_ingredientes.html',cantidad=cantidad, nombre=nombre, descripcion=descripcion)


@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404


@app.errorhandler(500)
def internal_server_error(e):
    return render_template('500.html'), 500


if __name__ == "__main__":
    app.run("127.0.0.1", port="8080", debug=True)