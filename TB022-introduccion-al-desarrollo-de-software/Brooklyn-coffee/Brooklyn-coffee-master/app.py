from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route("/")
def home():
    nombre = request.args.get('nombre')
    # URL = http://127.0.0.1:5001/?nombre=Mateo
    if nombre:
        return render_template('index.html', user=nombre)
    
    else:
        return render_template('index.html', user="Usuario")

'''
@app.route("/contact", methods = ["GET", "POST"])
def contact():
    if request.method == "POST":
        name = request.form.get("name")

        return redirect(url_for("show", name=name))

    return render_template('contact.html')

@app.route('/show_data/<nombre>')
def show(name):
    return render_template('show_data.html', nombre=name)
'''


@app.route("/about")
def about():
    return render_template('about.html')

@app.route("/contact", methods = ["GET", "POST"])
def contact():
    if request.method == "POST":
        name = request.form.get("name")
        email = request.form.get("email")
        message = request.form.get("message")

        print(name, email, message)

        return render_template('contacto_exitoso.html')

    return render_template('contact.html')

@app.route("/gallery")
def gallery():
    return render_template('gallery.html')

@app.route("/menu")
def menu():
    lista = ["Hola", "Como", "Estas", "Mateo"]
    return render_template('menu.html', lista=lista)

@app.route("/reservation")
def reservation():
    return render_template('reservation.html')

@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404

@app.errorhandler(500)
def page_not_found(e):
    return render_template('500.html'), 500



if __name__ == "__main__":
    app.run("127.0.0.1", port="5001", debug=True)