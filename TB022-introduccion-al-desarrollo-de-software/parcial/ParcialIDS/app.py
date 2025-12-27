from flask import Flask, render_template, request, url_for

app = Flask(__name__)

@app.route("/")
def Home():
    nombre = "Mateo"
    apellido = "Gonzalez Pautaso"
    return render_template("home.html", nombre=nombre, apellido=apellido)

@app.route("/datos_personales", methods = ["GET", "POST"])
def Formulario():
    if request.method == "POST":
        nombre = request.form.get("fnombre")
        apellido = request.form.get("fapellido")
        celular = request.form.get("fcelular")
        direccion = request.form.get("fdirec")
        dni = request.form.get("fdni")

        lista=[nombre, apellido, celular, direccion, dni]

        return render_template("aceptado.html", lista=lista)
    
    return render_template("formulario.html")

if __name__ == "__main__":
    app.run("127.0.0.1", port="8080", debug=True)
