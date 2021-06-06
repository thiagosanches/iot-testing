const express = require('express')
const bodyParser = require('body-parser');
const app = express()
const port = 5000
const SerialPort = require('serialport')
const port = new SerialPort('/dev/ttyACM0', { baudRate: 9600 })

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get('/t', (req, res) => {
    sendDataToArduino('t')
    res.send('Hello World!')
})

app.get('/b', (req, res) => {
    sendDataToArduino('b')
    res.send('Beeping and Blinking!')
})

//curl -X POST localhost:3000/m --data "{\"message\":\"hi\"}" -H "Content-Type: application/json"
app.post('/m', (req, res) => {
    sendDataToArduino(`#${req.body.message}`)
    return res.send('Message sent!');
})

app.listen(port, () => {
    console.log(`IoT listening at http://localhost:${port}`)
})

function sendDataToArduino(message) {  
    port.write(`${message}\n`, function (data, err) {
        if (err)
            console.log('Done ', err.message)
    })
}
