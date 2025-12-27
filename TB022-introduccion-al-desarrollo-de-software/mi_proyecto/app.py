from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route("/")
def home():
    lista_nombres=["Mateo", "Valentino", "Nazarena"]
    return render_template("home.html", nombres=lista_nombres)

@app.route("/perfil")
def perfil():
    return render_template("whoami.html", nombre="Mateo")

if __name__ == "__main__":
    app.run("127.0.0.1", port="8080", debug=True)

#export FLASK_DEBUG=1