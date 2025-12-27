function validateForm() {
    // Selecciona todos los checkboxes con la clase 'check'
    const checkboxes = document.getElementsByClassName('check')
    let checkedCount = 0

    // Cuenta cuántos checkboxes están seleccionados
    for (let i = 0; i < checkboxes.length; i++) {
        if (checkboxes[i].checked) {
            checkedCount++;
        }
    }
    
    // Si menos de dos están seleccionados, previene el envío del formulario
    if (checkedCount < 2) {
        return false 
    }

    // Si se seleccionan al menos dos, permite el envío del formulario
    return true 
}