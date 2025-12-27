const botonConcatenador = document.getElementById("boton_concatenador")
botonConcatenador.onclick = function(event) {
    const cadena1 = document.getElementById("cadena1").value
    const cadena2 = document.getElementById("cadena2").value
    const cadenaNueva = cadena1 + " " + cadena2
    alert(cadenaNueva)
    event.preventDefault()
}