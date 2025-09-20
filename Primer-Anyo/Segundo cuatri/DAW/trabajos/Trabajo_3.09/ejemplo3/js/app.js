function calcularPropina() {
    const total = parseFloat(document.getElementById('total').value);
    const porcentaje = parseFloat(document.getElementById('porcentaje').value);

    if (isNaN(total) || isNaN(porcentaje)) {
        document.getElementById('resultado').textContent = "Por favor, introduce números válidos.";
        return;
    }

    const propina = total * (porcentaje / 100);
    const totalConPropina = total + propina;

    document.getElementById('resultado').innerHTML = `
        <p>Propina: €${propina.toFixed(2)}</p>
        <p>Total a pagar: €${totalConPropina.toFixed(2)}</p>
    `;
}
