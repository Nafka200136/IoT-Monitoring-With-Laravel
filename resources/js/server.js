import WebSocket from "ws";
import mqtt from 'mqtt';

const wss = new WebSocket.Server({
    port: 8080,
    // autoAcceptConnections: false
});

wss.on('connection', ws => {

    console.log('New WebSocket connection');

    const mqttServer = 'mqtt://usm.revolusi-it.com';
    const mqttUser = 'usm';
    const mqttPassword = 'usmjaya24';
    const mqttTopic = 'test/test';

    const mqttClient = mqtt.connect(mqttServer, {
        username: mqttUser,
        password: mqttPassword
    });

    mqttClient.on('connect', () => {
        console.log('Connected to MQTT server')
        mqttClient.subscribe(mqttTopic, (err) =>{
            if (err) {
                console.error('Failed to subscribe to topic:', err);
            } else {
                console.log(`Subscribed to topic ${mqttTopic}`);
            }
        });
    });

    mqttClient.on('message', (topic, message) => {
        if (topic === mqttTopic) {
            const jsonMessage = message.toString();
            console.log('Received: ', jsonMessage);
            ws.send(message.toString());
        }
    });

    ws.on('message', (data) => {
        const msg = JSON.parse(data);
        mqttClient.publish(mqttTopic, JSON.stringify(msg));
    });

    ws.on('close', () => {
       mqttClient.end();
    });

    console.log('WebSocket server is running on ws://localhost:8080');

});










