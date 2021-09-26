const express = require('express')
const bodyParser = require('body-parser');
const app = express()
const port = 5000
const SerialPort = require('serialport')
const arduino = new SerialPort('/dev/ttyACM0', { baudRate: 9600 })

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get('/t', (req, res) => {
    sendDataToArduino('T')
    res.send('Take a look at the display!')
})

app.get('/b', (req, res) => {
    sendDataToArduino('B')
    res.send('Beeping and Blinking!')
})

app.get('/0', (req, res) => {
    sendDataToArduino('0')
    res.send('Getting the decibels!')
})

app.post('/c', (req, res) => {
    sendDataToArduino(`C${req.body.RGBColor}`)
    res.send(`Just sent the '${req.body.RGBColor}' color to the display!`)
})

/*
example: curl -X POST http://localhost:5000/m \
    --data "{\"sender\": \"123\",\"message\":\"Hii\"}" -H "Content-Type: application/json"
*/
app.post('/m', (req, res) => {
    let message = ""
    if (req.body.sender) {
        message = `${req.body.sender.toLowerCase()}:`;
        message += req.body.message;
    } else {
        message = req.body.message;
    }

    sendDataToArduino(`#${message.replace(/[^a-zA-Z0-9?:,. ]/gi, '')}`)
    return res.send(`Message '${message}' sent!`);
})

app.listen(port, () => {
    console.log(`IoT listening at http://localhost:${port}`)
})

function sendDataToArduino(message) {
    arduino.write(`${message.trim()}\n`, function (data, err) {
        if (err)
            console.log('error', err.message)
    })
}
