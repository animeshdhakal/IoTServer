const mongoose = require('mongoose')


const HomeAtionSchema = new mongoose.Schema({
    email: {
        type: String,
        required: true
    },
    password: {
        type: String,
        required: true
    },
    NormalPins: {
        N0: {type: String,default: 1},
        N1: {type: String,default: 1},
        N2: {type: String,default: 1},
        N3: {type: String,default: 1},
        N4: {type: String,default: 1},
        N5: {type: String,default: 1},
        N6: {type: String,default: 1},
        N7: {type: String,default: 1},
        N8: {type: String,default: 1},
        N9: {type: String,default: 1}
    },
    UsedPins: {
        type: Array,
        default: ["N0", "N1", "N2", "N3"]
    }
})  


module.exports = mongoose.model('HomeAtionDb', HomeAtionSchema);