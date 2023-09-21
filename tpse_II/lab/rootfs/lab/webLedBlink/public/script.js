document.addEventListener("DOMContentLoaded", () => {
    const ledSelect = document.getElementById("led");
    const ligarBtn = document.querySelector("button:nth-of-type(1)");
    const desligarBtn = document.querySelector("button:nth-of-type(2)");

    ligarBtn.addEventListener("click", ligarLED);
    desligarBtn.addEventListener("click", desligarLED);
});

function ligarLED() {
    const led = document.getElementById("led").value;
    enviarComando(led, 1);
}

function desligarLED() {
    const led = document.getElementById("led").value;
    enviarComando(led, 0);
}

function enviarComando(led, estado) {
    fetch(`/led?led=${led}&estado=${estado}`, { method: "POST" })
        .then((response) => response.text())
        .then((data) => {
            console.log(data);
        })
        .catch((error) => {
            console.error("Erro:", error);
        });
}
