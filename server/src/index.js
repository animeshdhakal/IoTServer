const express = require('express')
const app = express()
require('./db')

app.use(require('./Routes'))
app.use(express.static("public"))

app.listen(2000, process.env.HOST, ()=>{
    console.log("Started Server");
})