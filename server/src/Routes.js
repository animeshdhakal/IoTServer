const express = require("express");

const Router = express.Router();
const HomeAtion = require("./schemas");



Router.get("/:auth/setPin/:Pin", async (req, res) => {
  try {
    const { auth, Pin } = req.params;

    const findAuth = await HomeAtion.findOne({ _id: auth });
    if (findAuth) {
      findAuth.NormalPins[Pin] = req.query.value;
      findAuth.save();
      res.send("Success");
    } else {
      res.send("Invalid Auth");
    }
  } catch {
    res.send("Error");
  }
});

Router.get("/:auth/getAll", async (req, res) => {
  try {
    const { auth } = req.params;

    const findAuth = await HomeAtion.findOne({ _id: auth });
    if (findAuth) {
      findAuth.UsedPins.map((item) => {
        res.set("NP" + item.substr(1), findAuth.NormalPins[item]);
      });
      res.send("hello");
    } else {
      res.header("error", "Auth Invalid").send("Invalid Auth");
    }
  } catch {
    res.header("error", "Error").send("Error");
  }
});

module.exports = Router;
