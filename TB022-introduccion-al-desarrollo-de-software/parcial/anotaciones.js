// JavaScript se usa principalmente para añadir interactividad en las paginas web
// Tambien es usado como lenguaje para el backend a traves de aplicaciones de servidor como Node.js

const PI = 3.14159265359                    // Las constantes son inmutables y no puede asignarse otro valor a ellas
let cantidadManzanas = 3                    // Las variables si pueden ser sobreescritas con otros valores


// Tipos de datos (puedo saber el tipo de dato que es con el operador typeof)

const manzanas = 32                                                               // Number
const precioManzanas = 95.5                                                       // Number
const nombre = "Pedro"                                                            // String
const hayBananas = false                                                          // Boolean

const persona = {nombre:"Pedro" , edad:26 , apellido:"Diaz"}                      // Object
const numeros = [1,2,3,4,5]                                                       // Object                                                                
let valorInicial = null                                                           // Object

const ultimoDigitoPi = undefined                                                  // Undefined



let numero = 8 

// Ejemplo de estructura if

if (numero < 20) {
    console.log("El numero es menor a 20")
} else if (numero == 20) {
    console.log("El numero es 20")
} else {
    console.log("El numero es mayor a 20")
}

//  Ejemplo de estructura while

while (numero < 20) {
    numero ++  // numero = numero + 1
}

// Ejemplo estructura for 

for (let i=1; i<5; i++) {
    const nuevoValor = numero + i
}

// Ejemplo estructura switch 

const color = "red"

switch(color) {
    case "red": {
        console.log("El color es rojo")
        break
    }
    case "blue": {
        console.log("El color es azul")
        break
    }
    case "yellow": {
        console.log("El color es amarillo")
        break
    }
    default: {
        console.log("El color no es valido")
    }
}



// Funciones

function modulo(x,y) {
    return (x**2 + y**2)**0.5
}

// Funciones como tipo de dato

const modulo = function (x,y) {
    return (x**2 + y**2)**0.5
}

// Funciones flecha

const suma = (x,y) => x + y

// Todos los tipos son de tipo function 

console.log(((x,y) => x + y)(2,3))       // imprime el resultado de la funcion flecha 



// En javascript las funciones son first-class-citizen, se pueden manipular como valores 

const numerosEjemplo = [1,2,3,4,5,6,7]
const filtrados = numerosEjemplo.filter(x => x%2 == 0)          // Funcion anonima

// Aca estamos pasando una funcion como valor al metodo filter, quien internamente la va a llamar para filtrar la lista



// DOM: es una intergaz de programacion para representar elementos de HTML como objetos en javascript.
// Permite la manipulacion de la pagina web mediante codigo

// Cada atributo de ese elemento HTML, es una propiedad de ese objeto en javascript
// Los elementos HTML respodnden a eventos. Esos eventos en javascript se representan como funciones asignadas al objeto

/*
Ejemplo de DOM. Obtener el contenido del segundo parrafo

<p> Hola </p>
<p> Mundo! </p>

*/

const parrafos = document.getElementsByTagName("p")
const segundoParrafo = parrafos[1].innerText

// Funciones y props. basicas del DOM

document.getElementsByTagName()
document.getElementsByClassName()
document.getElementById()
document.createElement()                                // Crea un nuevo elemento indicando el tag. nuevoParrafo = document.createElement("p")
                                                        // Para agregarle contenido a ese parrafo uso nuevoParrafo.textContent = "Hola"

document.body                                           // Accede al elemento <body> del HTML

// parrafos puede ser reemplazado por cualquier otro elemento
                                    
parrafos.appendChild()                                  // Agrega un solo elemento al final del elemento especificado. document.body.appendChild(nuevoParrafo)
parrafos.append()                                      // Similar al anterior pero admite mas de un elemento para agregar y tambien admite texto

parrafos.innerText()                                   // Devuelve solo el texto visible dentro del elemento
parrafos.innerHTML()                                   // Devuelve TODO dentro del elemento, incluido tags
parrafos.style()                                       // Sirve para cambiar los atributos del tag style o css   elemento.style.backgroundColor = "lightblue"
parrafos.parentElement()                               // Devuelve el contenedor padre del elemento. Si tiene id definido devuelve eso


// ----------------- Eventos en la la pgina web ----------------- 

/* Para definir una respuesta a un evento necesitamos 
1- Un obejeto dDOM que "escuche" el evento, por ejemplo un boton
2- Una funcion asignada al objeto que realice una accion cada vez que se acciona la señal 

Como definir un evento */

const botonAlerta = document.getElementById("boton")
botonAlerta.addEventListener("click",function(event){               // La funcion siempre recibe event como parametro
    alert("Hello World!")
})

/* Otros eventos comunes  

    mouseover: Cuando el cursor pasa sobre un elemento
    mouseout: Cuando el cursor sale de un elemento
    keydown: Cuando se presiona una tecla
    keyup: Cuando se suelta una tecla
    keypress: Cuando se presiona y suelta una tecla
    submit: Cuando se envia un formulario
    change: Cuando el valor de un elemento de entrada cambia y se confirma (Ej. seleccionar una opcion en un menu)
    scroll: Cuando se desplaza el contenido de un elemento
     */

