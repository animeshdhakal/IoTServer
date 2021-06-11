const mongoose = require('mongoose')
require('dotenv').config()


mongoose.connect(process.env.DB, {useNewUrlParser: true, useUnifiedTopology: true}).then(()=>{
    console.log("Connection to DB Successfull");
}).catch(()=>{
    console.log("Connection to DB failed");
});