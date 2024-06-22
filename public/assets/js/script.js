const ctxSuhu = document.getElementById('chartSuhu').getContext('2d');
const ctxKelembaban = document.getElementById('chartKelembaban').getContext('2d');

Chart.defaults.font.size = 16;
const chartSuhu = new Chart(ctxSuhu, {
    type: 'line',
    data: {
        labels: [],
        datasets: [
            {
                label: 'Suhu',
                data: [],
                borderColor: 'red',
                borderWidth: 1,
                fill: false
            },
        ]
    },
    options: {
        responsive: true,
        scales: {
            x: {
                type: 'time',
                time: {
                    unit: 'second',
                    displayFormats: {
                        second: 'h:mm:ss a'
                    }
                }
            },
            y: {
                type: 'linear',
                position: 'left',
                beginAtZero: true,
                title: {
                    display: true,
                    text: 'Suhu (°C)'
                }
            },
        }
    }
});

const chartKelembaban = new Chart(ctxKelembaban, {
    type: 'line',
    data: {
        labels: [],
        datasets: [
            {
                label: 'Kelembaban',
                data: [],
                borderColor: 'blue',
                borderWidth: 1,
                fill: false
            }
        ]
    },
    options: {
        responsive: true,
        scales: {
            x: {
                type: 'time',
                time: {
                    unit: 'second',
                    displayFormats: {
                        second: 'h:mm:ss a'
                    }
                }
            },
            y: {
                type: 'linear',
                position: 'left',
                beginAtZero: true,
                title: {
                    display: true,
                    text: 'Kelembaban (%)'
                }
            },
        }
    }
});

let ws;

function connectWebSocket() {
    ws = new WebSocket('ws://localhost:8080');

    ws.onopen = () => {
        console.log('WebSocket connection established');
    };

    ws.onmessage = function(event){
        try {
            const data = JSON.parse(event.data);
            processWebSocketMessage(data);
        } catch (error) {
            console.error('Error processing WebSocket message:', error);
        }
    }

    ws.onclose = function() {
        console.log('WebSocket connection closed');
    };

    ws.onerror = function(error) {
        console.error('WebSocket error:', error);
    };

}

function processWebSocketMessage(data) {
    if (data.nim === 'G.231.20.0136' && data.hasOwnProperty('suhu') && data.hasOwnProperty('kelembaban')) {
        const currentTime = new Date();

        chartSuhu.data.labels.push(currentTime);
        chartSuhu.data.datasets[0].data.push({
            x: currentTime,
            y: data.suhu
        });

        chartKelembaban.data.labels.push(currentTime);
        chartKelembaban.data.datasets[0].data.push({
            x: currentTime,
            y: data.kelembaban
        });

        if (chartSuhu.data.labels.length > 50) {
            chartSuhu.data.labels.shift();
            chartSuhu.data.datasets[0].data.shift();
        }

        if (chartKelembaban.data.labels.length > 50) {
            chartKelembaban.data.labels.shift();
            chartKelembaban.data.datasets[0].data.shift();
        }

        requestAnimationFrame(() => {
            chartSuhu.update();
            chartKelembaban.update();
        });

        document.getElementById('suhu').innerText = data.suhu.toFixed(2);
        document.getElementById('kelembaban').innerText = data.kelembaban.toFixed(2);
    }
}

connectWebSocket();

function controlLED(pin, state) {
    const message = {
        nim: 'G.231.20.0136',
        messages: `${pin}=${state}`
    };
    console.log(message);
    ws.send(JSON.stringify(message));
}

