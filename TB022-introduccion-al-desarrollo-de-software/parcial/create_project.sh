#!/bin/bash

#Para ejecutar source ../create_project.sh test
mkdir $1 # Recibe el nombre del proyecto pasado por parametro
cd $1

touch app.py
echo 'from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

if __name__ == "__main__":
    app.run("127.0.0.1", port="8080", debug=True)

#export FLASK_DEBUG=1' > app.py

mkdir .venv

pipenv install flask

mkdir templates
mkdir static
cd static
mkdir images
mkdir css
mkdir js
cd ..
ls


# POSIBLE IDEA cp init_project a la carpeta $1

# init
#pipenv shell
#VER SI AGREGAR ESTO
#export FLASK_DEBUG=1

#flask run
# python3 app.py PREFIERO ESTA
#flask --app app.py --debug run
